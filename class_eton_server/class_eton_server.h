#ifndef __CLASS_ETON_SERVER_H__
#define __CLASS_ETON_SERVER_H__
//�Զ���ͷ�ļ�
#include "../debug_switch/debug.h"
//boost��ͷ�ļ�
#include <boost/asio.hpp>
#include <boost/system/system_error.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/container/vector.hpp>
using namespace boost;
using namespace boost::asio;
using namespace boost::system;
//��׼C++ͷ�ļ�
#include <iostream>
using namespace std;
//�Զ���ͷ�ļ�
#include "../class_eton_client/class_eton_client.h"
//�ඨ��
class class_eton_server
{
private:
	//˽�г�Ա����
	io_service & m_ios;
	TCP::acceptor m_acceptor;
	size_t m_thread_num;
	thread_group m_thread_group;
public:
	//���캯��
	class_eton_server(io_service & ios, unsigned int port, size_t cpu_core_num);
	//��������
	~class_eton_server();

	//�ص����տͻ�������
	void accept_client_connection(void);
	//����ios run �߳�
	void start();
	//�ر�ios run �߳�
	void stop();
	//�ͻ������ӻص�������
	void accept_handler(system::error_code ec, spt_client client);
	//�������������ص�����
	void read_handler(system::error_code ec, size_t len_data, char * data_read, spt_client client);
	//������д�����ص�����
	void write_handler(system::error_code ec, spt_client client);
};
#endif