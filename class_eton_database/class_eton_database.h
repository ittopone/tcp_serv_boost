#ifndef __CLASS_ETON_DATABASE_H__
#define __CLASS_ETON_DATABASE_H__
//�Զ���ͷ�ļ�
#include "../debug_switch/debug.h"
//boost��ͷ�ļ�
#include <boost/circular_buffer.hpp>  
#include <boost/shared_ptr.hpp>  
#include <boost/thread/mutex.hpp> 
#include <boost/container/vector.hpp>
using namespace boost;
//��׼c++ͷ�ļ�
#include <iostream>
using namespace std;
//otlv4��ͷ�ļ�
#define OTL_ODBC_MYSQL
#pragma comment(lib,"myodbc5w.lib")
#include "../otlv4_h2/otlv4.h"
//�Զ���ͷ�ļ�
#include "../class_eton_protocol/class_eton_protocol.h"
//�Զ��峣��
#define ETON_TABLE_USERS "eton_table_users"
#define ETON_TABLE_DEVICES "eton_table_devices"
//������
typedef boost::shared_ptr<otl_connect> spt_db_connection;
class class_dev_list
{
public:
	int dev_series;
	char dev_id[2 * MAX_LEN_DEV_ID + 1];
};
typedef boost::shared_ptr<class_dev_list> spt_dev_list;
class class_eton_database
{
private:
	static unsigned int m_conn_point_num;
	static boost::circular_buffer_space_optimized<spt_db_connection> m_conn_container;
	//������
	static boost::mutex m_mutex_for_get_conn;
	static boost::mutex m_mutex_for_free_conn;
public:
	class_eton_database();
	~class_eton_database();

	//��ӡ���ݿ������Ϣ
	static void database_print_otl_exception(otl_exception& p);
	//�������ݿ�����
	static spt_db_connection database_create_connection();
	//��ȡ���ݿ�����
	static spt_db_connection database_get_connection();
	//�ͷ����ݿ�����
	static void database_release_connection(spt_db_connection db_conn_ptr);
	//��ʼ�����ݿ�����
	static void database_init_connection(unsigned int cpu_core_num);
	//�������ݱ�eton_table_users
	static void db_create_eton_table_users();
	//�������ݱ�eton_table_devices
	static void db_create_eton_table_devices();
	//����ֻ��������ݿ��ETON_TABLE_USERS���Ƿ����
	static bool db_check_user_phone_num_exist(char * phone_num);
	//������û�
	static bool db_add_new_user(char * phone_num, char * uname, char * password);
	//��֤�û�����
	static bool db_check_user_password_exist(char * phone_num, char * password);
	//�޸��û��ǳ�
	static bool db_modify_user_name(char * phone_num, char * uname);
	//��ȡ�û��ǳ�
	static bool db_get_user_name(char * phone_num, char * uname);
	//�޸��û�����
	static bool db_modify_user_password(char * phone_num, char * password);
	//��֤�豸ID�����ݿ��ETON_TABLE_DEVICES���Ƿ����
	static bool db_check_device_id_exist(char * dev_id);
	//�����豸
	static bool db_add_new_device(unsigned int dev_type, unsigned int dev_series, char * dev_id);
	//��ȡ�豸�б�
	static bool db_get_device_list(unsigned int dev_type, char * phone_num,container::vector<spt_dev_list> & vector_dev_list);
	//�豸���ֻ���
	static bool db_device_bind_phone_num(unsigned int dev_type, unsigned int dev_series, \
		char * dev_id, char * phone_num);
};
#endif
