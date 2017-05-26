#ifndef __CLASS_ETON_DATABASE_H__
#define __CLASS_ETON_DATABASE_H__
//自定义头文件
#include "../debug_switch/debug.h"
//boost库头文件
#include <boost/circular_buffer.hpp>  
#include <boost/shared_ptr.hpp>  
#include <boost/thread/mutex.hpp> 
#include <boost/container/vector.hpp>
using namespace boost;
//标准c++头文件
#include <iostream>
using namespace std;
//otlv4库头文件
#define OTL_ODBC_MYSQL
#pragma comment(lib,"myodbc5w.lib")
#include "../otlv4_h2/otlv4.h"
//自定义头文件
#include "../class_eton_protocol/class_eton_protocol.h"
//自定义常量
#define ETON_TABLE_USERS "eton_table_users"
#define ETON_TABLE_DEVICES "eton_table_devices"
//重命名
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
	//互斥锁
	static boost::mutex m_mutex_for_get_conn;
	static boost::mutex m_mutex_for_free_conn;
public:
	class_eton_database();
	~class_eton_database();

	//打印数据库错误信息
	static void database_print_otl_exception(otl_exception& p);
	//创建数据库连接
	static spt_db_connection database_create_connection();
	//获取数据库连接
	static spt_db_connection database_get_connection();
	//释放数据库连接
	static void database_release_connection(spt_db_connection db_conn_ptr);
	//初始化数据库连接
	static void database_init_connection(unsigned int cpu_core_num);
	//创建数据表eton_table_users
	static void db_create_eton_table_users();
	//创建数据表eton_table_devices
	static void db_create_eton_table_devices();
	//检测手机号在数据库表ETON_TABLE_USERS中是否存在
	static bool db_check_user_phone_num_exist(char * phone_num);
	//添加新用户
	static bool db_add_new_user(char * phone_num, char * uname, char * password);
	//验证用户密码
	static bool db_check_user_password_exist(char * phone_num, char * password);
	//修改用户昵称
	static bool db_modify_user_name(char * phone_num, char * uname);
	//获取用户昵称
	static bool db_get_user_name(char * phone_num, char * uname);
	//修改用户密码
	static bool db_modify_user_password(char * phone_num, char * password);
	//验证设备ID在数据库表ETON_TABLE_DEVICES中是否存在
	static bool db_check_device_id_exist(char * dev_id);
	//新增设备
	static bool db_add_new_device(unsigned int dev_type, unsigned int dev_series, char * dev_id);
	//获取设备列表
	static bool db_get_device_list(unsigned int dev_type, char * phone_num,container::vector<spt_dev_list> & vector_dev_list);
	//设备绑定手机号
	static bool db_device_bind_phone_num(unsigned int dev_type, unsigned int dev_series, \
		char * dev_id, char * phone_num);
};
#endif
