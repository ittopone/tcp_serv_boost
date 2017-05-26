#ifndef __CLASS_GLOBAL_H__
#define __CLASS_GLOBAL_H__
//boost库头文件
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/container/vector.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
//自定义头文件
#include "../class_eton_client/class_eton_client.h"
//标准c++头文件
#include <iostream>
using namespace std;
//重命名
typedef unordered_map<string, spt_client> U_MAP;
//类定义
class class_global
{
public:
	//定义全局容器用来保存客户端连接
	static mutex g_mutex;
	static U_MAP g_client_map;
	//将包标识在数据中索引存放到容器中，并返回容器
	static container::vector<size_t> get_pack_mark_index(char * data, size_t len_data);
	//将sourceStr的size字节内容复制到destStr，且不受sourceStr中的'\0'影响，
	//复制完后，不在destStr后追加'\0'
	//成功返回0，失败返回1
	static int my_strncpy(char *destStr, const char *sourceStr, size_t size);
	//将16进制字符串转换为16进制字节数组
	//array_hex：16进制字节数组
	//hex_str：16进制字符串
	//len_array_hex：16进制字节数组长度
	static void hex_str_to_hex(char * array_hex, char * hex_str, size_t len_array_hex);
};
#endif