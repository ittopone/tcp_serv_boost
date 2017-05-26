#include "../class_eton_protocol/class_eton_protocol.h"
//自定义头文件
#include "../debug_switch/debug.h"
#include "../pspc/class_pspc/define_pspc.h"
//构造函数
class_eton_protocol::class_eton_protocol()
{
}
//析构函数
class_eton_protocol::~class_eton_protocol()
{
}
//crc16校验码计算方法
//pdata：要进行校验的数据
//data_len：要进行校验的数据的长度
//pcrc：返回的校验码
//返回值：错误返回-1，正确返回校验码
int class_eton_protocol::get_crc16(char *pdata, size_t data_len, char *pcrc)
{
	size_t i = 0;
	char j = 0;
	unsigned short CRC = 0xffff;
	unsigned short POLYNOMIAL = 0xa001;

	if ((NULL == pdata) || (NULL == pcrc))
		return -1;
	if (0 == data_len)
		return -1;
#ifdef DEBUG_PROTOCOL
	printf("get following data crc:\r\n");
#endif	
	for (i = 0; i < data_len; i++)
	{
		CRC ^= (unsigned char)pdata[i];
#ifdef DEBUG_PROTOCOL
		printf("%02x ", ((unsigned char)pdata[i]) & 0xff);
#endif
		for (j = 0; j < 8; j++)
		{
			if ((CRC & 0x0001) != 0)
			{
				CRC >>= 1;
				CRC ^= POLYNOMIAL;
			}
			else
				CRC >>= 1;
		}
	}
	pcrc[0] = (unsigned char)((CRC >> 8) & 0xff);
	pcrc[1] = (unsigned char)(CRC & 0xff);
#ifdef DEBUG_PROTOCOL
	printf("\r\nget crc:\r\n");
	printf("high byte:%02x\r\n", ((unsigned char)pcrc[0]) & 0xff);
	printf("low byte:%02x\r\n", ((unsigned char)pcrc[1]) & 0xff);
#endif
	return CRC;
}
//封包：填充结构体中的校验码，包内容加密，转义，得到要发送的数据及长度
//pst：包结构体，包含要发送的信息
//pdata_packed：得到要发送的数据
//len_data_packed：pdata_packed定义的长度
//返回值：-1参数错误，-2填充校验码出错，-3封包超出定义的最大长度，>0返回要发送的数据的长度
int class_eton_protocol::pack_data(protocol_pstruct pst, char * pdata_packed, size_t len_data_packed)
{
	size_t i = 0;
	size_t index = 0;
	size_t pack_len = ((pst->pack_len[0]) << 8) + (pst->pack_len[1]);
	//参数检验
	if ((NULL == pst) || (NULL == pdata_packed) || (len_data_packed < MIN_LEN_PACK))
		return -1;
	//填充校验码
	if (-1 == get_crc16((char*)pst, (OFF_SET_PACK_DATA + pack_len), pst->check_code))
		return -2;
	//打印调试信息
#ifdef DEBUG_PROTOCOL
	printf("before pack:\r\n");
	for (i = 0; i < (OFF_SET_PACK_DATA + pack_len); i++)
		printf("%02x ", *((char*)pst + i) & 0xff);
	for (i = 0; i < LEN_CHECK_CODE; i++)
		printf("%02x ", pst->check_code[i] & 0xff);
	printf("\r\n");
#endif
	//包内容加密
	if (0x00 != pst->code_type)
	{//进行加密

	}
	//填充包头
	pdata_packed[index++] = PACK_HEAD;
	//转义处理
	for (i = 0; i < (OFF_SET_PACK_DATA + pack_len); i++)
	{
		//封包是否超出定义的最大长度
		if ((index + 1) == len_data_packed)
			return -3;
		if (PACK_HEAD == *((char*)pst + i))
		{
			pdata_packed[index++] = 0x7d;
			pdata_packed[index++] = 0x02;
		}
		else if (0x7d == *((char*)pst + i))
		{
			pdata_packed[index++] = 0x7d;
			pdata_packed[index++] = 0x01;
		}
		else
			pdata_packed[index++] = *((char*)pst + i);
	}
	for (i = 0; i < LEN_CHECK_CODE; i++)
	{
		//封包是否超出定义的最大长度
		if ((index + 1) == len_data_packed)
			return -3;
		if (PACK_HEAD == pst->check_code[i])
		{
			pdata_packed[index++] = 0x7d;
			pdata_packed[index++] = 0x02;
		}
		else if (0x7d == pst->check_code[i])
		{
			pdata_packed[index++] = 0x7d;
			pdata_packed[index++] = 0x01;
		}
		else
			pdata_packed[index++] = pst->check_code[i];
	}
	//封包是否超出定义的最大长度
	if ((index + 1) == len_data_packed)
		return -3;
	//填充包尾
	pdata_packed[index++] = PACK_TAIL;
	//打印调试信息
#ifdef DEBUG_PROTOCOL
	printf("after pack:\r\n");
	for (i = 0; i < index; i++)
		printf("%02x ", pdata_packed[i] & 0xff);
	printf("\r\n");
#endif
	//返回封包数据长度
	return index;
}
//解包：转义还原，包内容解密，验证校验码，得到包含要接收的信息的包结构体
//pst：包结构体，包含要接受的信息
//pdata_need_unpacked：需要进行解包的数据
//len_data_need_unpacked：要进行解包的数据的长度
//返回值：-1参数错误，-2包头或包尾丢失,-3超出结构体长度，-4转义出错，-5验证校验码错误，>0解包后数据长度
int class_eton_protocol::unpack_data(protocol_pstruct pst, char *pdata_need_unpacked, size_t len_data_need_unpacked)
{
	size_t i = 0;
	size_t index = 0;
	size_t pack_len = 0;
	char crc[LEN_CHECK_CODE] = { 0 };
	char temp[LEN_PROTOCOL_STRUCT] = { 0 };
	//参数检验
	if ((NULL == pst) || (NULL == pdata_need_unpacked) || (len_data_need_unpacked < MIN_LEN_PACK) || (len_data_need_unpacked > MAX_LEN_PACK))
		return -1;
	if ((PACK_HEAD != pdata_need_unpacked[0]) || (PACK_TAIL != pdata_need_unpacked[len_data_need_unpacked - 1]))
		return -2;
	//打印调试信息
#ifdef DEBUG_PROTOCOL
	printf("before unpack:\r\n");
	for (i = 0; i < len_data_need_unpacked; i++)
		printf("%02x ", pdata_need_unpacked[i] & 0xff);
	printf("\r\n");
#endif
	//转义还原
	for (i = 1; i < (len_data_need_unpacked - 1); i++)
	{
		if ((index + 1) > LEN_PROTOCOL_STRUCT)
			return -3;
		if (0x7d == pdata_need_unpacked[i])
		{
			if (0x02 == pdata_need_unpacked[i + 1])
			{
				temp[index++] = PACK_HEAD;
				i++;
			}
			else if (0x01 == pdata_need_unpacked[i + 1])
			{
				temp[index++] = 0x7d;
				i++;
			}
			else
				return -4;
		}
		else
			temp[index++] = pdata_need_unpacked[i];
	}
	//填充pst结构体
	for (i = 0; i < (index - LEN_CHECK_CODE); i++)
		*((char*)pst + i) = temp[i];
	for (i = 0; i < LEN_CHECK_CODE; i++)
		pst->check_code[i] = temp[index - LEN_CHECK_CODE + i];
	//包内容解密
	if (0x00 != pst->code_type)
	{

	}
	//验证校验码
	pack_len = ((pst->pack_len[0]) << 8) + (pst->pack_len[1]);
	if (-1 == get_crc16((char*)pst, (OFF_SET_PACK_DATA + pack_len), crc))
		return -5;
	for (i = 0; i < LEN_CHECK_CODE; i++)
	{
		if (pst->check_code[i] != crc[i])
			return -5;
	}
	//打印调试信息
#ifdef DEBUG_PROTOCOL
	printf("after unpack:\r\n");
	for (i = 0; i < (OFF_SET_PACK_DATA + pack_len); i++)
		printf("%02x ", *((char*)pst + i) & 0xff);
	for (i = 0; i < LEN_CHECK_CODE; i++)
		printf("%02x ", pst->check_code[i] & 0xff);
	printf("\r\n");
#endif
	//返回解包后的数据长度
	return (index + LEN_PACK_HEAD + LEN_PACK_TAIL);
}
//设置结构体中的指令ID
//pst：包结构体
//cmd_id：要设置的指令ID
//返回值：-1参数错误，>0成功
int class_eton_protocol::set_struct_cmd_id(protocol_pstruct pst, unsigned int cmd_id)
{
	if (NULL == pst)
		return -1;
	pst->cmd_id[0] = (cmd_id >> 8) & 0xff;
	pst->cmd_id[1] = cmd_id & 0xff;

	return 1;
}
//获取结构体中的指令ID
//pst：包结构体
//返回值：指令ID
unsigned int class_eton_protocol::get_struct_cmd_id(protocol_pstruct pst)
{
	unsigned int cmd_id = 0;
	cmd_id = ((pst->cmd_id[0]) << 8) + pst->cmd_id[1];
	return cmd_id;
}
//设置结构体中的包长度
//pst：包结构体
//pack_len：包长度
//返回值：-1参数错误，>0成功
int class_eton_protocol::set_struct_pack_len(protocol_pstruct pst, size_t pack_len)
{
	if (NULL == pst)
		return -1;
	pst->pack_len[0] = (pack_len >> 8) & 0xff;
	pst->pack_len[1] = pack_len & 0xff;
	return 1;
}
//获取结构体中的包长度
//pst：包结构体
//返回值：包长度
size_t class_eton_protocol::get_struct_pack_len(protocol_pstruct pst)
{
	size_t pack_len = 0;
	pack_len = ((pst->pack_len[0]) << 8) + pst->pack_len[1];
	return pack_len;
}
//设置结构体中的包内容与包长度
//Pack_data：包内容
//pack_len：包长度
//返回值：-1参数错误,-2pack_len超出最大长度，>0成功
int class_eton_protocol::set_struct_pack_data_len(protocol_pstruct pst, char * pack_data, size_t pack_len)
{
	if ((NULL == pst) || (NULL == pack_data))
		return -1;
	if (pack_len > MAX_LEN_PACK_DATA)
		return -2;
	size_t i = 0;
	set_struct_pack_len(pst, pack_len);
	for (i = 0; i < pack_len; i++)
		pst->pack_data[i] = pack_data[i];

	return 1;
}
//设置结构体中的手机号
//pst：包结构体
//phone_num：手机号（字符串）
//返回值：-1参数错误，>0成功
int class_eton_protocol::set_struct_phone_num(protocol_pstruct pst, char * phone_num)
{
	if ((NULL == pst) || (NULL == phone_num))
		return -1;
	size_t i = 0;
	char temp[5] = { 0 };
	if (11 != strlen(phone_num))
		return -1;
	for (i = 0; i < 3; i++)
	{
		temp[i] = phone_num[i];
		if (2 == i)
		{
			temp[i + 1] = '\0';
			pst->phone_num[0] = atoi(temp) & 0xff;
		}
	}
	for (i = 3; i < 7; i++)
	{
		temp[i - 3] = phone_num[i];
		if (6 == i)
		{
			temp[i - 3 + 1] = '\0';
			pst->phone_num[1] = (atoi(temp) >> 8) & 0xff;
			pst->phone_num[2] = atoi(temp) & 0xff;
		}
	}
	for (i = 7; i < 11; i++)
	{
		temp[i - 7] = phone_num[i];
		if (10 == i)
		{
			temp[i - 7 + 1] = '\0';
			pst->phone_num[3] = (atoi(temp) >> 8) & 0xff;
			pst->phone_num[4] = atoi(temp) & 0xff;
		}
	}
	return 1;
}
//获取结构体中的手机号
//pst：包结构体
//phone_num：手机号（字符串）
//返回值：-1参数错误，>0成功
int class_eton_protocol::get_struct_phone_num(protocol_pstruct pst, char * phone_num)
{
	if ((NULL == pst) || (NULL == phone_num))
		return -1;
	unsigned char duan1 = 0;
	unsigned short duan2 = 0;
	unsigned short duan3 = 0;
	duan1 = pst->phone_num[0];
	duan2 = (((unsigned char)(pst->phone_num[1])) << 8) + ((unsigned char)(pst->phone_num[2]));
	duan3 = (((unsigned char)(pst->phone_num[3])) << 8) + ((unsigned char)(pst->phone_num[4]));
	sprintf(phone_num, "%03u%04u%04u", duan1, duan2, duan3);
	return 1;
}
//从包内容中获取用户名与密码（用于手机app注册服务器）
//pst：包结构体
//username：放置从pst中获取的用户名
//password：放置从pst中获取的密码
//返回值：-1参数错误，-2包内容格式错误，-3超出用户名最大长度，-4密码长度错误，>0成功
int class_eton_protocol::get_uname_pswd_from_pack_data(protocol_pstruct pst, char *username, char *password)
{
	size_t i = 0;
	size_t j = 0;
	size_t pack_len = get_struct_pack_len(pst);

	if ((NULL == pst) || (NULL == username) || (NULL == password))
		return -1;
	for (i = 0; i < pack_len; i++)
	{
		if (',' == pst->pack_data[i])
			break;
	}
	if ((i == (pack_len - 1)) || (0 == i))
		return -2;
	if ((i + 1) > MAX_LEN_USER_NAME)
		return -3;
	if (((pack_len - (i + 1)) > MAX_LEN_PASSWORD) || ((pack_len - (i + 1)) < MIN_LEN_PASSWORD))
		return -4;
	for (j = 0; j < i; j++)
		username[j] = pst->pack_data[j];
	username[j] = '\0';
	for (j = (i + 1); j < pack_len; j++)
		password[j - (i + 1)] = pst->pack_data[j];
	password[j - (i + 1)] = '\0';

	return 1;
}
//从包内容中取出密码（用于手机app登录服务器或修改密码）
//pst：包结构体
//password：放置从包内容中取出的密码
//返回值：-1参数错误，-2密码长度错误，>0成功
int class_eton_protocol::get_pswd_from_pack_data(protocol_pstruct pst, char * password)
{
	size_t i = 0;
	size_t pack_len = get_struct_pack_len(pst);

	if ((NULL == pst) || (NULL == password))
		return -1;
	if ((pack_len > MAX_LEN_PASSWORD) || (pack_len < MIN_LEN_PASSWORD))
		return -2;
	for (i = 0; i < pack_len; i++)
		password[i] = pst->pack_data[i];
	password[i] = '\0';

	return 1;
}
//从包内容中取出用户名（用于手机app更改用户名）
//pst：包结构体
//username：放置从包内容中取出的用户名
//返回值：-1参数错误，-2用户名长度错误，>0成功
int class_eton_protocol::get_uname_from_pack_data(protocol_pstruct pst, char * username)
{
	size_t i = 0;
	size_t pack_len = get_struct_pack_len(pst);

	if ((NULL == pst) || (NULL == username))
		return -1;
	if ((pack_len > MAX_LEN_USER_NAME) || (pack_len <= 0))
		return -2;
	for (i = 0; i < pack_len; i++)
		username[i] = pst->pack_data[i];
	username[i] = '\0';

	return 1;
}
//设置包结构体中的确认码
//pst：包结构体
//cfm_code：确认码
//返回值：-1参数错误，>0成功
int class_eton_protocol::set_struct_cfm_code(protocol_pstruct pst, unsigned short cfm_code)
{
	if (NULL == pst)
		return -1;
	pst->pack_data[0] = (cfm_code >> 8) & 0xff;
	pst->pack_data[1] = cfm_code & 0xff;
	return 1;
}
//设置包结构体中的确认码和数据
//pst：包结构体
//cfm_code：确认码
//data：数据
//len：数据长度
//返回值：-1参数错误，>0成功
int class_eton_protocol::set_struct_cfm_code_and_data(protocol_pstruct pst, unsigned short cfm_code, char * data, size_t len)
{
	if ((NULL == pst)||(NULL == data)||((len + 2) > MAX_LEN_PACK_DATA))
		return -1;
	pst->pack_data[0] = (cfm_code >> 8) & 0xff;
	pst->pack_data[1] = cfm_code & 0xff;

	for (size_t i = 0; i < len; i++)
	{
		pst->pack_data[i + 2] = data[i];
	}

	return 1;
}
//将设备ID转换成字符串
//pst：包结构体
//len_dev_id：设备ID的长度
//dev_id_str：转换得到的设备ID字符串
//返回值：-1参数错误，>0成功
int class_eton_protocol::get_struct_dev_id_str(protocol_pstruct pst, const size_t len_dev_id, char * dev_id_str)
{
	if ((NULL == pst) || (NULL == dev_id_str) || (len_dev_id > MAX_LEN_DEV_ID))
		return -1;
	char temp[3] = { 0 };
	for (unsigned int i = 0; i < len_dev_id; i++)
	{
		sprintf(temp, "%02x", pst->dev_id[i] & 0xff);
		strcat(dev_id_str, temp);
	}
	return 1;
}