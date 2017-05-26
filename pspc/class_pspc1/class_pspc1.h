#ifndef __CLASS_PSPC1_H__
#define __CLASS_PSPC1_H__
//boost库头文件
#include <boost/shared_ptr.hpp>
//自定义头文件
#include "../class_pspc/class_pspc.h"
#include "define_pspc1.h"
//类定义
class class_pspc1
{
public:
	char * m_data_write;
	bool & m_client_send_available;
	size_t * m_len_data;
	spt_client & m_client;
	protocol_pstruct m_pst;
	//构造函数
	class_pspc1(char * pdata, size_t * len_data, bool & client_send_available, spt_client & client, protocol_pstruct pst);
	//析构函数
	~class_pspc1();
	//返回确认码
	int pspc1_cfm_code_ret(unsigned int cfm_code);
	//pspc1处理数据
	void pspc1_handle_data();
	//处理pspc1登录服务器指令
	void pspc1_handle_CMD_PSPC1_LOGIN();
	//处理手机绑定pspc1设备指令
	void pspc1_handle_CMD_APP_BIND_PSPC1();
	//将app发送的数据转发给pspc1
	void pspc1_app_data_to_pspc1(unsigned short cmd);
	//将pspc1发送的数据转发给app
	void pspc1_pspc1_data_to_app(unsigned short cmd);
	//根据指令获取确认码
	unsigned short pspc1_get_check_code_by_cmd(unsigned short cmd,bool is_ok);
};
//重命名
typedef boost::shared_ptr<class_pspc1> spt_pspc1;
#endif