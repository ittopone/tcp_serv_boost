#include "../class_pspc/class_pspc.h"
#include "../../class_eton_database/class_eton_database.h"
#include "../../class_global/class_global.h"
//boost��ͷ�ļ�
#include <boost/container/vector.hpp>
using namespace boost;
//��׼C++ͷ�ļ�
#include <iostream>
using namespace std;
//���캯��
class_pspc::class_pspc(char * pdata, size_t * len_data, bool & client_send_available, \
	spt_client & client, protocol_pstruct pst)
	:m_client_send_available(client_send_available),
	m_client(client)
{
	m_data_write = pdata;
	m_len_data = len_data;
	m_pst = pst;
	this->pspc_handle_data();
}
//��������
class_pspc::~class_pspc()
{
	
}
//����ȷ����
int class_pspc::pspc_cfm_code_ret(unsigned int cfm_code)
{
	m_pst->pack_mark = CFM_PACK;
	int ret = 0;
	ret = class_eton_protocol::set_struct_pack_len(m_pst, LEN_CFM_CODE);
	if (ret < 0)
		goto ret_error;
	ret = class_eton_protocol::set_struct_cfm_code(m_pst, cfm_code);
	if (ret < 0)
		goto ret_error;
	*m_len_data = class_eton_protocol::pack_data(m_pst, m_data_write, MAX_LEN_PACK);
	if (ret < 0)
		goto ret_error;
	else
	{
		m_client_send_available = TRUE;
		return 1;
	}
ret_error:
	m_client_send_available = FALSE;
	return -1;
}
//����ȷ���������
int class_pspc::pspc_cfm_code_and_data_ret(unsigned int cfm_code, char * data, size_t len)
{
	m_pst->pack_mark = CFM_PACK;
	int ret = 0;
	ret = class_eton_protocol::set_struct_pack_len(m_pst, LEN_CFM_CODE + len);
	if (ret < 0)
		goto ret_error;
	ret = class_eton_protocol::set_struct_cfm_code_and_data(m_pst, cfm_code, data, len);
	if (ret < 0)
		goto ret_error;
	*m_len_data = class_eton_protocol::pack_data(m_pst, m_data_write, MAX_LEN_PACK);
	if (ret < 0)
		goto ret_error;
	else
	{
		m_client_send_available = TRUE;
		return 1;
	}
ret_error:
	m_client_send_available = FALSE;
	return -1;
}
//pspc��������
void class_pspc:: pspc_handle_data()
{
	switch (class_eton_protocol::get_struct_cmd_id(m_pst))
	{
	case CMD_APP_GET_PSPC_LIST://�ֻ���ȡpspc�豸�б�
		this->pspc_handle_CMD_APP_GET_PSPC_LIST();
		break;
	default:
		m_client_send_available = FALSE;
		break;
	}
}
//pspc����APP��ȡpspc�豸�б�ָ��
void class_pspc::pspc_handle_CMD_APP_GET_PSPC_LIST()
{
#ifdef DEBUG_PSPC
	cout << "pspc����APP��ȡpspc�豸�б�ָ��" << endl;
#endif
	char phone_num[12] = { 0 };
	class_eton_protocol::get_struct_phone_num(m_pst, phone_num);
	container::vector<spt_dev_list>  vector_dev_list;
	if (!class_eton_database::db_get_device_list(DEV_TYPE_PSPC, phone_num, vector_dev_list))
	{//���ֻ��Ż�δ�󶨸����͵��κ��豸
#ifdef DEBUG_PSPC
		cout << "���ֻ��Ż�δ�󶨸����͵��κ��豸" << endl;
#endif
		pspc_cfm_code_ret(CFM_APP_GET_PSPC_LIST_FAIL);
		return;
	}
	char data[2 * MAX_LEN_PACK_DATA] = { 0 };
	size_t index = 0;
	for (unsigned int i = 0; i < vector_dev_list.size(); i++)
	{
		switch ((vector_dev_list.at(i))->dev_series)
		{
		case DEV_SERIES_PSPC1:
			data[index++] = DEV_SERIES_PSPC1;
			class_global::hex_str_to_hex(data+index, (vector_dev_list.at(i))->dev_id, LEN_DEV_ID_PSPC1);
			index += LEN_DEV_ID_PSPC1;
			break;
		default:
			m_client_send_available = FALSE;
			return;
		}
	}
#ifdef DEBUG_PSPC
	cout << "��ȡpspc�豸�б�ɹ�." << endl;
#endif
	pspc_cfm_code_and_data_ret(CFM_APP_GET_PSPC_LIST_OK, data, index);
}