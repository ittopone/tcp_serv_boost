#ifndef __CLASS_PSPC_H__
#define __CLASS_PSPC_H__
//boost库头文件
#include <boost/shared_ptr.hpp>
//自定义头文件
#include "../../class_eton_protocol/class_eton_protocol.h"
#include "../../class_eton_client/class_eton_client.h"
#include "define_pspc.h"
//类定义
class class_pspc
{
public:
	char * m_data_write;
	bool & m_client_send_available;
	size_t * m_len_data;
	spt_client & m_client;
	protocol_pstruct m_pst;
	//构造函数
	class_pspc(char * pdata, size_t * len_data, bool & client_send_available, spt_client & client, protocol_pstruct pst);
	//析构函数
	~class_pspc();
	//返回确认码
	int pspc_cfm_code_ret(unsigned int cfm_code);
	//返回确认码和数据
	int pspc_cfm_code_and_data_ret(unsigned int cfm_code, char * data, size_t len);
	//pspc处理数据
	void pspc_handle_data();
	//pspc处理APP获取pspc设备列表指令
	void pspc_handle_CMD_APP_GET_PSPC_LIST();
};
//重命名
typedef boost::shared_ptr<class_pspc> spt_pspc;
#endif