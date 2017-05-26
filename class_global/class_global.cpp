#include "class_global.h"
//定义全局容器用来保存客户端连接
mutex class_global::g_mutex;
U_MAP class_global::g_client_map;
//将包标识在数据中索引存放到容器中，并返回容器
container::vector<size_t> class_global::get_pack_mark_index(char * data, size_t len_data)
{
	container::vector<size_t> vector_pack_mark_index;
	for (size_t index = 0; index < len_data; index++)
	{
		if (PACK_HEAD == data[index])
			vector_pack_mark_index.push_back(index);
	}

	return vector_pack_mark_index;
}
//将sourceStr的size字节内容复制到destStr，且不受sourceStr中的'\0'影响，
//复制完后，不在destStr后追加'\0'
//成功返回0，失败返回1
int class_global::my_strncpy(char *destStr, const char *sourceStr, size_t size)
{
	size_t i = 0;

	//参数检测
	if (NULL == destStr)
		return -1;
	if (NULL == sourceStr)
		return -1;

	for (i = 0; i < size; i++)
		*(destStr + i) = *(sourceStr + i);

	return 1;
}
//将16进制字符串转换为16进制字节数组
//array_hex：16进制字节数组
//hex_str：16进制字符串
//len_array_hex：16进制字节数组长度
void class_global::hex_str_to_hex(char * array_hex, char * hex_str, size_t len_array_hex)
{
	char temp[3] = { 0 };
	char * end;
	unsigned int j = 0;
	for (unsigned int i = 0; i < strlen(hex_str); i += 2)
	{
		strncpy(temp, hex_str + i, 2);
		if (j < len_array_hex)
			array_hex[j++] = strtol(temp, &end, 16) & 0xff;
		else
			break;
	}
}