#include "class_eton_client.h"
//boost库头文件
#include <boost/bind.hpp>
//标准c++头文件
#include <iostream>
using namespace std;
//log4z库头文件
#include "../log4z/log4z.h"
using namespace zsummer::log4z;

//构造函数
class_eton_client::class_eton_client(io_service & ios)
	:
#if ENABLE_NIAN_FEN_PACKET
	m_current_index(0),
#endif
#if ENABLE_TIMER
	m_deadline_timer(ios),
	m_client_exit(FALSE),
	m_time_out(FALSE),
#endif
	m_socket(ios)
{
#if ENABLE_NIAN_FEN_PACKET
	memset(m_data, 0, MAX_LEN_PACK);
#endif
	memset(m_client_id, 0, MAX_LEN_DEV_ID);
	m_client_id_available = FALSE;
}
//析构函数
class_eton_client::~class_eton_client()
{

}
#if ENABLE_NIAN_FEN_PACKET
//清空数据缓冲
void class_eton_client::clear_data()
{
	m_current_index = 0;
	memset(m_data, 0, MAX_LEN_PACK);
}
#endif
#if ENABLE_TIMER
//重置定时器
void class_eton_client::timer_reset()
{
	try
	{
		//设定定时器超时时间  
		m_deadline_timer.expires_from_now(boost::posix_time::seconds(70));
	}
	catch (const std::exception& e)
	{
		LOGE("server exception: " << e.what());
	}
	
}
//开启定时器
void class_eton_client::timer_start()
{
	//重新启动定时器 
	m_deadline_timer.async_wait(boost::bind(&class_eton_client::timer_out, this));
}
//超时处理
void class_eton_client::timer_out()
{
	if (m_deadline_timer.expires_at() <= deadline_timer::traits_type::now())
	{// 真正的等待超时
		m_time_out = TRUE;
		if(FALSE == m_client_exit)
		{
#ifdef DEBUG_CLIENT
			cout << "client time out." << endl;
#endif	
			try
			{			
				// 取消定时器任务
				m_deadline_timer.cancel();
				// 关闭对应的socket 包括连接超时/recv超时
				m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
				m_socket.close();
			}
			catch (const std::exception& e)
			{
				LOGE("client exception: " << e.what());
			}			
		}
		return;
	}
	// 如果不是真正的超时，定是其操作已成功/用户重新设置了定时器  
	// 重新启动定时器 	
	if (FALSE == m_client_exit)
	{
#ifdef DEBUG_CLIENT
		cout << "timer reset." << endl;
#endif
		m_time_out = FALSE;
		m_deadline_timer.async_wait(boost::bind(&class_eton_client::timer_out, this));
	}	
}
//客户端退出
void class_eton_client::client_already_exit()
{
	if (FALSE == m_time_out)
	{
		m_client_exit = TRUE;
		try
		{
			// 取消定时器任务
			m_deadline_timer.cancel();
			// 关闭对应的socket 包括连接超时/recv超时,在linux中会报错:
			//client exception: shutdown: Transport endpoint is not connected
			//m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
			//m_socket.close();
		}
		catch (const std::exception & e)
		{
			LOGE("client exception: " << e.what());
		}	
	}	
}
#endif
//客户端ID是否有效
bool class_eton_client::get_client_id_available()
{
	return m_client_id_available;
}
//设置客户端ID是否有效
void class_eton_client::set_client_id_available(bool available)
{
	m_client_id_available = available;
}
