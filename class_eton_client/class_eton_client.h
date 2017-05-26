#ifndef __CLASS_ETON_CLIENT_H__
#define __CLASS_ETON_CLIENT_H__
//自定义头文件
#include "../debug_switch/debug.h"
//boost库头文件
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio/deadline_timer.hpp>
using namespace boost;
using namespace boost::asio;
using namespace boost::system;
//常量定义
//定时器开关控制
#define ENABLE_TIMER 0
//粘包，分包处理开关控制
#define ENABLE_NIAN_FEN_PACKET 0
//自定义头文件
#include "../class_eton_protocol/class_eton_protocol.h"
//重命名
typedef boost::asio::ip::tcp TCP;
typedef boost::shared_ptr<TCP::socket> spt_socket;
//类定义
class class_eton_client
{
private:
	//私有成员变量
	bool m_client_id_available;
#if ENABLE_TIMER
	bool m_client_exit;
	bool m_time_out;
	deadline_timer m_deadline_timer;
#endif
public:
	//公开成员变量
	char m_client_id[2 * MAX_LEN_DEV_ID + 1];
	TCP::socket m_socket;
#if ENABLE_NIAN_FEN_PACKET
	unsigned int m_current_index;
	char m_data[MAX_LEN_PACK];
#endif
	//构造函数
	class_eton_client(io_service & ios);
	//析构函数
	~class_eton_client();
#if ENABLE_NIAN_FEN_PACKET
	//清空数据缓冲
	void clear_data();
#endif
#if ENABLE_TIMER
	//重置定时器
	void timer_reset();
	//开启定时器
	void timer_start();
	//超时处理
	void timer_out();
	//客户端退出
	void client_already_exit();
#endif
	//客户端ID是否有效
	bool get_client_id_available();
	//设置客户端ID是否有效
	void set_client_id_available(bool available);
};
//重命名
typedef boost::shared_ptr<class_eton_client> spt_client;
#endif
