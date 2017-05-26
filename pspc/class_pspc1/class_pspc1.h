#ifndef __CLASS_PSPC1_H__
#define __CLASS_PSPC1_H__
//boost��ͷ�ļ�
#include <boost/shared_ptr.hpp>
//�Զ���ͷ�ļ�
#include "../class_pspc/class_pspc.h"
#include "define_pspc1.h"
//�ඨ��
class class_pspc1
{
public:
	char * m_data_write;
	bool & m_client_send_available;
	size_t * m_len_data;
	spt_client & m_client;
	protocol_pstruct m_pst;
	//���캯��
	class_pspc1(char * pdata, size_t * len_data, bool & client_send_available, spt_client & client, protocol_pstruct pst);
	//��������
	~class_pspc1();
	//����ȷ����
	int pspc1_cfm_code_ret(unsigned int cfm_code);
	//pspc1��������
	void pspc1_handle_data();
	//����pspc1��¼������ָ��
	void pspc1_handle_CMD_PSPC1_LOGIN();
	//�����ֻ���pspc1�豸ָ��
	void pspc1_handle_CMD_APP_BIND_PSPC1();
	//��app���͵�����ת����pspc1
	void pspc1_app_data_to_pspc1(unsigned short cmd);
	//��pspc1���͵�����ת����app
	void pspc1_pspc1_data_to_app(unsigned short cmd);
	//����ָ���ȡȷ����
	unsigned short pspc1_get_check_code_by_cmd(unsigned short cmd,bool is_ok);
};
//������
typedef boost::shared_ptr<class_pspc1> spt_pspc1;
#endif