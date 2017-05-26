#include "class_pack_handle.h"
#include "define_pack_handle.h"
#include "../pspc/class_pspc/class_pspc.h"
#include "../pspc/class_pspc1/class_pspc1.h"
#include "../class_eton_database/class_eton_database.h"
#include "../class_global/class_global.h"
//��׼C++ͷ�ļ�
#include <iostream>
using namespace std;
//���캯��
class_pack_handle::class_pack_handle()
	:m_len_data(0)
{
	m_client_send_available = FALSE;
	memset(m_data_write, 0, MAX_LEN_PACK);
	memset(&m_st, 0, LEN_PROTOCOL_STRUCT);
}
//��������
class_pack_handle::~class_pack_handle()
{

}
//������
void class_pack_handle::handle_pack(char * data_read, size_t len_data, spt_client client)
{
	m_client = client;

	//����������
	if (2 == len_data)
	{
#ifdef DEBUG_PACK_HANDLE
		cout << "�յ�������." << endl;
#endif
		handle_heartbeat();
	}	
	else
	{
		int ret = class_eton_protocol::unpack_data(&m_st, data_read, len_data);
		if (ret > 0)
		{
			switch (class_eton_protocol::get_struct_cmd_id(&m_st))
			{
			case CMD_APP_REGISTER://�ֻ�appע�������ָ��
				handle_app_register();
				break;
			case CMD_APP_LOGIN://�ֻ�app��¼������ָ��
				handle_app_login();
				break;
			case CMD_APP_MODIFY_UNAME://�ֻ��޸��û��ǳ�ָ��
				handle_app_modify_uname();
				break;
			case CMD_APP_MODIFY_PSWD://�ֻ��޸��û�����ָ��
				handle_app_modify_pswd();
				break;
			default:
				handle_device_type();
				break;
			}
		}
		else
		{//������������
#ifdef DEBUG_PACK_HANDLE
			cout << "����������.ret:" << ret << endl;
#endif
			m_client_send_available = FALSE;
		}
	}
}
//����������
void class_pack_handle::handle_heartbeat()
{
#ifdef DEBUG_PACK_HANDLE
	cout << "����������." << endl;
#endif
	m_data_write[0] = PACK_HEAD;
	m_data_write[1] = PACK_TAIL;
	m_len_data = 2;
	m_client_send_available = TRUE;
}
//�豸���ʹ���
void class_pack_handle::handle_device_type()
{
	switch (m_st.dev_type)
	{
	case DEV_TYPE_PSPC://pspc�豸����
		this->handle_device_type_pspc();
		break;
	default:
		m_client_send_available = FALSE;
		break;
	}
}
//pspc�豸����
void class_pack_handle::handle_device_type_pspc()
{
#ifdef  DEBUG_PACK_HANDLE
	cout << "pspc�豸����" << endl;
#endif
	if (CMD_APP_GET_PSPC_LIST == class_eton_protocol::get_struct_cmd_id(&m_st))
	{//app��ȡpspc�豸�б�
		spt_pspc pspc(new class_pspc(m_data_write, &m_len_data, m_client_send_available, m_client, &m_st));
	}
	else
	{
		switch (m_st.dev_series)
		{
		case DEV_SERIES_PSPC1://pspc1�豸
			handle_device_series_pspc1();
			break;
		default:
			break;
		}
	}
}
//pspc1�豸
void class_pack_handle::handle_device_series_pspc1()
{
#ifdef  DEBUG_PACK_HANDLE
	cout << "pspc1�豸" << endl;
#endif
	spt_pspc1 pspc1(new class_pspc1(m_data_write, &m_len_data, m_client_send_available, m_client, &m_st));
}
//�ֻ�appע�������
void class_pack_handle::handle_app_register()
{
#ifdef DEBUG_PACK_HANDLE
	cout << "�ֻ�appע�������." << endl;
#endif
	char phone_num[12] = {0};
	class_eton_protocol::get_struct_phone_num(&m_st, phone_num);
	if (class_eton_database::db_check_user_phone_num_exist(phone_num))
	{//��ע��
		this->handle_cfm_code_ret(CFM_APP_REGISTER_EXIST);
#ifdef DEBUG_PACK_HANDLE
		cout << "�ֻ���" << phone_num << "��ע��" << endl;
#endif
	}
	else
	{//����ע��
		char uname[MAX_LEN_USER_NAME + 1] = { 0 };
		char pswd[MAX_LEN_PASSWORD + 1] = { 0 };
		int ret = 0;
		ret = class_eton_protocol::get_uname_pswd_from_pack_data(&m_st, uname, pswd);
		if (ret < 0)
		{//ע��ʧ��
			this->handle_cfm_code_ret(CFM_APP_REGISTER_FAIL);
#ifdef DEBUG_PACK_HANDLE
			cout << "�ֻ���" << phone_num << "ע��ʧ��" << endl;
#endif
		}
		else
		{//ע��ɹ�
			//���û�ע����Ϣ��ӵ����ݿ�
			if (class_eton_database::db_add_new_user(phone_num, uname, pswd))
			{
				this->handle_cfm_code_ret(CFM_APP_REGISTER_OK);
#ifdef DEBUG_PACK_HANDLE
				cout << "�ֻ���" << phone_num << "ע��ɹ�" << endl;
#endif
#if 0
				strncpy(m_client->m_client_id, phone_num,11);				
				class_global::g_client_map.insert(U_MAP::value_type(phone_num, m_client));
				m_client->set_client_id_available(TRUE);
#endif
			}
			else
			{
				this->handle_cfm_code_ret(CFM_APP_REGISTER_FAIL);
#ifdef DEBUG_PACK_HANDLE
				cout << "�ֻ���" << phone_num << "ע��ʧ��" << endl;
#endif
			}
		}
	}
}
//�ֻ�app��¼������
void class_pack_handle::handle_app_login()
{
#ifdef DEBUG_PACK_HANDLE
	cout << "�ֻ�app��¼������." << endl;
#endif
	char phone_num[12] = { 0 };
	char password[MAX_LEN_PASSWORD + 1] = { 0 };
	class_eton_protocol::get_struct_phone_num(&m_st, phone_num);
	class_eton_protocol::get_pswd_from_pack_data(&m_st, password);
	if (class_eton_database::db_check_user_phone_num_exist(phone_num))
	{//�ֻ��Ŵ���
		if (class_eton_database::db_check_user_password_exist(phone_num, password))
		{//��¼�ɹ�
#ifdef DEBUG_PACK_HANDLE
			cout << "�ֻ���" << phone_num << "��¼�ɹ�" << endl;
#endif				
			if (!m_client->get_client_id_available())
			{
				boost::mutex::scoped_lock lock(class_global::g_mutex);
				U_MAP::iterator it = class_global::g_client_map.find(string(phone_num));
				if (it == class_global::g_client_map.end())
				{
					class_global::g_client_map.insert(U_MAP::value_type(string(phone_num), m_client));
					strcpy(m_client->m_client_id, phone_num);
					m_client->set_client_id_available(TRUE);
				}
				else
				{//�ʺ��ѵ�¼���Ƴ�֮ǰ�ĵ�¼��Ϣ�����Ŀǰ�ĵ�¼��Ϣ
					boost::mutex::scoped_lock lock(class_global::g_mutex);
					//�Ƴ�
					class_global::g_client_map.erase(string(phone_num));
					it->second->set_client_id_available(FALSE);
					//���
					class_global::g_client_map.insert(U_MAP::value_type(string(phone_num), m_client));
					strcpy(m_client->m_client_id, phone_num);
					m_client->set_client_id_available(TRUE);
#ifdef DEBUG_PACK_HANDLE
					cout << "�ֻ���" << phone_num << "�ѳɹ���¼" << endl;
#endif
				}
			}
			//�����û��ǳƸ��ͻ���
			char uname[MAX_LEN_USER_NAME + 1] = { 0 };
			class_eton_database::db_get_user_name(phone_num, uname);
			handle_cfm_code_and_data_ret(CFM_APP_LOGIN_OK, uname, strlen(uname));
		}
		else
		{//��¼ʧ��
			handle_cfm_code_ret(CFM_APP_LOGIN_FAIL);
#ifdef DEBUG_PACK_HANDLE
			cout << "�ֻ���" << phone_num << "��¼ʧ��" << endl;
#endif
		}
	}
	else
	{//�ֻ��Ų�����
		handle_cfm_code_ret(CFM_APP_NOT_REGISTER);
#ifdef DEBUG_PACK_HANDLE
		cout << "�ֻ���" << phone_num << "δע��" << endl;
#endif
	}	
}
//�ֻ��޸��û��ǳ�
void class_pack_handle::handle_app_modify_uname()
{
#ifdef DEBUG_PACK_HANDLE
	cout << "�ֻ��޸��û��ǳ�." << endl;
#endif
	char phone_num[12] = { 0 };
	class_eton_protocol::get_struct_phone_num(&m_st, phone_num);
	char uname[MAX_LEN_USER_NAME + 1] = { 0 };
	class_eton_protocol::get_uname_from_pack_data(&m_st, uname);
	if (class_eton_database::db_modify_user_name(phone_num, uname))
	{//�޸��ǳƳɹ�
		handle_cfm_code_ret(CFM_APP_MODIFY_UNAME_OK);
#ifdef DEBUG_PACK_HANDLE
		cout << "�ֻ���" << phone_num << "�޸��ǳƳɹ�" << endl;
#endif
	}
	else
	{//�޸��ǳ�ʧ��
		handle_cfm_code_ret(CFM_APP_MODIFY_UNAME_FAIL);
#ifdef DEBUG_PACK_HANDLE
		cout << "�ֻ���" << phone_num << "�޸��ǳ�ʧ��" << endl;
#endif
	}
}
//�ֻ��޸��û�����ָ��
void class_pack_handle::handle_app_modify_pswd()
{
#ifdef DEBUG_PACK_HANDLE
	cout << "�ֻ��޸��û�����." << endl;
#endif
	char phone_num[12] = { 0 };
	char password[MAX_LEN_PASSWORD + 1] = { 0 };
	class_eton_protocol::get_struct_phone_num(&m_st, phone_num);
	class_eton_protocol::get_pswd_from_pack_data(&m_st, password);
	if (class_eton_database::db_modify_user_password(phone_num, password))
	{//�޸�����ɹ�
		handle_cfm_code_ret(CFM_APP_MODIFY_PSWD_OK);
#ifdef DEBUG_PACK_HANDLE
		cout << "�ֻ���" << phone_num << "�޸�����ɹ�" << endl;
#endif
	}
	else
	{//�޸�����ʧ��
		handle_cfm_code_ret(CFM_APP_MODIFY_PSWD_FAIL);
#ifdef DEBUG_PACK_HANDLE
		cout << "�ֻ���" << phone_num << "�޸�����ʧ��" << endl;
#endif
	}
}
//����ȷ����
int class_pack_handle::handle_cfm_code_ret(unsigned int cfm_code)
{
	m_st.pack_mark = CFM_PACK;
	int ret = 0;
	ret = class_eton_protocol::set_struct_pack_len(&m_st, LEN_CFM_CODE);
	if (ret < 0)
		goto ret_error;
	ret = class_eton_protocol::set_struct_cfm_code(&m_st, cfm_code);
	if (ret < 0)
		goto ret_error;
	m_len_data = class_eton_protocol::pack_data(&m_st, m_data_write, MAX_LEN_PACK);
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
int class_pack_handle::handle_cfm_code_and_data_ret(unsigned int cfm_code, char * data, size_t len)
{
	m_st.pack_mark = CFM_PACK;
	int ret = 0;
	ret = class_eton_protocol::set_struct_pack_len(&m_st, LEN_CFM_CODE + len);
	if (ret < 0)
		goto ret_error;
	ret = class_eton_protocol::set_struct_cfm_code_and_data(&m_st, cfm_code, data, len);
	if (ret < 0)
		goto ret_error;
	m_len_data = class_eton_protocol::pack_data(&m_st, m_data_write, MAX_LEN_PACK);
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