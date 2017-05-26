#ifndef __CLASS_PACK_HANDLE_H__
#define __CLASS_PACK_HANDLE_H__
//boost��ͷ�ļ�
#include <boost/shared_ptr.hpp>
//�Զ���ͷ�ļ�
#include "../class_eton_client/class_eton_client.h"
#include "../class_eton_protocol/class_eton_protocol.h"
#include "../class_eton_client/class_eton_client.h"
//�ඨ��
class class_pack_handle
{
public:
	char m_data_write[MAX_LEN_PACK];
	bool m_client_send_available;
	size_t m_len_data;
	spt_client m_client;
	protocol_struct m_st;
	//���캯��
	class_pack_handle();
	//��������
	~class_pack_handle();
	//������
	void handle_pack(char * data_read, size_t len_data, spt_client client);
	//����������
	void handle_heartbeat();
	//�ֻ�appע�������
	void handle_app_register();
	//�ֻ�app��¼������
	void handle_app_login();
	//�ֻ��޸��û��ǳ�
	void handle_app_modify_uname();
	//�ֻ��޸��û�����ָ��
	void handle_app_modify_pswd();
	//����ȷ����
	int handle_cfm_code_ret(unsigned int cfm_code);
	//����ȷ���������
	int handle_cfm_code_and_data_ret(unsigned int cfm_code, char * data, size_t len);
	//�豸���ʹ���
	void handle_device_type();	
	//pspc�豸
	void handle_device_type_pspc();
	//pspc1�豸
	void handle_device_series_pspc1();
};
//������
typedef boost::shared_ptr<class_pack_handle> spt_pack_handle;
#endif