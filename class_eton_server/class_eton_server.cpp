#include "class_eton_server.h"
//boost库头文件
#include <boost/format.hpp>
//log4z库头文件
#include "../log4z/log4z.h"
using namespace zsummer::log4z;
//自定义头文件
#include "../class_global/class_global.h"
#include "../class_pack_handle/class_pack_handle.h"
#include "../class_pack_handle/define_pack_handle.h"
//构造函数
class_eton_server::class_eton_server(io_service & ios, unsigned int port, size_t cpu_core_num)
	:m_ios(ios),
	m_thread_num(cpu_core_num * 2 + 2),
	m_acceptor(m_ios, TCP::endpoint(ip::address::from_string("192.168.1.229"), port))
{
	try
	{
		//打印调试信息
#ifdef DEBUG_SERVER
		cout << "ip: " << m_acceptor.local_endpoint().address()
			<< ", port: " << m_acceptor.local_endpoint().port() << endl;
#endif
		//设置IP地址快速重用
		m_acceptor.set_option(TCP::acceptor::reuse_address(true));
	}
	catch (const std::exception & e)
	{
		LOGE("server exception: " << e.what());
	}
	//开始监听客户端连接
	this->accept_client_connection();
	//记录服务器日志
	LOGD("eton server start success.");
}
//析构函数
class_eton_server::~class_eton_server()
{

}
//回调接收客户端连接
void class_eton_server::accept_client_connection(void)
{
	spt_client client(new class_eton_client(m_ios));
	m_acceptor.async_accept(client->m_socket, 
		bind(&class_eton_server::accept_handler, this, boost::asio::placeholders::error, client));
}
//开启ios run 线程
void class_eton_server::start()
{
	for (std::size_t i = 0; i < m_thread_num; i++)
	{
		m_thread_group.create_thread(bind(&io_service::run, &m_ios));
	}
}
//关闭ios run 线程
void class_eton_server::stop()
{
	m_ios.stop();
	m_thread_group.join_all();
}
//客户端连接回调处理函数
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
	//布置接收客户端消息任务
	char * data_read = new char[MAX_LEN_BUFFER];
	client->m_socket.async_read_some(buffer(data_read , MAX_LEN_BUFFER),
		boost::bind(&class_eton_server::read_handler, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred, data_read, client));
#if ENABLE_TIMER
	//重置接收超时定时器
	client->timer_reset();
	//开始接收超时定时器任务
	client->timer_start();
#endif
	//返回继续监听客户端连接
	this->accept_client_connection();
}
//服务器读操作回调函数
void class_eton_server::read_handler(system::error_code ec, size_t len_data, char * data_read, spt_client client)
{
	if (ec)
	{
#ifdef DEBUG_SERVER
		cout << "read data error,client exit." << endl;
#endif	
#if ENABLE_TIMER
		//客户端已经退出
		client->client_already_exit();
#endif
		if (client->get_client_id_available())
		{
			boost::mutex::scoped_lock lock(class_global::g_mutex);
			class_global::g_client_map.erase(string(client->m_client_id));
			client->set_client_id_available(FALSE);
#ifdef DEBUG_SERVER
			cout << "从u_map中移除客户端" << client->m_client_id << endl;
#endif
		}
		//手动释放内存
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
	//处理客户端发送过来的数据
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
			//给客户端返回数据
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
			//给客户端返回数据		
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
	{//完整的指令，进入处理
#ifdef DEBUG_SERVER
		cout << "get complete pack." << endl;
#endif
		spt_pack_handle pack_handle(new class_pack_handle());
		pack_handle->handle_pack(data_read, len_data, client);
		//给客户端返回数据		
		if (pack_handle->m_client_send_available)
		{
			(pack_handle->m_client)->m_socket.async_write_some(buffer(pack_handle->m_data_write,
				pack_handle->m_len_data), boost::bind(&class_eton_server::write_handler,
					this, boost::asio::placeholders::error, pack_handle->m_client));
		}
	}
#endif
	//手动释放内存
	delete[] data_read;
#if ENABLE_TIMER
	//重置接收超时定时器	
	client->timer_reset();
#endif
	//重新布置接收任务
	char * data_read_new = new char[MAX_LEN_BUFFER];
	client->m_socket.async_read_some(buffer(data_read_new, MAX_LEN_BUFFER),
		boost::bind(&class_eton_server::read_handler, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred, data_read_new, client));
}
//服务器写操作回调函数
void class_eton_server::write_handler(system::error_code ec, spt_client client)
{
	if (ec)
	{
#ifdef DEBUG_SERVER
		cout << "write data error,client exit." << endl;
#endif
	}
}