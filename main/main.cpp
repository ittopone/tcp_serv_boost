//boost��ͷ�ļ�
#include <boost/lexical_cast.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/function.hpp>
using namespace boost::lambda;
//log4z��ͷ�ļ�
#include "../log4z/log4z.h"
using namespace zsummer::log4z;
//�Զ���ͷ�ļ�
#include "../class_eton_server/class_eton_server.h"
#include "../class_eton_database/class_eton_database.h"
int main(int argc, char * argv[])
{
	//start log4z
	ILog4zManager::getRef().setLoggerPath(LOG4Z_MAIN_LOGGER_ID, "./logFile");
	ILog4zManager::getRef().start();
	ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_TRACE);
	//��ʱ5��
	//boost::thread::sleep(boost::get_system_time() + boost::posix_time::seconds(2));
	//���ݿ��ʼ��
	class_eton_database::database_init_connection(lexical_cast<int>(argv[2]));
	//��ʱ5��
	//boost::thread::sleep(boost::get_system_time() + boost::posix_time::seconds(2));
	//��������ʼ��
	boost::asio::io_service ios;
	//�źŴ���
	signal_set sig(ios);
	sig.add(SIGINT);
	typedef void(handler_type)(const system::error_code &, int);
	boost::function<handler_type> sig_handler = [](const system::error_code & ec, int n)
	{
		if (ec)
		{
			LOGE(ec.message());
			return;
		}
		switch (n)
		{
		case SIGINT:
			LOGE("GET SIGINT.");
			break;
		default:
			LOGE("GET UNKNOWN SIGNAL.");
			break;
		}
	};
	//�첽����źŴ�����
	sig.async_wait(sig_handler);
	class_eton_server server(ios, lexical_cast<int>(argv[1]), lexical_cast<int>(argv[2]));	
	try
	{
		server.start();
		ios.run();	
	}
	catch (const std::exception & e)
	{
		LOGE("server exception: " << e.what());
		server.stop();
	}	
	LOGD("eton server shutdown.");
	return 0;
}