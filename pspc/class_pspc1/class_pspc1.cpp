#include "../class_pspc1/class_pspc1.h"
#include "../../class_eton_database/class_eton_database.h"
#include "../../class_global/class_global.h"
//��׼C++ͷ�ļ�
#include <iostream>
using namespace std;
//���캯��
class_pspc1::class_pspc1(char * pdata, size_t * len_data, bool & client_send_available,\
	spt_client & client, protocol_pstruct pst)
	:m_client_send_available(client_send_available),
	m_client(client)
{
	m_data_write = pdata;
	m_len_data = len_data;
	m_pst = pst;
	this->pspc1_handle_data();
}
//��������
class_pspc1::~class_pspc1()
{

}
//����ȷ����
int class_pspc1::pspc1_cfm_code_ret(unsigned int cfm_code)
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
//pspc1��������
void class_pspc1::pspc1_handle_data()
{
	switch (class_eton_protocol::get_struct_cmd_id(m_pst))
	{
	case CMD_PSPC1_LOGIN://Pspc1��¼������ָ��
		this->pspc1_handle_CMD_PSPC1_LOGIN();
		break;
	case CMD_APP_BIND_PSPC1://�ֻ���pspc1�豸ָ��
		this->pspc1_handle_CMD_APP_BIND_PSPC1();
		break;
	case CMD_APP_GET_PSPC1_STATUS://�ֻ���ȡpspc1�豸����״ָ̬��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_GET_PSPC1_STATUS);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_GET_PSPC1_STATUS);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_GET_PSPC1_SET_ARGS://�ֻ���ȡpspc1�豸���ò���ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_GET_PSPC1_SET_ARGS);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_GET_PSPC1_SET_ARGS);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_GLDZDL_ARG://�ֻ�����pspc1�豸����������������ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_GLDZDL_ARG);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_GLDZDL_ARG);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_LLBDZDL_ARG://�ֻ�����pspc1�豸©����������������ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_LLBDZDL_ARG);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_LLBDZDL_ARG);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_LLDZDL_ARG://�ֻ�����pspc1�豸©��������������ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_LLDZDL_ARG);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_LLDZDL_ARG);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_GYDZDY_ARG://�ֻ�����pspc1�豸��ѹ������ѹ����ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_GYDZDY_ARG);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_GYDZDY_ARG);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_QYDZDY_ARG://�ֻ�����pspc1�豸Ƿѹ������ѹ����ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_QYDZDY_ARG);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_QYDZDY_ARG);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_GLDKDZSJ_ARG://�ֻ�����pspc1�豸�����Ͽ�����ʱ�����ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_GLDKDZSJ_ARG);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_GLDKDZSJ_ARG);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_GYQYDKDZSJ_ARG://�ֻ�����pspc1�豸��ѹ/Ƿѹ�Ͽ�����ʱ�����ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_GYQYDKDZSJ_ARG);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_GYQYDKDZSJ_ARG);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_ZDCHZSJ_ARG://�ֻ�����pspc1�豸�Զ��غ�բʱ�����ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_ZDCHZSJ_ARG);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_ZDCHZSJ_ARG);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_ZDN_CLEAR://�ֻ�����pspc1�豸�ܵ�������ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_ZDN_CLEAR);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_ZDN_CLEAR);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_FL1DN_CLEAR://�ֻ�����pspc1�豸��·1��������ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_FL1DN_CLEAR);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_FL1DN_CLEAR);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_FL2DN_CLEAR://�ֻ�����pspc1�豸��·2��������ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_FL2DN_CLEAR);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_FL2DN_CLEAR);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_FL3DN_CLEAR://�ֻ�����pspc1�豸��·3��������ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_FL3DN_CLEAR);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_FL3DN_CLEAR);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_CLOCK://�ֻ�����pspc1�豸ʱ��У׼ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_CLOCK);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_CLOCK);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_DATE://�ֻ�����pspc1�豸����У׼ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_DATE);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_DATE);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_WIFI://�ֻ�����pspc1�豸WiFi����ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_WIFI);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_WIFI);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_WIFI_STIME://�ֻ�����pspc1�豸WiFi������ʼʱ��ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_WIFI_STIME);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_WIFI_STIME);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_WIFI_ETIME://�ֻ�����pspc1�豸WiFi������ֹʱ��ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_WIFI_ETIME);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_WIFI_ETIME);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_GET_PSPC1_RECORD://�ֻ���ȡpspc1�豸�ռ���Ϣָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_GET_PSPC1_RECORD);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_GET_PSPC1_RECORD);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_PSPC1_SEND_ALARM_LD://Pspc1���ֻ�����©��澯ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_PSPC1_SEND_ALARM_LD);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_PSPC1_SEND_ALARM_LD);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_PSPC1_SEND_ALARM_GY://Pspc1���ֻ����͸�ѹ�澯ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_PSPC1_SEND_ALARM_GY);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_PSPC1_SEND_ALARM_GY);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_PSPC1_SEND_ALARM_DY://Pspc1���ֻ����͵�ѹ�澯ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_PSPC1_SEND_ALARM_DY);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_PSPC1_SEND_ALARM_DY);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_PSPC1_SEND_ALARM_GL://Pspc1���ֻ����͹����澯ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_PSPC1_SEND_ALARM_GL);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_PSPC1_SEND_ALARM_GL);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_GET_PSPC1_MNDNSYQK://�ֻ���pspc1���ͻ�ȡĳ�����ʹ�����ָ��
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_GET_PSPC1_MNDNSYQK);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_GET_PSPC1_MNDNSYQK);
		else
			m_client_send_available = FALSE;
		break;
	default:
		m_client_send_available = FALSE;
		break;
	}
}
//����pspc1��¼������ָ��
void class_pspc1::pspc1_handle_CMD_PSPC1_LOGIN()
{
#ifdef DEBUG_PSPC1
	cout << "pspc1�豸��¼" << endl;
#endif 
	char dev_id[2 * LEN_DEV_ID_PSPC1 + 1] = { 0 };
	class_eton_protocol::get_struct_dev_id_str(m_pst, LEN_DEV_ID_PSPC1, dev_id);
	if (!class_eton_database::db_check_device_id_exist(dev_id))
	{//���ݿ�δ�洢���豸ID�����д洢
#ifdef DEBUG_PSPC1
		cout << "����pspc1�豸" << endl;
#endif 
		if (!class_eton_database::db_add_new_device(m_pst->dev_type, m_pst->dev_series, dev_id))
		{//����豸ʧ��
			this->pspc1_cfm_code_ret(CFM_PSPC1_LOGIN_FAIL);
			return;
		}
	}	
	if (!m_client->get_client_id_available())
	{
		boost::mutex::scoped_lock lock(class_global::g_mutex);	
		U_MAP::iterator it = class_global::g_client_map.find(string(dev_id));
		if (it == class_global::g_client_map.end())
		{
			class_global::g_client_map.insert(U_MAP::value_type(string(dev_id), m_client));
			strcpy(m_client->m_client_id, dev_id);
			m_client->set_client_id_available(TRUE);
#ifdef DEBUG_PSPC1
			cout << "pspc1�豸��¼�ɹ�." << endl;
#endif 
		}
		else
		{//�ʺ��ѵ�¼���Ƴ�֮ǰ�ĵ�¼��Ϣ�����Ŀǰ�ĵ�¼��Ϣ
			boost::mutex::scoped_lock lock(class_global::g_mutex);
			//�Ƴ�
			class_global::g_client_map.erase(string(dev_id));
			it->second->set_client_id_available(FALSE);
			//���
			class_global::g_client_map.insert(U_MAP::value_type(string(dev_id), m_client));
			strcpy(m_client->m_client_id, dev_id);
			m_client->set_client_id_available(TRUE);
#ifdef DEBUG_PSPC1
			cout << "pspc1�豸" << dev_id << "�ѳɹ���¼" << endl;
#endif
		}
	}
	this->pspc1_cfm_code_ret(CFM_PSPC1_LOGIN_OK);
}
//�����ֻ���pspc1�豸ָ��
void class_pspc1::pspc1_handle_CMD_APP_BIND_PSPC1()
{
#ifdef DEBUG_PSPC1
	cout << "�����ֻ���pspc1�豸ָ��." << endl;
#endif 
	char dev_id[2 * LEN_DEV_ID_PSPC1 + 1] = { 0 };
	class_eton_protocol::get_struct_dev_id_str(m_pst, LEN_DEV_ID_PSPC1, dev_id);
	char phone_num[12] = { 0 };
	class_eton_protocol::get_struct_phone_num(m_pst, phone_num);
#if 1
	if (!class_eton_database::db_check_device_id_exist(dev_id))
	{
#ifdef DEBUG_PSPC1
		cout << "pspc1�豸" << dev_id << "δע��." << endl;
#endif 
		//����豸
		if (!class_eton_database::db_add_new_device(m_pst->dev_type, m_pst->dev_series, dev_id))
		{
			this->pspc1_cfm_code_ret(CFM_APP_BIND_PSPC1_FAIL);
			return;
		}
	}
#endif
	if (!class_eton_database::db_device_bind_phone_num(m_pst->dev_type, m_pst->dev_series, dev_id, phone_num))
	{
#ifdef DEBUG_PSPC1
		cout << "pspc1�豸" << dev_id << "���ֻ���." << phone_num << "ʧ��." << endl;
#endif
		this->pspc1_cfm_code_ret(CFM_APP_BIND_PSPC1_FAIL);
		return;
	}
#ifdef DEBUG_PSPC1
	cout << "pspc1�豸" << dev_id << "���ֻ���." << phone_num << "�ɹ�." << endl;
#endif
	this->pspc1_cfm_code_ret(CFM_APP_BIND_PSPC1_OK);
}
//��app���͵�����ת����pspc1
void class_pspc1::pspc1_app_data_to_pspc1(unsigned short cmd)
{
#ifdef DEBUG_PSPC1
	cout << "��app���͵�����ת����pspc1" << endl;
#endif
	char dev_id[2 * LEN_DEV_ID_PSPC1 + 1] = { 0 };
	class_eton_protocol::get_struct_dev_id_str(m_pst, LEN_DEV_ID_PSPC1, dev_id);
	U_MAP::iterator it = class_global::g_client_map.find(string(dev_id));
	if (it == class_global::g_client_map.end())
	{
#ifdef DEBUG_PSPC1
		cout << "pspc1�豸" << dev_id  << "δ��¼."<< endl;
#endif
		if (CMD_PACK == m_pst->pack_mark)
		{
			this->pspc1_cfm_code_ret(this->pspc1_get_check_code_by_cmd(cmd, FALSE));
			return;
		}
		m_client_send_available = FALSE;
		return;
	}
	//ת������
	*m_len_data = class_eton_protocol::pack_data(m_pst, m_data_write, MAX_LEN_PACK);
	if (*m_len_data > 0)
	{
		m_client = it->second;
		m_client_send_available = TRUE;
#ifdef DEBUG_PSPC1
		cout << "������ת�����ݸ�pspc1�ɹ�." << endl;
#endif
	}
	else
	{
		if (CMD_PACK == m_pst->pack_mark)
		{
			this->pspc1_cfm_code_ret(this->pspc1_get_check_code_by_cmd(cmd, FALSE));
			return;
		}
		m_client_send_available = FALSE;
		return;
	}
}
//��pspc1���͵�����ת����app
void class_pspc1::pspc1_pspc1_data_to_app(unsigned short cmd)
{
#ifdef DEBUG_PSPC1
	cout << "��pspc1���͵�����ת����app" << endl;
#endif
	char phone_num[12] = { 0 };
	class_eton_protocol::get_struct_phone_num(m_pst, phone_num);
	U_MAP::iterator it = class_global::g_client_map.find(string(phone_num));
	if (it == class_global::g_client_map.end())
	{
#ifdef DEBUG_PSPC1
		cout << "�ֻ�" << phone_num << "δ��¼." << endl;
#endif
		if (CMD_PACK == m_pst->pack_mark)
		{
			this->pspc1_cfm_code_ret(this->pspc1_get_check_code_by_cmd(cmd, FALSE));
			return;
		}
		m_client_send_available = FALSE;
		return;
	}
	//ת������
	*m_len_data = class_eton_protocol::pack_data(m_pst, m_data_write, MAX_LEN_PACK);
	if (*m_len_data > 0)
	{
		m_client = it->second;
		m_client_send_available = TRUE;
#ifdef DEBUG_PSPC1
		cout << "������ת�����ݸ��ֻ��ɹ�." << endl;
#endif
	}
	else
	{
		if (CMD_PACK == m_pst->pack_mark)
		{
			this->pspc1_cfm_code_ret(this->pspc1_get_check_code_by_cmd(cmd, FALSE));
			return;
		}
		m_client_send_available = FALSE;
		return;
	}
}
//����ָ���ȡȷ����
unsigned short class_pspc1::pspc1_get_check_code_by_cmd(unsigned short cmd, bool is_ok)
{
	switch (cmd)
	{
	case CMD_APP_GET_PSPC1_STATUS://�ֻ���ȡpspc1�豸����״ָ̬��
		if (is_ok)
			return CFM_APP_GET_PSPC1_STATUS_OK;
		else
			return CFM_APP_GET_PSPC1_STATUS_FAIL;
	case CMD_APP_GET_PSPC1_SET_ARGS://�ֻ���ȡpspc1�豸���ò���ָ��
		if (is_ok)
			return CFM_APP_GET_PSPC1_SET_ARGS_OK;
		else
			return CFM_APP_GET_PSPC1_SET_ARGS_FAIL;
	case CMD_APP_SET_PSPC1_GLDZDL_ARG://�ֻ�����pspc1�豸����������������ָ��
		if (is_ok)
			return CFM_APP_SET_PSPC1_GLDZDL_OK;
		else
			return CFM_APP_SET_PSPC1_GLDZDL_FAIL;
	case CMD_APP_SET_PSPC1_LLBDZDL_ARG://�ֻ�����pspc1�豸©����������������ָ��
		if (is_ok)
			return CFM_APP_SET_PSPC1_LLBDZDL_OK;
		else
			return CFM_APP_SET_PSPC1_LLBDZDL_FAIL;
	case CMD_APP_SET_PSPC1_LLDZDL_ARG://�ֻ�����pspc1�豸©��������������ָ��
		if (is_ok)
			return CFM_APP_SET_PSPC1_LLDZDL_OK;
		else
			return CFM_APP_SET_PSPC1_LLDZDL_FAIL;
	case CMD_APP_SET_PSPC1_GYDZDY_ARG://�ֻ�����pspc1�豸��ѹ������ѹ����ָ��
		if (is_ok)
			return CFM_APP_SET_PSPC1_GYDZDY_OK;
		else
			return CFM_APP_SET_PSPC1_GYDZDY_FAIL;
	case CMD_APP_SET_PSPC1_QYDZDY_ARG://�ֻ�����pspc1�豸Ƿѹ������ѹ����ָ��
		if (is_ok)
			return CFM_APP_SET_PSPC1_QYDZDY_OK;
		else
			return CFM_APP_SET_PSPC1_QYDZDY_FAIL;
	case CMD_APP_SET_PSPC1_GLDKDZSJ_ARG://�ֻ�����pspc1�豸�����Ͽ�����ʱ�����ָ��
		if (is_ok)
			return CFM_APP_SET_PSPC1_GLDKDZSJ_OK;
		else
			return CFM_APP_SET_PSPC1_GLDKDZSJ_FAIL;
	case CMD_APP_SET_PSPC1_GYQYDKDZSJ_ARG://�ֻ�����pspc1�豸��ѹ/Ƿѹ�Ͽ�����ʱ�����ָ��
		if (is_ok)
			return CFM_APP_SET_PSPC1_GYQYDKDZSJ_OK;
		else
			return CFM_APP_SET_PSPC1_GYQYDKDZSJ_FAIL;
	case CMD_APP_SET_PSPC1_ZDCHZSJ_ARG://�ֻ�����pspc1�豸�Զ��غ�բʱ�����ָ��
		if (is_ok)
			return CFM_APP_SET_PSPC1_ZDCHZSJ_OK;
		else
			return CFM_APP_SET_PSPC1_ZDCHZSJ_FAIL;
	case CMD_APP_SET_PSPC1_ZDN_CLEAR://�ֻ�����pspc1�豸�ܵ�������ָ��
		if (is_ok)
			return CFM_APP_SET_PSPC1_ZDN_CLEAR_OK;
		else
			return CFM_APP_SET_PSPC1_ZDN_CLEAR_FAIL;
	case CMD_APP_SET_PSPC1_FL1DN_CLEAR://�ֻ�����pspc1�豸��·1��������ָ��
		if (is_ok)
			return CFM_APP_SET_PSPC1_FL1DN_CLEAR_OK;
		else
			return CFM_APP_SET_PSPC1_FL1DN_CLEAR_FAIL;
	case CMD_APP_SET_PSPC1_FL2DN_CLEAR://�ֻ�����pspc1�豸��·2��������ָ��
		if (is_ok)
			return CFM_APP_SET_PSPC1_FL2DN_CLEAR_OK;
		else
			return CFM_APP_SET_PSPC1_FL2DN_CLEAR_FAIL;
	case CMD_APP_SET_PSPC1_FL3DN_CLEAR://�ֻ�����pspc1�豸��·3��������ָ��
		if (is_ok)
			return CFM_APP_SET_PSPC1_FL3DN_CLEAR_OK;
		else
			return CFM_APP_SET_PSPC1_FL3DN_CLEAR_FAIL;
	case CMD_APP_SET_PSPC1_CLOCK://�ֻ�����pspc1�豸ʱ��У׼ָ��
		if (is_ok)
			return CFM_APP_SET_PSPC1_CLOCK_OK;
		else
			return CFM_APP_SET_PSPC1_CLOCK_FAIL;
	case CMD_APP_SET_PSPC1_DATE://�ֻ�����pspc1�豸����У׼ָ��
		if (is_ok)
			return CFM_APP_SET_PSPC1_DATE_OK;
		else
			return CFM_APP_SET_PSPC1_DATE_FAIL;
	case CMD_APP_SET_PSPC1_WIFI://�ֻ�����pspc1�豸WiFi����ָ��
		if (is_ok)
			return CFM_APP_SET_PSPC1_WIFI_OK;
		else
			return CFM_APP_SET_PSPC1_WIFI_FAIL;
	case CMD_APP_SET_PSPC1_WIFI_STIME://�ֻ�����pspc1�豸WiFi������ʼʱ��ָ��
		if (is_ok)
			return CFM_APP_SET_PSPC1_WIFI_STIME_OK;
		else
			return CFM_APP_SET_PSPC1_WIFI_STIME_FAIL;
	case CMD_APP_SET_PSPC1_WIFI_ETIME://�ֻ�����pspc1�豸WiFi������ֹʱ��ָ��
		if (is_ok)
			return CFM_APP_SET_PSPC1_WIFI_ETIME_OK;
		else
			return CFM_APP_SET_PSPC1_WIFI_ETIME_FAIL;
	case CMD_APP_GET_PSPC1_RECORD://�ֻ���ȡpspc1�豸�ռ���Ϣָ��
		if (is_ok)
			return CFM_APP_GET_PSPC1_RECORD_OK;
		else
			return CFM_APP_GET_PSPC1_RECORD_FAIL;
	case CMD_PSPC1_SEND_ALARM_LD://Pspc1���ֻ�����©��澯ָ��
		if (is_ok)
			return CFM_APP_GET_PSPC1_ALARM_LD_OK;
		else
			return CFM_APP_GET_PSPC1_ALARM_LD_FAIL;
	case CMD_PSPC1_SEND_ALARM_GY://Pspc1���ֻ����͸�ѹ�澯ָ��
		if (is_ok)
			return CFM_APP_GET_PSPC1_ALARM_GY_OK;
		else
			return CFM_APP_GET_PSPC1_ALARM_GY_FAIL;
	case CMD_PSPC1_SEND_ALARM_DY://Pspc1���ֻ����͵�ѹ�澯ָ��
		if (is_ok)
			return CFM_APP_GET_PSPC1_ALARM_DY_OK;
		else
			return CFM_APP_GET_PSPC1_ALARM_DY_FAIL;
	case CMD_PSPC1_SEND_ALARM_GL://Pspc1���ֻ����͹����澯ָ��
		if (is_ok)
			return CFM_APP_GET_PSPC1_ALARM_GL_OK;
		else
			return CFM_APP_GET_PSPC1_ALARM_GL_FAIL;
	case CMD_APP_GET_PSPC1_MNDNSYQK://�ֻ���pspc1���ͻ�ȡĳ�����ʹ�����ָ��
		if (is_ok)
			return CFM_APP_GET_PSPC1_MNDNSYQK_OK;
		else
			return CFM_APP_GET_PSPC1_MNDNSYQK_FAIL;
	default:
		return 0xffff;
	}
}
