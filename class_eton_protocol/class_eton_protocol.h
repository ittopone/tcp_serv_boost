#ifndef __CLASS_ETON_PROTOCOL_H__
#define __CLASS_ETON_PROTOCOL_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//��ͷ
#define PACK_HEAD 0x7e
//��β
#define PACK_TAIL 0x7e
//�����
#define CMD_PACK 0x01
//Ӧ���
#define CFM_PACK 0x03
//���ݰ�
#define DATA_PACK 0x02

//��ͷ����
#define LEN_PACK_HEAD 1
//��β����
#define LEN_PACK_TAIL 1
//�ֻ����볤��
#define LEN_PHONE_NUM 5
//�豸���ͳ���
#define LEN_DEV_TYPE 1
//�豸ϵ�г���
#define LEN_DEV_SERIES 1
//�豸ID��󳤶�
#define MAX_LEN_DEV_ID 12
//�������ͳ���
#define LEN_CODE_TYPE 1
//��ˮ�ų���
#define LEN_SERIAL_NUM 1
//����ʶ����
#define LEN_PACK_MARK 1
//ָ��ID����
#define LEN_CMD_ID 2
//�����ȳ���
#define LEN_PACK_LEN 2
//��������󳤶�
#define MAX_LEN_PACK_DATA 256
//У���볤��
#define LEN_CHECK_CODE 2
//ת��������������������ֵ
#define MAX_LEN_ZHUANYI 20
//�û�����󳤶�
#define MAX_LEN_USER_NAME 20
//�û��������󳤶�
#define MAX_LEN_PASSWORD 20
//�û��������С����
#define MIN_LEN_PASSWORD 10
//ȷ���볤��
#define LEN_CFM_CODE 2

//����ʶ�ڰ��ṹ���е�ƫ����
#define OFF_SET_PACK_MARK (LEN_PHONE_NUM+LEN_DEV_TYPE+LEN_DEV_SERIES+MAX_LEN_DEV_ID+LEN_CODE_TYPE+LEN_SERIAL_NUM)
//����ʶ�������֮���ƫ����
#define OFF_SET_MARK_TO_DATA (LEN_CMD_ID + LEN_PACK_LEN)
//�����ݵ�ƫ����
#define OFF_SET_PACK_DATA (OFF_SET_PACK_MARK+LEN_PACK_MARK+OFF_SET_MARK_TO_DATA)
//��С�ķ������
#define MIN_LEN_PACK (LEN_PACK_HEAD+OFF_SET_PACK_DATA+LEN_CHECK_CODE+LEN_PACK_TAIL)
//���������
#define MAX_LEN_PACK (MIN_LEN_PACK+MAX_LEN_PACK_DATA+MAX_LEN_ZHUANYI)
//���ṹ��ĳ���
#define LEN_PROTOCOL_STRUCT sizeof(protocol_struct)
//���������տͻ������ݵ���󻺳���
#define MAX_LEN_BUFFER (2 * MAX_LEN_PACK)

//���ṹ��
typedef struct
{
	//�ֻ���
	char phone_num[LEN_PHONE_NUM];
	//�豸����
	char dev_type;
	//�豸ϵ�к�
	char dev_series;
	//�豸ID
	char dev_id[MAX_LEN_DEV_ID];
	//�������ͣ������ó�0x00ʱ����ʾ������
	char code_type;
	//��ˮ��
	char serial_num;
	//����ʶ
	char pack_mark;
	//ָ��ID
	char cmd_id[LEN_CMD_ID];
	//������
	char pack_len[LEN_PACK_LEN];
	//������
	char pack_data[MAX_LEN_PACK_DATA];
	//У����
	char check_code[LEN_CHECK_CODE];
}protocol_struct, *protocol_pstruct;
//�ඨ��
class class_eton_protocol
{
public:
	//���캯��
	class_eton_protocol();
	//��������
	~class_eton_protocol();
	//crc16У������㷽��
	//pdata��Ҫ����У�������
	//data_len��Ҫ����У������ݵĳ���
	//pcrc�����ص�У����
	//����ֵ�����󷵻�-1����ȷ����У����
	static int get_crc16(char *pdata, size_t data_len, char * pcrc);
	//��������ṹ���е�У���룬�����ݼ��ܣ�ת�壬�õ�Ҫ���͵����ݼ�����
	//pst�����ṹ�壬����Ҫ���͵���Ϣ
	//pdata_packed���õ�Ҫ���͵�����
	//len_data_packed��pdata_packed����ĳ���
	//����ֵ��-1��������-2���У�������-3��������������󳤶ȣ�>0����Ҫ���͵����ݵĳ���
	static int pack_data(protocol_pstruct pst, char * pdata_packed, size_t len_data_packed);
	//�����ת�廹ԭ�������ݽ��ܣ���֤У���룬�õ�����Ҫ���յ���Ϣ�İ��ṹ��
	//pst�����ṹ�壬����Ҫ���ܵ���Ϣ
	//pdata_need_unpacked����Ҫ���н��������
	//len_data_need_unpacked��Ҫ���н�������ݵĳ���
	//����ֵ��-1��������-2��ͷ���β��ʧ,-3�����ṹ�峤�ȣ�-4ת�����-5��֤У�������>0��������ݳ���
	static int unpack_data(protocol_pstruct pst, char * pdata_need_unpacked, size_t len_data_need_unpacked);
	//���ýṹ���е�ָ��ID
	//pst�����ṹ��
	//cmd_id��Ҫ���õ�ָ��ID
	//����ֵ��-1��������>0�ɹ�
	static int set_struct_cmd_id(protocol_pstruct pst, unsigned int cmd_id);
	//��ȡ�ṹ���е�ָ��ID
	//pst�����ṹ��
	//����ֵ��ָ��ID
	static unsigned int get_struct_cmd_id(protocol_pstruct pst);
	//���ýṹ���еİ�����
	//pst�����ṹ��
	//pack_len��������
	//����ֵ��-1��������>0�ɹ�
	static int set_struct_pack_len(protocol_pstruct pst, size_t pack_len);
	//��ȡ�ṹ���еİ�����
	//pst�����ṹ��
	//����ֵ��������
	static size_t get_struct_pack_len(protocol_pstruct pst);
	//���ýṹ���еİ������������
	//Pack_data��������
	//pack_len��������
	//����ֵ��-1��������,-2pack_len������󳤶ȣ�>0�ɹ�
	static int set_struct_pack_data_len(protocol_pstruct pst, char * pack_data, size_t pack_len);
	//���ýṹ���е��ֻ���
	//pst�����ṹ��
	//phone_num���ֻ��ţ��ַ�����
	//����ֵ��-1��������>0�ɹ�
	static int set_struct_phone_num(protocol_pstruct pst, char * phone_num);
	//��ȡ�ṹ���е��ֻ���
	//pst�����ṹ��
	//phone_num���ֻ��ţ��ַ�����
	//����ֵ��-1��������>0�ɹ�
	static int get_struct_phone_num(protocol_pstruct pst, char * phone_num);
	//�Ӱ������л�ȡ�û��������루�����ֻ�appע���������
	//pst�����ṹ��
	//username�����ô�pst�л�ȡ���û���
	//password�����ô�pst�л�ȡ������
	//����ֵ��-1��������-2�����ݸ�ʽ����-3�����û�����󳤶ȣ�-4���볤�ȴ���>0�ɹ�
	static int get_uname_pswd_from_pack_data(protocol_pstruct pst, char * username, char * password);
	//�Ӱ�������ȡ�����루�����ֻ�app��¼���������޸����룩
	//pst�����ṹ��
	//password�����ôӰ�������ȡ��������
	//����ֵ��-1��������-2���볤�ȴ���>0�ɹ�
	static int get_pswd_from_pack_data(protocol_pstruct pst, char * password);
	//�Ӱ�������ȡ���û����������ֻ�app�����û�����
	//pst�����ṹ��
	//username�����ôӰ�������ȡ�����û���
	//����ֵ��-1��������-2�û������ȴ���>0�ɹ�
	static int get_uname_from_pack_data(protocol_pstruct pst, char * username);
	//���ð��ṹ���е�ȷ����
	//pst�����ṹ��
	//cfm_code��ȷ����
	//����ֵ��-1��������>0�ɹ�
	static int set_struct_cfm_code(protocol_pstruct pst,unsigned short cfm_code);
	//���ð��ṹ���е�ȷ���������
	//pst�����ṹ��
	//cfm_code��ȷ����
	//data������
	//len�����ݳ���
	//����ֵ��-1��������>0�ɹ�
	static int set_struct_cfm_code_and_data(protocol_pstruct pst, unsigned short cfm_code, char * data, size_t len);
	//���豸IDת�����ַ���
	//pst�����ṹ��
	//len_dev_id���豸ID�ĳ���
	//dev_id_str��ת���õ����豸ID�ַ���
	//����ֵ��-1��������>0�ɹ�
	static int get_struct_dev_id_str(protocol_pstruct pst, const size_t len_dev_id, char * dev_id_str);
};

#endif