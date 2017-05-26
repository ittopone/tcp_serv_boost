#include "class_eton_database.h"
//boost库头文件
#include "boost/format.hpp"
#include "boost/locale.hpp"
//log4z库头文件
#include "../log4z/log4z.h"
using namespace zsummer::log4z;
//互斥锁
boost::mutex class_eton_database::m_mutex_for_get_conn;
boost::mutex class_eton_database::m_mutex_for_free_conn;
unsigned int class_eton_database::m_conn_point_num;
boost::circular_buffer_space_optimized<spt_db_connection> class_eton_database::m_conn_container;
//自定义常量
#define MAX_LEN_SQL_STR 256
//构造函数
class_eton_database::class_eton_database()
{
}
//析构函数
class_eton_database::~class_eton_database()
{
}
//打印数据库错误信息
void class_eton_database::database_print_otl_exception(otl_exception& p)
{	
	// print out error message	
	// print out error code
	// print out SQL that caused the error
	// print out the variable that caused the error
	// print out error SQLSTATE
	LOGE("msg:"<<p.msg<<".code:"<<p.code<<".text:"<<p.stm_text<<".info:"<<p.var_info<<".sql:"<< p.sqlstate);
}

//创建数据库连接
spt_db_connection class_eton_database::database_create_connection()
{
	spt_db_connection db_conn_ptr(new otl_connect());
	try
	{		
		db_conn_ptr->rlogon("UID=root;PWD=78511603;DSN=eton_db_dsn");

		if ((NULL != db_conn_ptr) && (db_conn_ptr->connected))
		{
			db_conn_ptr->auto_commit_on();
			db_conn_ptr->set_timeout(60);
			m_conn_container.push_back(db_conn_ptr);
		}
	}
	catch (otl_exception & p)
	{
		class_eton_database::database_print_otl_exception(p);
	}
	
	return db_conn_ptr;
}
//获取数据库连接
spt_db_connection class_eton_database::database_get_connection()
{
	spt_db_connection db_conn_ptr;

	std::time_t begin;
	std::time(&begin);

	while (1)
	{
		boost::mutex::scoped_lock lock(m_mutex_for_get_conn);

		if (m_conn_container.size() == 0)
		{
			std::time_t now;
			std::time(&now);
			if (now - begin > 2)
			{
				/*
				*若超过2秒还没取得连接对象，则认为连接池里的连接都失效用完，
				*应重新创建
				*/
				database_create_connection();
				begin = now;
				cout << "create db connect1" << endl;
			}
			continue;
		}

		db_conn_ptr = m_conn_container.front();
		m_conn_container.pop_front();

		if ((NULL != db_conn_ptr) && (db_conn_ptr->connected))
		{
			break;
		}
		else
		{ 
			database_create_connection();
			cout << "create db connect2" << endl;
			continue;
		}
	}//while

	return db_conn_ptr;
}

//释放数据库连接
void class_eton_database::database_release_connection(spt_db_connection db_conn_ptr)
{
	boost::mutex::scoped_lock lock(m_mutex_for_free_conn);
	if (db_conn_ptr != NULL  && db_conn_ptr->connected)
	{
		m_conn_container.push_back(db_conn_ptr);
	}
}
//初始化数据库连接
void class_eton_database::database_init_connection(unsigned int cpu_core_num)
{
	m_conn_point_num = cpu_core_num * 2 + 2;
	m_conn_container.resize(m_conn_point_num);

	otl_connect::otl_initialize(1); // initialize the database API environment  
#if 1
	for (unsigned int i = 0; i < m_conn_point_num; i++)
	{
		if (NULL != class_eton_database::database_create_connection())
		{
#ifdef DEBUG_DATABASE
			cout << "create database connection" << i <<" OK." << endl;
#endif
		}
	}
	//创建数据表eton_table_users
	class_eton_database::db_create_eton_table_users();
	//创建数据表eton_table_devices
	class_eton_database::db_create_eton_table_devices();
#endif
}
//创建数据表eton_table_users
void class_eton_database::db_create_eton_table_users()
{
	//获取数据库连接
	spt_db_connection db_connection = class_eton_database::database_get_connection();
	format fmt("create table if not exists %1%(\
id integer unsigned auto_increment not null,\
phone_num char(30) not null,\
user_name char(30) not null,\
password char(30) not null,\
register_time timestamp not null default CURRENT_TIMESTAMP,\
primary key(id),\
unique(phone_num)\
)");
	fmt % ETON_TABLE_USERS;
	try
	{
		otl_cursor::direct_exec(*db_connection, fmt.str().c_str());
	}
	catch (otl_exception & p)
	{
		class_eton_database::database_print_otl_exception(p);
		LOGE("create table eton_table_users failed !");
	}
	//释放数据库连接
	class_eton_database::database_release_connection(db_connection);
#ifdef DEBUG_DATABASE
	cout << "create table eton_table_users success." << endl;
#endif
}
//创建数据表eton_table_devices
void class_eton_database::db_create_eton_table_devices()
{
	//获取数据库连接
	spt_db_connection db_connection = class_eton_database::database_get_connection();
	format fmt("create table if not exists %1%(\
id integer unsigned auto_increment not null,\
dev_type tinyint unsigned not null,\
dev_series tinyint unsigned not null,\
dev_id char(30) not null,\
dev_name char(30),\
soft_version char(30),\
phone_num char(30),\
primary key(id),\
unique(dev_id)\
)");
	fmt % ETON_TABLE_DEVICES;
	try
	{
		otl_cursor::direct_exec(*db_connection, fmt.str().c_str());
	}
	catch (otl_exception & p)
	{
		class_eton_database::database_print_otl_exception(p);
		LOGE("create table eton_table_devices failed !");
	}
	//释放数据库连接
	class_eton_database::database_release_connection(db_connection);
#ifdef DEBUG_DATABASE
	cout << "create table eton_table_devices success." << endl;
#endif
}
//检测手机号在数据库表eton_table_users中是否存在
bool class_eton_database::db_check_user_phone_num_exist(char * phone_num)
{
	//获取数据库连接
	spt_db_connection db_connection = class_eton_database::database_get_connection();
	format fmt("select * from %1% where phone_num='%2%'");
	fmt % ETON_TABLE_USERS % phone_num;
	try
	{
		otl_stream db_io(strlen(fmt.str().c_str()), fmt.str().c_str(), *db_connection);
		while (!(db_io.eof()))
		{
			//释放数据库连接
			class_eton_database::database_release_connection(db_connection);
			return TRUE;
		}
	}
	catch (otl_exception & p)
	{
		class_eton_database::database_print_otl_exception(p);
	}
	
	//释放数据库连接
	class_eton_database::database_release_connection(db_connection);
	return FALSE;
}
//添加新用户
bool class_eton_database::db_add_new_user(char * phone_num, char * uname, char * password)
{
#if 0
	//uname为utf-8编码时，出错，即不支持中文，故不采用该方法
	//获取数据库连接
	spt_db_connection db_connection = class_eton_database::database_get_connection();
	format fmt("insert into %1%(phone_num,user_name,password) values('%2%','%3%','%4%')");
	fmt % ETON_TABLE_USERS % phone_num % uname % password;
	try
	{
		otl_cursor::direct_exec(*db_connection, fmt.str().c_str());
	}
	catch (otl_exception & p)
	{
		class_eton_database::database_print_otl_exception(p);
		LOGE((format("insert user: %s, %s failed !") % phone_num % uname).str());
		//释放数据库连接
		class_eton_database::database_release_connection(db_connection);
		return FALSE;
	}
	//释放数据库连接
	class_eton_database::database_release_connection(db_connection);
	return TRUE;
#else
	//获取数据库连接
	spt_db_connection db_connection = class_eton_database::database_get_connection();
	format fmt("insert into %1%(phone_num,user_name,password) values('%2%',:user_name<char[31]>,'%3%')");
	fmt % ETON_TABLE_USERS % phone_num % password;
	try
	{
		otl_stream db_io(MAX_LEN_SQL_STR, fmt.str().c_str(), *db_connection);
		db_io << uname ;
	}
	catch (otl_exception & p)
	{
		class_eton_database::database_print_otl_exception(p);
		LOGE((format("insert user: %s, %s failed !") % phone_num % uname).str());
		//释放数据库连接
		class_eton_database::database_release_connection(db_connection);
		return FALSE;
	}	
	//释放数据库连接
	class_eton_database::database_release_connection(db_connection);
	return TRUE;
#endif
}
//验证用户密码
bool class_eton_database::db_check_user_password_exist(char * phone_num, char * password)
{
	//获取数据库连接
	spt_db_connection db_connection = class_eton_database::database_get_connection();
	format fmt("select * from %1% where phone_num='%2%' and password='%3%'");
	fmt % ETON_TABLE_USERS % phone_num % password;
	try
	{
		otl_stream db_io(strlen(fmt.str().c_str()), fmt.str().c_str(), *db_connection);
		while (!(db_io.eof()))
		{
			//释放数据库连接
			class_eton_database::database_release_connection(db_connection);
			return TRUE;
		}
	}
	catch (otl_exception & p)
	{
		class_eton_database::database_print_otl_exception(p);		
	}
	//释放数据库连接
	class_eton_database::database_release_connection(db_connection);
	return FALSE;
}
//修改用户昵称
bool class_eton_database::db_modify_user_name(char * phone_num, char * uname)
{
	//获取数据库连接
	spt_db_connection db_connection = class_eton_database::database_get_connection();
	format fmt("update %1% set user_name=:user_name<char[31]> where phone_num='%2%'");
	fmt % ETON_TABLE_USERS % phone_num;

	try
	{
		otl_stream db_io(MAX_LEN_SQL_STR, fmt.str().c_str(), *db_connection);
		db_io << uname;
	}
	catch (otl_exception & p)
	{
		class_eton_database::database_print_otl_exception(p);
		LOGE((format("user %s modify uname %s fail.") % phone_num % uname).str());
		//释放数据库连接
		class_eton_database::database_release_connection(db_connection);
		return FALSE;
	}
	//释放数据库连接
	class_eton_database::database_release_connection(db_connection);
	return TRUE;
}
//获取用户昵称
bool class_eton_database::db_get_user_name(char * phone_num, char * uname)
{
	//获取数据库连接
	spt_db_connection db_connection = class_eton_database::database_get_connection();
	format fmt("select user_name from %1% where phone_num='%2%'");
	fmt % ETON_TABLE_USERS % phone_num;
	try
	{
		otl_stream db_io(strlen(fmt.str().c_str()), fmt.str().c_str(), *db_connection);
		while (!(db_io.eof()))
		{
			db_io >> uname;
			//释放数据库连接
			class_eton_database::database_release_connection(db_connection);
			return TRUE;
		}
	}
	catch (otl_exception & p)
	{
		class_eton_database::database_print_otl_exception(p);		
	}
	//释放数据库连接
	class_eton_database::database_release_connection(db_connection);
	return FALSE;
}
//修改用户密码
bool class_eton_database::db_modify_user_password(char * phone_num, char * password)
{
	//获取数据库连接
	spt_db_connection db_connection = class_eton_database::database_get_connection();
	format fmt("update %1% set password='%2%' where phone_num='%3%'");
	fmt % ETON_TABLE_USERS % password % phone_num;

	try
	{
		otl_cursor::direct_exec(*db_connection, fmt.str().c_str());
	}
	catch (otl_exception & p)
	{
		class_eton_database::database_print_otl_exception(p);
		LOGE((format("user %s modify password %s fail.") % phone_num % password).str());
		//释放数据库连接
		class_eton_database::database_release_connection(db_connection);
		return FALSE;
	}
	//释放数据库连接
	class_eton_database::database_release_connection(db_connection);
	return TRUE;
}
//验证设备ID在数据库表ETON_TABLE_DEVICES中是否存在
bool class_eton_database::db_check_device_id_exist(char * dev_id)
{
	//获取数据库连接
	spt_db_connection db_connection = class_eton_database::database_get_connection();
	format fmt("select * from %1% where dev_id='%2%'");
	fmt % ETON_TABLE_DEVICES % dev_id;
	try
	{
		otl_stream db_io(strlen(fmt.str().c_str()), fmt.str().c_str(), *db_connection);
		while (!(db_io.eof()))
		{
			//释放数据库连接
			class_eton_database::database_release_connection(db_connection);
			return TRUE;
		}
	}
	catch (otl_exception & p)
	{
		class_eton_database::database_print_otl_exception(p);		
	}
	//释放数据库连接
	class_eton_database::database_release_connection(db_connection);
	return FALSE;
}
//新增设备
bool class_eton_database::db_add_new_device(unsigned int dev_type, unsigned int dev_series, char * dev_id)
{
	//获取数据库连接
	spt_db_connection db_connection = class_eton_database::database_get_connection();
	format fmt("insert into %1%(dev_type,dev_series,dev_id) values('%2%','%3%','%4%')");
	fmt % ETON_TABLE_DEVICES % dev_type % dev_series % dev_id;

	try
	{
		otl_cursor::direct_exec(*db_connection, fmt.str().c_str());
	}
	catch (otl_exception & p)
	{
		class_eton_database::database_print_otl_exception(p);
		LOGE((format("insert device: %s failed !") % dev_id).str());
		//释放数据库连接
		class_eton_database::database_release_connection(db_connection);
		return FALSE;
	}
	//释放数据库连接
	class_eton_database::database_release_connection(db_connection);
	return TRUE;
}
//获取设备列表
bool class_eton_database::db_get_device_list(unsigned int dev_type, char * phone_num, \
	container::vector<spt_dev_list> & vector_dev_list)
{
	//获取数据库连接
	spt_db_connection db_connection = class_eton_database::database_get_connection();
	format fmt("select dev_series,dev_id from %1% where dev_type='%2%' and phone_num='%3%'");
	fmt % ETON_TABLE_DEVICES % dev_type % phone_num;

	bool flag = FALSE;
	try
	{
		otl_stream db_io(strlen(fmt.str().c_str()), fmt.str().c_str(), *db_connection);
		while (!(db_io.eof()))
		{
			flag = TRUE;
			spt_dev_list dev_list(new class_dev_list());
			db_io >> dev_list->dev_series;
			db_io >> dev_list->dev_id;
			vector_dev_list.push_back(dev_list);
		}
	}
	catch (otl_exception & p)
	{
		class_eton_database::database_print_otl_exception(p);
	}
	if (flag)
	{
		//释放数据库连接
		class_eton_database::database_release_connection(db_connection);
		return TRUE;
	}
	//释放数据库连接
	class_eton_database::database_release_connection(db_connection);
	return FALSE;
	
}
//设备绑定手机号
bool class_eton_database::db_device_bind_phone_num(unsigned int dev_type, unsigned int dev_series, \
	char * dev_id, char * phone_num)
{
	//获取数据库连接
	spt_db_connection db_connection = class_eton_database::database_get_connection();
	format fmt("update %1% set phone_num='%2%' where dev_type='%3%' and dev_series='%4%' and dev_id='%5%'");
	fmt % ETON_TABLE_DEVICES % phone_num % dev_type % dev_series % dev_id;

	try
	{
		otl_cursor::direct_exec(*db_connection, fmt.str().c_str());
	}
	catch (otl_exception & p)
	{
		class_eton_database::database_print_otl_exception(p);
		LOGE((format("device %s bind phone %s fail.") % dev_id % phone_num).str());
		//释放数据库连接
		class_eton_database::database_release_connection(db_connection);
		return FALSE;
	}
	//释放数据库连接
	class_eton_database::database_release_connection(db_connection);
	return TRUE;
}
