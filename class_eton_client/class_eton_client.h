#ifndef __CLASS_ETON_CLIENT_H__
#define __CLASS_ETON_CLIENT_H__
//�Զ���ͷ�ļ�
#include "../debug_switch/debug.h"
//boost��ͷ�ļ�
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio/deadline_timer.hpp>
using namespace boost;
using namespace boost::asio;
using namespace boost::system;
//��������
//��ʱ�����ؿ���
#define ENABLE_TIMER 0
//ճ�����ְ������ؿ���
#define ENABLE_NIAN_FEN_PACKET 0
//�Զ���ͷ�ļ�
#include "../class_eton_protocol/class_eton_protocol.h"
//������
typedef boost::asio::ip::tcp TCP;
typedef boost::shared_ptr<TCP::socket> spt_socket;
//�ඨ��
class class_eton_client
{
private:
	//˽�г�Ա����
	bool m_client_id_available;
#if ENABLE_TIMER
	bool m_client_exit;
	bool m_time_out;
	deadline_timer m_deadline_timer;
#endif
public:
	//������Ա����
	char m_client_id[2 * MAX_LEN_DEV_ID + 1];
	TCP::socket m_socket;
#if ENABLE_NIAN_FEN_PACKET
	unsigned int m_current_index;
	char m_data[MAX_LEN_PACK];
#endif
	//���캯��
	class_eton_client(io_service & ios);
	//��������
	~class_eton_client();
#if ENABLE_NIAN_FEN_PACKET
	//������ݻ���
	void clear_data();
#endif
#if ENABLE_TIMER
	//���ö�ʱ��
	void timer_reset();
	//������ʱ��
	void timer_start();
	//��ʱ����
	void timer_out();
	//�ͻ����˳�
	void client_already_exit();
#endif
	//�ͻ���ID�Ƿ���Ч
	bool get_client_id_available();
	//���ÿͻ���ID�Ƿ���Ч
	void set_client_id_available(bool available);
};
//������
typedef boost::shared_ptr<class_eton_client> spt_client;
#endif
