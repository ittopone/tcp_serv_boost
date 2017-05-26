#include "class_eton_server.h"
//boost��ͷ�ļ�
#include <boost/format.hpp>
//log4z��ͷ�ļ�
#include "../log4z/log4z.h"
using namespace zsummer::log4z;
//�Զ���ͷ�ļ�
#include "../class_global/class_global.h"
#include "../class_pack_handle/class_pack_handle.h"
#include "../class_pack_handle/define_pack_handle.h"
//���캯��
class_eton_server::class_eton_server(io_service & ios, unsigned int port, size_t cpu_core_num)
	:m_ios(ios),
	m_thread_num(cpu_core_num * 2 + 2),
	m_acceptor(m_ios, TCP::endpoint(ip::address::from_string("192.168.1.229"), port))
{
	try
	{
		//��ӡ������Ϣ
#ifdef DEBUG_SERVER
		cout << "ip: " << m_acceptor.local_endpoint().address()
			<< ", port: " << m_acceptor.local_endpoint().port() << endl;
#endif
		//����IP��ַ��������
		m_acceptor.set_option(TCP::acceptor::reuse_address(true));
	}
	catch (const std::exception & e)
	{
		LOGE("server exception: " << e.what());
	}
	//��ʼ�����ͻ�������
	this->accept_client_connection();
	//��¼��������־
	LOGD("eton server start success.");
}
//��������
class_eton_server::~class_eton_server()
{

}
//�ص����տͻ�������
void class_eton_server::accept_client_connection(void)
{
	spt_client client(new class_eton_client(m_ios));
	m_acceptor.async_accept(client->m_socket, 
		bind(&class_eton_server::accept_handler, this, boost::asio::placeholders::error, client));
}
//����ios run �߳�
void class_eton_server::start()
{
	for (std::size_t i = 0; i < m_thread_num; i++)
	{
		m_thread_group.create_thread(bind(&io_service::run, &m_ios));
	}
}
//�ر�ios run �߳�
void class_eton_server::stop()
{
	m_ios.stop();
	m_thread_group.join_all();
}
//�ͻ������ӻص�������
void class_eton_server::accept_handler(system::error_code ec, spt_client client)
{
	if (ec)
	{
#ifdef DEBUG_SERVER
		cout << "accept client error." << endl;
#endif
		return;
	}	
#ifdef DEBUG_SERVER
	cout << "client connected: " << client->m_socket.remote_endpoint().address()
		<< ", " << client->m_socket.remote_endpoint().port()
		<< ", threadID: " << this_thread::get_id() << endl;
#endif
	//���ý��տͻ�����Ϣ����
	char * data_read = new char[MAX_LEN_BUFFER];
	client->m_socket.async_read_some(buffer(data_read , MAX_LEN_BUFFER),
		boost::bind(&class_eton_server::read_handler, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred, data_read, client));
#if ENABLE_TIMER
	//���ý��ճ�ʱ��ʱ��
	client->timer_reset();
	//��ʼ���ճ�ʱ��ʱ������
	client->timer_start();
#endif
	//���ؼ��������ͻ�������
	this->accept_client_connection();
}
//�������������ص�����
void class_eton_server::read_handler(system::error_code ec, size_t len_data, char * data_read, spt_client client)
{
	if (ec)
	{
#ifdef DEBUG_SERVER
		cout << "read data error,client exit." << endl;
#endif	
#if ENABLE_TIMER
		//�ͻ����Ѿ��˳�
		client->client_already_exit();
#endif
		if (client->get_client_id_available())
		{
			boost::mutex::scoped_lock lock(class_global::g_mutex);
			class_global::g_client_map.erase(string(client->m_client_id));
			client->set_client_id_available(FALSE);
#ifdef DEBUG_SERVER
			cout << "��u_map���Ƴ��ͻ���" << client->m_client_id << endl;
#endif
		}
		//�ֶ��ͷ��ڴ�
		delete[] data_read;
		return;
	}
#ifdef DEBUG_SERVER
	printf("read msg threadID: %s\r\n", (format("%1%") % this_thread::get_id()).str().c_str());
	for (unsigned int i = 0; i < len_data; i++)
	{
		printf("%02x ", *(data_read + i) & 0xff);
	}
	printf("\r\n");
#endif
	//����ͻ��˷��͹���������
	container::vector<size_t> vector_pack_mark_index =class_global::get_pack_mark_index(data_read, len_data);
#if ENABLE_NIAN_FEN_PACKET
	for (size_t index = 0; index < vector_pack_mark_index.size(); index++)
	{
		if (0 != client->m_current_index)
		{
#ifdef DEBUG_SERVER
			cout << "get latter part of the pack." << endl;
#endif
			class_global::my_strncpy(client->m_data + client->m_current_index, data_read, vector_pack_mark_index.at(index) + 1);
			client->m_current_index += (vector_pack_mark_index.at(index) + 1);
			spt_pack_handle pack_handle(new class_pack_handle());
			pack_handle->handle_pack(client->m_data, client->m_current_index,client);
			client->clear_data();
			//���ͻ��˷�������
			if (pack_handle->m_client_send_available)
			{
				(pack_handle->m_client)->m_socket.async_write_some(buffer(pack_handle->m_data_write,
					pack_handle->m_len_data), boost::bind(&class_eton_server::write_handler,
						this, boost::asio::placeholders::error, pack_handle->m_client));
			}			
			continue;
		}
		if (++index < vector_pack_mark_index.size())
		{
#ifdef DEBUG_SERVER
			cout << "get complete pack." << endl;
#endif
			spt_pack_handle pack_handle(new class_pack_handle());
			size_t len_temp = vector_pack_mark_index.at(index) - vector_pack_mark_index.at(index - 1) + 1;
			pack_handle->handle_pack(data_read + vector_pack_mark_index.at(index - 1), len_temp,client);
			//���ͻ��˷�������		
			if (pack_handle->m_client_send_available)
			{
				(pack_handle->m_client)->m_socket.async_write_some(buffer(pack_handle->m_data_write,
					pack_handle->m_len_data), boost::bind(&class_eton_server::write_handler,
						this, boost::asio::placeholders::error, pack_handle->m_client));
			}
		}
		else
		{
#ifdef DEBUG_SERVER
			cout << "get first part of the pack." << endl;
#endif
			client->m_current_index = len_data - vector_pack_mark_index.at(index - 1);
			class_global::my_strncpy(client->m_data, data_read + vector_pack_mark_index.at(index - 1), client->m_current_index);			
		}
	}
#else
	if (2 == vector_pack_mark_index.size())
	{//������ָ����봦��
#ifdef DEBUG_SERVER
		cout << "get complete pack." << endl;
#endif
		spt_pack_handle pack_handle(new class_pack_handle());
		pack_handle->handle_pack(data_read, len_data, client);
		//���ͻ��˷�������		
		if (pack_handle->m_client_send_available)
		{
			(pack_handle->m_client)->m_socket.async_write_some(buffer(pack_handle->m_data_write,
				pack_handle->m_len_data), boost::bind(&class_eton_server::write_handler,
					this, boost::asio::placeholders::error, pack_handle->m_client));
		}
	}
#endif
	//�ֶ��ͷ��ڴ�
	delete[] data_read;
#if ENABLE_TIMER
	//���ý��ճ�ʱ��ʱ��	
	client->timer_reset();
#endif
	//���²��ý�������
	char * data_read_new = new char[MAX_LEN_BUFFER];
	client->m_socket.async_read_some(buffer(data_read_new, MAX_LEN_BUFFER),
		boost::bind(&class_eton_server::read_handler, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred, data_read_new, client));
}
//������д�����ص�����
void class_eton_server::write_handler(system::error_code ec, spt_client client)
{
	if (ec)
	{
#ifdef DEBUG_SERVER
		cout << "write data error,client exit." << endl;
#endif
	}
}