#include "class_eton_client.h"
//boost��ͷ�ļ�
#include <boost/bind.hpp>
//��׼c++ͷ�ļ�
#include <iostream>
using namespace std;
//log4z��ͷ�ļ�
#include "../log4z/log4z.h"
using namespace zsummer::log4z;

//���캯��
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
//��������
class_eton_client::~class_eton_client()
{

}
#if ENABLE_NIAN_FEN_PACKET
//������ݻ���
void class_eton_client::clear_data()
{
	m_current_index = 0;
	memset(m_data, 0, MAX_LEN_PACK);
}
#endif
#if ENABLE_TIMER
//���ö�ʱ��
void class_eton_client::timer_reset()
{
	try
	{
		//�趨��ʱ����ʱʱ��  
		m_deadline_timer.expires_from_now(boost::posix_time::seconds(70));
	}
	catch (const std::exception& e)
	{
		LOGE("server exception: " << e.what());
	}
	
}
//������ʱ��
void class_eton_client::timer_start()
{
	//����������ʱ�� 
	m_deadline_timer.async_wait(boost::bind(&class_eton_client::timer_out, this));
}
//��ʱ����
void class_eton_client::timer_out()
{
	if (m_deadline_timer.expires_at() <= deadline_timer::traits_type::now())
	{// �����ĵȴ���ʱ
		m_time_out = TRUE;
		if(FALSE == m_client_exit)
		{
#ifdef DEBUG_CLIENT
			cout << "client time out." << endl;
#endif	
			try
			{			
				// ȡ����ʱ������
				m_deadline_timer.cancel();
				// �رն�Ӧ��socket �������ӳ�ʱ/recv��ʱ
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
	// ������������ĳ�ʱ������������ѳɹ�/�û����������˶�ʱ��  
	// ����������ʱ�� 	
	if (FALSE == m_client_exit)
	{
#ifdef DEBUG_CLIENT
		cout << "timer reset." << endl;
#endif
		m_time_out = FALSE;
		m_deadline_timer.async_wait(boost::bind(&class_eton_client::timer_out, this));
	}	
}
//�ͻ����˳�
void class_eton_client::client_already_exit()
{
	if (FALSE == m_time_out)
	{
		m_client_exit = TRUE;
		try
		{
			// ȡ����ʱ������
			m_deadline_timer.cancel();
			// �رն�Ӧ��socket �������ӳ�ʱ/recv��ʱ,��linux�лᱨ��:
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
//�ͻ���ID�Ƿ���Ч
bool class_eton_client::get_client_id_available()
{
	return m_client_id_available;
}
//���ÿͻ���ID�Ƿ���Ч
void class_eton_client::set_client_id_available(bool available)
{
	m_client_id_available = available;
}
