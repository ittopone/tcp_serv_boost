#include "class_global.h"
//����ȫ��������������ͻ�������
mutex class_global::g_mutex;
U_MAP class_global::g_client_map;
//������ʶ��������������ŵ������У�����������
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
//��sourceStr��size�ֽ����ݸ��Ƶ�destStr���Ҳ���sourceStr�е�'\0'Ӱ�죬
//������󣬲���destStr��׷��'\0'
//�ɹ�����0��ʧ�ܷ���1
int class_global::my_strncpy(char *destStr, const char *sourceStr, size_t size)
{
	size_t i = 0;

	//�������
	if (NULL == destStr)
		return -1;
	if (NULL == sourceStr)
		return -1;

	for (i = 0; i < size; i++)
		*(destStr + i) = *(sourceStr + i);

	return 1;
}
//��16�����ַ���ת��Ϊ16�����ֽ�����
//array_hex��16�����ֽ�����
//hex_str��16�����ַ���
//len_array_hex��16�����ֽ����鳤��
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