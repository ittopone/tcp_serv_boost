#ifndef __CLASS_ETON_PROTOCOL_H__
#define __CLASS_ETON_PROTOCOL_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//包头
#define PACK_HEAD 0x7e
//包尾
#define PACK_TAIL 0x7e
//命令包
#define CMD_PACK 0x01
//应答包
#define CFM_PACK 0x03
//数据包
#define DATA_PACK 0x02

//包头长度
#define LEN_PACK_HEAD 1
//包尾长度
#define LEN_PACK_TAIL 1
//手机号码长度
#define LEN_PHONE_NUM 5
//设备类型长度
#define LEN_DEV_TYPE 1
//设备系列长度
#define LEN_DEV_SERIES 1
//设备ID最大长度
#define MAX_LEN_DEV_ID 12
//加密类型长度
#define LEN_CODE_TYPE 1
//流水号长度
#define LEN_SERIAL_NUM 1
//包标识长度
#define LEN_PACK_MARK 1
//指令ID长度
#define LEN_CMD_ID 2
//包长度长度
#define LEN_PACK_LEN 2
//包内容最大长度
#define MAX_LEN_PACK_DATA 256
//校验码长度
#define LEN_CHECK_CODE 2
//转义造成数据量上升的最大值
#define MAX_LEN_ZHUANYI 20
//用户名最大长度
#define MAX_LEN_USER_NAME 20
//用户密码的最大长度
#define MAX_LEN_PASSWORD 20
//用户密码的最小长度
#define MIN_LEN_PASSWORD 10
//确认码长度
#define LEN_CFM_CODE 2

//包标识在包结构体中的偏移量
#define OFF_SET_PACK_MARK (LEN_PHONE_NUM+LEN_DEV_TYPE+LEN_DEV_SERIES+MAX_LEN_DEV_ID+LEN_CODE_TYPE+LEN_SERIAL_NUM)
//包标识与包内容之间的偏移量
#define OFF_SET_MARK_TO_DATA (LEN_CMD_ID + LEN_PACK_LEN)
//包内容的偏移量
#define OFF_SET_PACK_DATA (OFF_SET_PACK_MARK+LEN_PACK_MARK+OFF_SET_MARK_TO_DATA)
//最小的封包长度
#define MIN_LEN_PACK (LEN_PACK_HEAD+OFF_SET_PACK_DATA+LEN_CHECK_CODE+LEN_PACK_TAIL)
//最大封包长度
#define MAX_LEN_PACK (MIN_LEN_PACK+MAX_LEN_PACK_DATA+MAX_LEN_ZHUANYI)
//包结构体的长度
#define LEN_PROTOCOL_STRUCT sizeof(protocol_struct)
//服务器接收客户端数据的最大缓冲区
#define MAX_LEN_BUFFER (2 * MAX_LEN_PACK)

//包结构体
typedef struct
{
	//手机号
	char phone_num[LEN_PHONE_NUM];
	//设备类型
	char dev_type;
	//设备系列号
	char dev_series;
	//设备ID
	char dev_id[MAX_LEN_DEV_ID];
	//加密类型，当设置成0x00时，表示不加密
	char code_type;
	//流水号
	char serial_num;
	//包标识
	char pack_mark;
	//指令ID
	char cmd_id[LEN_CMD_ID];
	//包长度
	char pack_len[LEN_PACK_LEN];
	//包内容
	char pack_data[MAX_LEN_PACK_DATA];
	//校验码
	char check_code[LEN_CHECK_CODE];
}protocol_struct, *protocol_pstruct;
//类定义
class class_eton_protocol
{
public:
	//构造函数
	class_eton_protocol();
	//析构函数
	~class_eton_protocol();
	//crc16校验码计算方法
	//pdata：要进行校验的数据
	//data_len：要进行校验的数据的长度
	//pcrc：返回的校验码
	//返回值：错误返回-1，正确返回校验码
	static int get_crc16(char *pdata, size_t data_len, char * pcrc);
	//封包：填充结构体中的校验码，包内容加密，转义，得到要发送的数据及长度
	//pst：包结构体，包含要发送的信息
	//pdata_packed：得到要发送的数据
	//len_data_packed：pdata_packed定义的长度
	//返回值：-1参数错误，-2填充校验码出错，-3封包超出定义的最大长度，>0返回要发送的数据的长度
	static int pack_data(protocol_pstruct pst, char * pdata_packed, size_t len_data_packed);
	//解包：转义还原，包内容解密，验证校验码，得到包含要接收的信息的包结构体
	//pst：包结构体，包含要接受的信息
	//pdata_need_unpacked：需要进行解包的数据
	//len_data_need_unpacked：要进行解包的数据的长度
	//返回值：-1参数错误，-2包头或包尾丢失,-3超出结构体长度，-4转义出错，-5验证校验码错误，>0解包后数据长度
	static int unpack_data(protocol_pstruct pst, char * pdata_need_unpacked, size_t len_data_need_unpacked);
	//设置结构体中的指令ID
	//pst：包结构体
	//cmd_id：要设置的指令ID
	//返回值：-1参数错误，>0成功
	static int set_struct_cmd_id(protocol_pstruct pst, unsigned int cmd_id);
	//获取结构体中的指令ID
	//pst：包结构体
	//返回值：指令ID
	static unsigned int get_struct_cmd_id(protocol_pstruct pst);
	//设置结构体中的包长度
	//pst：包结构体
	//pack_len：包长度
	//返回值：-1参数错误，>0成功
	static int set_struct_pack_len(protocol_pstruct pst, size_t pack_len);
	//获取结构体中的包长度
	//pst：包结构体
	//返回值：包长度
	static size_t get_struct_pack_len(protocol_pstruct pst);
	//设置结构体中的包内容与包长度
	//Pack_data：包内容
	//pack_len：包长度
	//返回值：-1参数错误,-2pack_len超出最大长度，>0成功
	static int set_struct_pack_data_len(protocol_pstruct pst, char * pack_data, size_t pack_len);
	//设置结构体中的手机号
	//pst：包结构体
	//phone_num：手机号（字符串）
	//返回值：-1参数错误，>0成功
	static int set_struct_phone_num(protocol_pstruct pst, char * phone_num);
	//获取结构体中的手机号
	//pst：包结构体
	//phone_num：手机号（字符串）
	//返回值：-1参数错误，>0成功
	static int get_struct_phone_num(protocol_pstruct pst, char * phone_num);
	//从包内容中获取用户名与密码（用于手机app注册服务器）
	//pst：包结构体
	//username：放置从pst中获取的用户名
	//password：放置从pst中获取的密码
	//返回值：-1参数错误，-2包内容格式错误，-3超出用户名最大长度，-4密码长度错误，>0成功
	static int get_uname_pswd_from_pack_data(protocol_pstruct pst, char * username, char * password);
	//从包内容中取出密码（用于手机app登录服务器或修改密码）
	//pst：包结构体
	//password：放置从包内容中取出的密码
	//返回值：-1参数错误，-2密码长度错误，>0成功
	static int get_pswd_from_pack_data(protocol_pstruct pst, char * password);
	//从包内容中取出用户名（用于手机app更改用户名）
	//pst：包结构体
	//username：放置从包内容中取出的用户名
	//返回值：-1参数错误，-2用户名长度错误，>0成功
	static int get_uname_from_pack_data(protocol_pstruct pst, char * username);
	//设置包结构体中的确认码
	//pst：包结构体
	//cfm_code：确认码
	//返回值：-1参数错误，>0成功
	static int set_struct_cfm_code(protocol_pstruct pst,unsigned short cfm_code);
	//设置包结构体中的确认码和数据
	//pst：包结构体
	//cfm_code：确认码
	//data：数据
	//len：数据长度
	//返回值：-1参数错误，>0成功
	static int set_struct_cfm_code_and_data(protocol_pstruct pst, unsigned short cfm_code, char * data, size_t len);
	//将设备ID转换成字符串
	//pst：包结构体
	//len_dev_id：设备ID的长度
	//dev_id_str：转换得到的设备ID字符串
	//返回值：-1参数错误，>0成功
	static int get_struct_dev_id_str(protocol_pstruct pst, const size_t len_dev_id, char * dev_id_str);
};

#endif