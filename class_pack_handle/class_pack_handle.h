#ifndef __CLASS_PACK_HANDLE_H__
#define __CLASS_PACK_HANDLE_H__
//boost库头文件
#include <boost/shared_ptr.hpp>
//自定义头文件
#include "../class_eton_client/class_eton_client.h"
#include "../class_eton_protocol/class_eton_protocol.h"
#include "../class_eton_client/class_eton_client.h"
//类定义
class class_pack_handle
{
public:
	char m_data_write[MAX_LEN_PACK];
	bool m_client_send_available;
	size_t m_len_data;
	spt_client m_client;
	protocol_struct m_st;
	//构造函数
	class_pack_handle();
	//析构函数
	~class_pack_handle();
	//包处理
	void handle_pack(char * data_read, size_t len_data, spt_client client);
	//心跳包处理
	void handle_heartbeat();
	//手机app注册服务器
	void handle_app_register();
	//手机app登录服务器
	void handle_app_login();
	//手机修改用户昵称
	void handle_app_modify_uname();
	//手机修改用户密码指令
	void handle_app_modify_pswd();
	//返回确认码
	int handle_cfm_code_ret(unsigned int cfm_code);
	//返回确认码和数据
	int handle_cfm_code_and_data_ret(unsigned int cfm_code, char * data, size_t len);
	//设备类型处理
	void handle_device_type();	
	//pspc设备
	void handle_device_type_pspc();
	//pspc1设备
	void handle_device_series_pspc1();
};
//重命名
typedef boost::shared_ptr<class_pack_handle> spt_pack_handle;
#endif