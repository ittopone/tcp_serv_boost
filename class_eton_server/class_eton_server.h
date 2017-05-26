#ifndef __CLASS_ETON_SERVER_H__
#define __CLASS_ETON_SERVER_H__
//自定义头文件
#include "../debug_switch/debug.h"
//boost库头文件
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
//标准C++头文件
#include <iostream>
using namespace std;
//自定义头文件
#include "../class_eton_client/class_eton_client.h"
//类定义
class class_eton_server
{
private:
	//私有成员变量
	io_service & m_ios;
	TCP::acceptor m_acceptor;
	size_t m_thread_num;
	thread_group m_thread_group;
public:
	//构造函数
	class_eton_server(io_service & ios, unsigned int port, size_t cpu_core_num);
	//析构函数
	~class_eton_server();

	//回调接收客户端连接
	void accept_client_connection(void);
	//开启ios run 线程
	void start();
	//关闭ios run 线程
	void stop();
	//客户端连接回调处理函数
	void accept_handler(system::error_code ec, spt_client client);
	//服务器读操作回调函数
	void read_handler(system::error_code ec, size_t len_data, char * data_read, spt_client client);
	//服务器写操作回调函数
	void write_handler(system::error_code ec, spt_client client);
};
#endif