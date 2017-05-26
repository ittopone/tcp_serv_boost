#ifndef __CLASS_GLOBAL_H__
#define __CLASS_GLOBAL_H__
//boost��ͷ�ļ�
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/container/vector.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
//�Զ���ͷ�ļ�
#include "../class_eton_client/class_eton_client.h"
//��׼c++ͷ�ļ�
#include <iostream>
using namespace std;
//������
typedef unordered_map<string, spt_client> U_MAP;
//�ඨ��
class class_global
{
public:
	//����ȫ��������������ͻ�������
	static mutex g_mutex;
	static U_MAP g_client_map;
	//������ʶ��������������ŵ������У�����������
	static container::vector<size_t> get_pack_mark_index(char * data, size_t len_data);
	//��sourceStr��size�ֽ����ݸ��Ƶ�destStr���Ҳ���sourceStr�е�'\0'Ӱ�죬
	//������󣬲���destStr��׷��'\0'
	//�ɹ�����0��ʧ�ܷ���1
	static int my_strncpy(char *destStr, const char *sourceStr, size_t size);
	//��16�����ַ���ת��Ϊ16�����ֽ�����
	//array_hex��16�����ֽ�����
	//hex_str��16�����ַ���
	//len_array_hex��16�����ֽ����鳤��
	static void hex_str_to_hex(char * array_hex, char * hex_str, size_t len_array_hex);
};
#endif