#include "../class_pspc1/class_pspc1.h"
#include "../../class_eton_database/class_eton_database.h"
#include "../../class_global/class_global.h"
//标准C++头文件
#include <iostream>
using namespace std;
//构造函数
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
//析构函数
class_pspc1::~class_pspc1()
{

}
//返回确认码
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
//pspc1处理数据
void class_pspc1::pspc1_handle_data()
{
	switch (class_eton_protocol::get_struct_cmd_id(m_pst))
	{
	case CMD_PSPC1_LOGIN://Pspc1登录服务器指令
		this->pspc1_handle_CMD_PSPC1_LOGIN();
		break;
	case CMD_APP_BIND_PSPC1://手机绑定pspc1设备指令
		this->pspc1_handle_CMD_APP_BIND_PSPC1();
		break;
	case CMD_APP_GET_PSPC1_STATUS://手机获取pspc1设备运行状态指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_GET_PSPC1_STATUS);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_GET_PSPC1_STATUS);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_GET_PSPC1_SET_ARGS://手机获取pspc1设备设置参数指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_GET_PSPC1_SET_ARGS);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_GET_PSPC1_SET_ARGS);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_GLDZDL_ARG://手机设置pspc1设备过流动作电流参数指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_GLDZDL_ARG);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_GLDZDL_ARG);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_LLBDZDL_ARG://手机设置pspc1设备漏流不动作电流参数指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_LLBDZDL_ARG);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_LLBDZDL_ARG);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_LLDZDL_ARG://手机设置pspc1设备漏流动作电流参数指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_LLDZDL_ARG);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_LLDZDL_ARG);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_GYDZDY_ARG://手机设置pspc1设备过压动作电压参数指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_GYDZDY_ARG);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_GYDZDY_ARG);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_QYDZDY_ARG://手机设置pspc1设备欠压动作电压参数指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_QYDZDY_ARG);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_QYDZDY_ARG);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_GLDKDZSJ_ARG://手机设置pspc1设备过流断开动作时间参数指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_GLDKDZSJ_ARG);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_GLDKDZSJ_ARG);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_GYQYDKDZSJ_ARG://手机设置pspc1设备过压/欠压断开动作时间参数指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_GYQYDKDZSJ_ARG);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_GYQYDKDZSJ_ARG);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_ZDCHZSJ_ARG://手机设置pspc1设备自动重合闸时间参数指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_ZDCHZSJ_ARG);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_ZDCHZSJ_ARG);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_ZDN_CLEAR://手机设置pspc1设备总电能清零指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_ZDN_CLEAR);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_ZDN_CLEAR);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_FL1DN_CLEAR://手机设置pspc1设备分路1电能清零指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_FL1DN_CLEAR);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_FL1DN_CLEAR);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_FL2DN_CLEAR://手机设置pspc1设备分路2电能清零指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_FL2DN_CLEAR);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_FL2DN_CLEAR);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_FL3DN_CLEAR://手机设置pspc1设备分路3电能清零指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_FL3DN_CLEAR);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_FL3DN_CLEAR);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_CLOCK://手机设置pspc1设备时钟校准指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_CLOCK);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_CLOCK);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_DATE://手机设置pspc1设备日历校准指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_DATE);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_DATE);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_WIFI://手机设置pspc1设备WiFi连接指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_WIFI);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_WIFI);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_WIFI_STIME://手机设置pspc1设备WiFi连接起始时间指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_WIFI_STIME);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_WIFI_STIME);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_SET_PSPC1_WIFI_ETIME://手机设置pspc1设备WiFi连接终止时间指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_SET_PSPC1_WIFI_ETIME);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_SET_PSPC1_WIFI_ETIME);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_GET_PSPC1_RECORD://手机获取pspc1设备日记信息指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_APP_GET_PSPC1_RECORD);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_APP_GET_PSPC1_RECORD);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_PSPC1_SEND_ALARM_LD://Pspc1向手机发送漏电告警指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_PSPC1_SEND_ALARM_LD);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_PSPC1_SEND_ALARM_LD);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_PSPC1_SEND_ALARM_GY://Pspc1向手机发送高压告警指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_PSPC1_SEND_ALARM_GY);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_PSPC1_SEND_ALARM_GY);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_PSPC1_SEND_ALARM_DY://Pspc1向手机发送低压告警指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_PSPC1_SEND_ALARM_DY);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_PSPC1_SEND_ALARM_DY);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_PSPC1_SEND_ALARM_GL://Pspc1向手机发送过流告警指令
		if (CMD_PACK == m_pst->pack_mark)
			this->pspc1_pspc1_data_to_app(CMD_PSPC1_SEND_ALARM_GL);
		else if (CFM_PACK == m_pst->pack_mark)
			this->pspc1_app_data_to_pspc1(CMD_PSPC1_SEND_ALARM_GL);
		else
			m_client_send_available = FALSE;
		break;
	case CMD_APP_GET_PSPC1_MNDNSYQK://手机向pspc1发送获取某年电能使用情况指令
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
//处理pspc1登录服务器指令
void class_pspc1::pspc1_handle_CMD_PSPC1_LOGIN()
{
#ifdef DEBUG_PSPC1
	cout << "pspc1设备登录" << endl;
#endif 
	char dev_id[2 * LEN_DEV_ID_PSPC1 + 1] = { 0 };
	class_eton_protocol::get_struct_dev_id_str(m_pst, LEN_DEV_ID_PSPC1, dev_id);
	if (!class_eton_database::db_check_device_id_exist(dev_id))
	{//数据库未存储该设备ID，进行存储
#ifdef DEBUG_PSPC1
		cout << "新增pspc1设备" << endl;
#endif 
		if (!class_eton_database::db_add_new_device(m_pst->dev_type, m_pst->dev_series, dev_id))
		{//添加设备失败
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
			cout << "pspc1设备登录成功." << endl;
#endif 
		}
		else
		{//帐号已登录，移除之前的登录信息，添加目前的登录信息
			boost::mutex::scoped_lock lock(class_global::g_mutex);
			//移除
			class_global::g_client_map.erase(string(dev_id));
			it->second->set_client_id_available(FALSE);
			//添加
			class_global::g_client_map.insert(U_MAP::value_type(string(dev_id), m_client));
			strcpy(m_client->m_client_id, dev_id);
			m_client->set_client_id_available(TRUE);
#ifdef DEBUG_PSPC1
			cout << "pspc1设备" << dev_id << "已成功登录" << endl;
#endif
		}
	}
	this->pspc1_cfm_code_ret(CFM_PSPC1_LOGIN_OK);
}
//处理手机绑定pspc1设备指令
void class_pspc1::pspc1_handle_CMD_APP_BIND_PSPC1()
{
#ifdef DEBUG_PSPC1
	cout << "处理手机绑定pspc1设备指令." << endl;
#endif 
	char dev_id[2 * LEN_DEV_ID_PSPC1 + 1] = { 0 };
	class_eton_protocol::get_struct_dev_id_str(m_pst, LEN_DEV_ID_PSPC1, dev_id);
	char phone_num[12] = { 0 };
	class_eton_protocol::get_struct_phone_num(m_pst, phone_num);
#if 1
	if (!class_eton_database::db_check_device_id_exist(dev_id))
	{
#ifdef DEBUG_PSPC1
		cout << "pspc1设备" << dev_id << "未注册." << endl;
#endif 
		//添加设备
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
		cout << "pspc1设备" << dev_id << "绑定手机号." << phone_num << "失败." << endl;
#endif
		this->pspc1_cfm_code_ret(CFM_APP_BIND_PSPC1_FAIL);
		return;
	}
#ifdef DEBUG_PSPC1
	cout << "pspc1设备" << dev_id << "绑定手机号." << phone_num << "成功." << endl;
#endif
	this->pspc1_cfm_code_ret(CFM_APP_BIND_PSPC1_OK);
}
//将app发送的数据转发给pspc1
void class_pspc1::pspc1_app_data_to_pspc1(unsigned short cmd)
{
#ifdef DEBUG_PSPC1
	cout << "将app发送的数据转发给pspc1" << endl;
#endif
	char dev_id[2 * LEN_DEV_ID_PSPC1 + 1] = { 0 };
	class_eton_protocol::get_struct_dev_id_str(m_pst, LEN_DEV_ID_PSPC1, dev_id);
	U_MAP::iterator it = class_global::g_client_map.find(string(dev_id));
	if (it == class_global::g_client_map.end())
	{
#ifdef DEBUG_PSPC1
		cout << "pspc1设备" << dev_id  << "未登录."<< endl;
#endif
		if (CMD_PACK == m_pst->pack_mark)
		{
			this->pspc1_cfm_code_ret(this->pspc1_get_check_code_by_cmd(cmd, FALSE));
			return;
		}
		m_client_send_available = FALSE;
		return;
	}
	//转发数据
	*m_len_data = class_eton_protocol::pack_data(m_pst, m_data_write, MAX_LEN_PACK);
	if (*m_len_data > 0)
	{
		m_client = it->second;
		m_client_send_available = TRUE;
#ifdef DEBUG_PSPC1
		cout << "服务器转发数据给pspc1成功." << endl;
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
//将pspc1发送的数据转发给app
void class_pspc1::pspc1_pspc1_data_to_app(unsigned short cmd)
{
#ifdef DEBUG_PSPC1
	cout << "将pspc1发送的数据转发给app" << endl;
#endif
	char phone_num[12] = { 0 };
	class_eton_protocol::get_struct_phone_num(m_pst, phone_num);
	U_MAP::iterator it = class_global::g_client_map.find(string(phone_num));
	if (it == class_global::g_client_map.end())
	{
#ifdef DEBUG_PSPC1
		cout << "手机" << phone_num << "未登录." << endl;
#endif
		if (CMD_PACK == m_pst->pack_mark)
		{
			this->pspc1_cfm_code_ret(this->pspc1_get_check_code_by_cmd(cmd, FALSE));
			return;
		}
		m_client_send_available = FALSE;
		return;
	}
	//转发数据
	*m_len_data = class_eton_protocol::pack_data(m_pst, m_data_write, MAX_LEN_PACK);
	if (*m_len_data > 0)
	{
		m_client = it->second;
		m_client_send_available = TRUE;
#ifdef DEBUG_PSPC1
		cout << "服务器转发数据给手机成功." << endl;
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
//根据指令获取确认码
unsigned short class_pspc1::pspc1_get_check_code_by_cmd(unsigned short cmd, bool is_ok)
{
	switch (cmd)
	{
	case CMD_APP_GET_PSPC1_STATUS://手机获取pspc1设备运行状态指令
		if (is_ok)
			return CFM_APP_GET_PSPC1_STATUS_OK;
		else
			return CFM_APP_GET_PSPC1_STATUS_FAIL;
	case CMD_APP_GET_PSPC1_SET_ARGS://手机获取pspc1设备设置参数指令
		if (is_ok)
			return CFM_APP_GET_PSPC1_SET_ARGS_OK;
		else
			return CFM_APP_GET_PSPC1_SET_ARGS_FAIL;
	case CMD_APP_SET_PSPC1_GLDZDL_ARG://手机设置pspc1设备过流动作电流参数指令
		if (is_ok)
			return CFM_APP_SET_PSPC1_GLDZDL_OK;
		else
			return CFM_APP_SET_PSPC1_GLDZDL_FAIL;
	case CMD_APP_SET_PSPC1_LLBDZDL_ARG://手机设置pspc1设备漏流不动作电流参数指令
		if (is_ok)
			return CFM_APP_SET_PSPC1_LLBDZDL_OK;
		else
			return CFM_APP_SET_PSPC1_LLBDZDL_FAIL;
	case CMD_APP_SET_PSPC1_LLDZDL_ARG://手机设置pspc1设备漏流动作电流参数指令
		if (is_ok)
			return CFM_APP_SET_PSPC1_LLDZDL_OK;
		else
			return CFM_APP_SET_PSPC1_LLDZDL_FAIL;
	case CMD_APP_SET_PSPC1_GYDZDY_ARG://手机设置pspc1设备过压动作电压参数指令
		if (is_ok)
			return CFM_APP_SET_PSPC1_GYDZDY_OK;
		else
			return CFM_APP_SET_PSPC1_GYDZDY_FAIL;
	case CMD_APP_SET_PSPC1_QYDZDY_ARG://手机设置pspc1设备欠压动作电压参数指令
		if (is_ok)
			return CFM_APP_SET_PSPC1_QYDZDY_OK;
		else
			return CFM_APP_SET_PSPC1_QYDZDY_FAIL;
	case CMD_APP_SET_PSPC1_GLDKDZSJ_ARG://手机设置pspc1设备过流断开动作时间参数指令
		if (is_ok)
			return CFM_APP_SET_PSPC1_GLDKDZSJ_OK;
		else
			return CFM_APP_SET_PSPC1_GLDKDZSJ_FAIL;
	case CMD_APP_SET_PSPC1_GYQYDKDZSJ_ARG://手机设置pspc1设备过压/欠压断开动作时间参数指令
		if (is_ok)
			return CFM_APP_SET_PSPC1_GYQYDKDZSJ_OK;
		else
			return CFM_APP_SET_PSPC1_GYQYDKDZSJ_FAIL;
	case CMD_APP_SET_PSPC1_ZDCHZSJ_ARG://手机设置pspc1设备自动重合闸时间参数指令
		if (is_ok)
			return CFM_APP_SET_PSPC1_ZDCHZSJ_OK;
		else
			return CFM_APP_SET_PSPC1_ZDCHZSJ_FAIL;
	case CMD_APP_SET_PSPC1_ZDN_CLEAR://手机设置pspc1设备总电能清零指令
		if (is_ok)
			return CFM_APP_SET_PSPC1_ZDN_CLEAR_OK;
		else
			return CFM_APP_SET_PSPC1_ZDN_CLEAR_FAIL;
	case CMD_APP_SET_PSPC1_FL1DN_CLEAR://手机设置pspc1设备分路1电能清零指令
		if (is_ok)
			return CFM_APP_SET_PSPC1_FL1DN_CLEAR_OK;
		else
			return CFM_APP_SET_PSPC1_FL1DN_CLEAR_FAIL;
	case CMD_APP_SET_PSPC1_FL2DN_CLEAR://手机设置pspc1设备分路2电能清零指令
		if (is_ok)
			return CFM_APP_SET_PSPC1_FL2DN_CLEAR_OK;
		else
			return CFM_APP_SET_PSPC1_FL2DN_CLEAR_FAIL;
	case CMD_APP_SET_PSPC1_FL3DN_CLEAR://手机设置pspc1设备分路3电能清零指令
		if (is_ok)
			return CFM_APP_SET_PSPC1_FL3DN_CLEAR_OK;
		else
			return CFM_APP_SET_PSPC1_FL3DN_CLEAR_FAIL;
	case CMD_APP_SET_PSPC1_CLOCK://手机设置pspc1设备时钟校准指令
		if (is_ok)
			return CFM_APP_SET_PSPC1_CLOCK_OK;
		else
			return CFM_APP_SET_PSPC1_CLOCK_FAIL;
	case CMD_APP_SET_PSPC1_DATE://手机设置pspc1设备日历校准指令
		if (is_ok)
			return CFM_APP_SET_PSPC1_DATE_OK;
		else
			return CFM_APP_SET_PSPC1_DATE_FAIL;
	case CMD_APP_SET_PSPC1_WIFI://手机设置pspc1设备WiFi连接指令
		if (is_ok)
			return CFM_APP_SET_PSPC1_WIFI_OK;
		else
			return CFM_APP_SET_PSPC1_WIFI_FAIL;
	case CMD_APP_SET_PSPC1_WIFI_STIME://手机设置pspc1设备WiFi连接起始时间指令
		if (is_ok)
			return CFM_APP_SET_PSPC1_WIFI_STIME_OK;
		else
			return CFM_APP_SET_PSPC1_WIFI_STIME_FAIL;
	case CMD_APP_SET_PSPC1_WIFI_ETIME://手机设置pspc1设备WiFi连接终止时间指令
		if (is_ok)
			return CFM_APP_SET_PSPC1_WIFI_ETIME_OK;
		else
			return CFM_APP_SET_PSPC1_WIFI_ETIME_FAIL;
	case CMD_APP_GET_PSPC1_RECORD://手机获取pspc1设备日记信息指令
		if (is_ok)
			return CFM_APP_GET_PSPC1_RECORD_OK;
		else
			return CFM_APP_GET_PSPC1_RECORD_FAIL;
	case CMD_PSPC1_SEND_ALARM_LD://Pspc1向手机发送漏电告警指令
		if (is_ok)
			return CFM_APP_GET_PSPC1_ALARM_LD_OK;
		else
			return CFM_APP_GET_PSPC1_ALARM_LD_FAIL;
	case CMD_PSPC1_SEND_ALARM_GY://Pspc1向手机发送高压告警指令
		if (is_ok)
			return CFM_APP_GET_PSPC1_ALARM_GY_OK;
		else
			return CFM_APP_GET_PSPC1_ALARM_GY_FAIL;
	case CMD_PSPC1_SEND_ALARM_DY://Pspc1向手机发送低压告警指令
		if (is_ok)
			return CFM_APP_GET_PSPC1_ALARM_DY_OK;
		else
			return CFM_APP_GET_PSPC1_ALARM_DY_FAIL;
	case CMD_PSPC1_SEND_ALARM_GL://Pspc1向手机发送过流告警指令
		if (is_ok)
			return CFM_APP_GET_PSPC1_ALARM_GL_OK;
		else
			return CFM_APP_GET_PSPC1_ALARM_GL_FAIL;
	case CMD_APP_GET_PSPC1_MNDNSYQK://手机向pspc1发送获取某年电能使用情况指令
		if (is_ok)
			return CFM_APP_GET_PSPC1_MNDNSYQK_OK;
		else
			return CFM_APP_GET_PSPC1_MNDNSYQK_FAIL;
	default:
		return 0xffff;
	}
}
