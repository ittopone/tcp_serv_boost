#ifndef __CLASS_PSPC_H__
#define __CLASS_PSPC_H__
//boost��ͷ�ļ�
#include <boost/shared_ptr.hpp>
//�Զ���ͷ�ļ�
#include "../../class_eton_protocol/class_eton_protocol.h"
#include "../../class_eton_client/class_eton_client.h"
#include "define_pspc.h"
//�ඨ��
class class_pspc
{
public:
	char * m_data_write;
	bool & m_client_send_available;
	size_t * m_len_data;
	spt_client & m_client;
	protocol_pstruct m_pst;
	//���캯��
	class_pspc(char * pdata, size_t * len_data, bool & client_send_available, spt_client & client, protocol_pstruct pst);
	//��������
	~class_pspc();
	//����ȷ����
	int pspc_cfm_code_ret(unsigned int cfm_code);
	//����ȷ���������
	int pspc_cfm_code_and_data_ret(unsigned int cfm_code, char * data, size_t len);
	//pspc��������
	void pspc_handle_data();
	//pspc����APP��ȡpspc�豸�б�ָ��
	void pspc_handle_CMD_APP_GET_PSPC_LIST();
};
//������
typedef boost::shared_ptr<class_pspc> spt_pspc;
#endif