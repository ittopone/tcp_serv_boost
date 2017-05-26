#ifndef __DEFINE_PSPC1_H__
#define __DEFINE_PSPC1_H__
/******************************************ָ��****************************************/
//Pspc1��¼������ָ�0x0024��
#define CMD_PSPC1_LOGIN 0x0024
//�ֻ���pspc1�豸ָ�0x0025��
#define CMD_APP_BIND_PSPC1 0x0025
//�ֻ���ȡpspc1�豸����״ָ̬�0x0026��
#define CMD_APP_GET_PSPC1_STATUS 0x0026
//�ֻ���ȡpspc1�豸���ò���ָ�0x0027��
#define CMD_APP_GET_PSPC1_SET_ARGS 0x0027
//�ֻ�����pspc1�豸����������������ָ�0x0028��
#define CMD_APP_SET_PSPC1_GLDZDL_ARG 0x0028
//�ֻ�����pspc1�豸©����������������ָ�0x0029��
#define CMD_APP_SET_PSPC1_LLBDZDL_ARG 0x0029
//�ֻ�����pspc1�豸©��������������ָ�0x002a��
#define CMD_APP_SET_PSPC1_LLDZDL_ARG 0x002a
//�ֻ�����pspc1�豸��ѹ������ѹ����ָ�0x002b��
#define CMD_APP_SET_PSPC1_GYDZDY_ARG 0x002b
//�ֻ�����pspc1�豸Ƿѹ������ѹ����ָ�0x002c��
#define CMD_APP_SET_PSPC1_QYDZDY_ARG 0x002c
//�ֻ�����pspc1�豸�����Ͽ�����ʱ�����ָ�0x002d��
#define CMD_APP_SET_PSPC1_GLDKDZSJ_ARG 0x002d
//�ֻ�����pspc1�豸��ѹ/Ƿѹ�Ͽ�����ʱ�����ָ�0x002e��
#define CMD_APP_SET_PSPC1_GYQYDKDZSJ_ARG 0x002e
//�ֻ�����pspc1�豸�Զ��غ�բʱ�����ָ�0x002f��
#define CMD_APP_SET_PSPC1_ZDCHZSJ_ARG 0x002f
//�ֻ�����pspc1�豸�ܵ�������ָ�0x0030��
#define CMD_APP_SET_PSPC1_ZDN_CLEAR 0x0030
//�ֻ�����pspc1�豸��·1��������ָ�0x0031��
#define CMD_APP_SET_PSPC1_FL1DN_CLEAR 0x0031
//�ֻ�����pspc1�豸��·2��������ָ�0x0032��
#define CMD_APP_SET_PSPC1_FL2DN_CLEAR 0x0032
//�ֻ�����pspc1�豸��·3��������ָ�0x0033��
#define CMD_APP_SET_PSPC1_FL3DN_CLEAR 0x0033
//�ֻ�����pspc1�豸ʱ��У׼ָ�0x0034��
#define CMD_APP_SET_PSPC1_CLOCK 0x0034
//�ֻ�����pspc1�豸����У׼ָ�0x0035��
#define CMD_APP_SET_PSPC1_DATE 0x0035
//�ֻ�����pspc1�豸WiFi����ָ�0x0036��
#define CMD_APP_SET_PSPC1_WIFI 0x0036
//�ֻ�����pspc1�豸WiFi������ʼʱ��ָ�0x0037��
#define CMD_APP_SET_PSPC1_WIFI_STIME 0x0037
//�ֻ�����pspc1�豸WiFi������ֹʱ��ָ�0x0038��
#define CMD_APP_SET_PSPC1_WIFI_ETIME 0x0038
//�ֻ���ȡpspc1�豸�ռ���Ϣָ�0x0039��
#define CMD_APP_GET_PSPC1_RECORD 0x0039
//Pspc1���ֻ�����©��澯ָ�0x003a��
#define CMD_PSPC1_SEND_ALARM_LD 0x003a
//Pspc1���ֻ����͸�ѹ�澯ָ�0x003b��
#define CMD_PSPC1_SEND_ALARM_GY 0x003b
//Pspc1���ֻ����͵�ѹ�澯ָ�0x003c��
#define CMD_PSPC1_SEND_ALARM_DY 0x003c
//Pspc1���ֻ����͹����澯ָ�0x003d��
#define CMD_PSPC1_SEND_ALARM_GL	0x003d
//�ֻ���pspc1���ͻ�ȡĳ�����ʹ�����ָ�0x003e��
#define CMD_APP_GET_PSPC1_MNDNSYQK 0x003e
/******************************************ȷ����****************************************/
//Pspc1��¼�������ɹ�
#define CFM_PSPC1_LOGIN_OK 0x0048
//Pspc1��¼������ʧ��
#define CFM_PSPC1_LOGIN_FAIL 0x0049
//�ֻ���PSPC1�豸�ɹ�
#define CFM_APP_BIND_PSPC1_OK 0x004a
//�ֻ���PSPC1�豸ʧ��
#define CFM_APP_BIND_PSPC1_FAIL 0x004b
//�ֻ���ȡpspc1�豸����״̬�ɹ�
#define CFM_APP_GET_PSPC1_STATUS_OK 0x004c
//�ֻ���ȡpspc1�豸����״̬ʧ��
#define CFM_APP_GET_PSPC1_STATUS_FAIL 0x004d
//�ֻ���ȡpspc1���ò����ɹ�
#define CFM_APP_GET_PSPC1_SET_ARGS_OK 0x004e
//�ֻ���ȡpspc1���ò���ʧ��
#define CFM_APP_GET_PSPC1_SET_ARGS_FAIL 0x004f
//�ֻ�����pspc1�����������������ɹ�
#define CFM_APP_SET_PSPC1_GLDZDL_OK 0x0050
//�ֻ�����pspc1����������������ʧ��
#define CFM_APP_SET_PSPC1_GLDZDL_FAIL 0x0051
//�ֻ�����PSPC1©�����������������ɹ�
#define CFM_APP_SET_PSPC1_LLBDZDL_OK 0x0052
//�ֻ�����PSPC1©����������������ʧ��
#define CFM_APP_SET_PSPC1_LLBDZDL_FAIL 0x0053
//�ֻ�����PSPC1©���������������ɹ�
#define CFM_APP_SET_PSPC1_LLDZDL_OK 0x0054
//�ֻ�����PSPC1©��������������ʧ��
#define CFM_APP_SET_PSPC1_LLDZDL_FAIL 0x0055
//�ֻ�����PSPC1��ѹ������ѹ�����ɹ�
#define CFM_APP_SET_PSPC1_GYDZDY_OK 0x0056
//�ֻ�����PSPC1��ѹ������ѹ����ʧ��
#define CFM_APP_SET_PSPC1_GYDZDY_FAIL 0x0057
//�ֻ�����PSPC1Ƿѹ������ѹ�����ɹ�
#define CFM_APP_SET_PSPC1_QYDZDY_OK 0x0058
//�ֻ�����PSPC1Ƿѹ������ѹ����ʧ��
#define CFM_APP_SET_PSPC1_QYDZDY_FAIL 0x0059
//�ֻ�����PSPC1�����Ͽ�����ʱ������ɹ�
#define CFM_APP_SET_PSPC1_GLDKDZSJ_OK 0x0005a
//�ֻ�����PSPC1�����Ͽ�����ʱ�����ʧ��
#define CFM_APP_SET_PSPC1_GLDKDZSJ_FAIL 0x005b
//�ֻ�����PSPC1��ѹ/Ƿѹ�Ͽ�����ʱ������ɹ�
#define CFM_APP_SET_PSPC1_GYQYDKDZSJ_OK 0x005c
//�ֻ�����PSPC1��ѹ/Ƿѹ�Ͽ�����ʱ�����ʧ��
#define CFM_APP_SET_PSPC1_GYQYDKDZSJ_FAIL 0x005d
//�ֻ�����PSPC1�Զ��غ�բʱ������ɹ�
#define CFM_APP_SET_PSPC1_ZDCHZSJ_OK 0x005e
//�ֻ�����PSPC1�Զ��غ�բʱ������ɹ�
#define CFM_APP_SET_PSPC1_ZDCHZSJ_FAIL 0x005f
//�ֻ�����PSPC1�ܵ�������ɹ�
#define CFM_APP_SET_PSPC1_ZDN_CLEAR_OK 0x0060
//�ֻ�����PSPC1�ܵ�������ʧ��
#define CFM_APP_SET_PSPC1_ZDN_CLEAR_FAIL 0x0061
//�ֻ�����PSPC1��·1��������ɹ�
#define CFM_APP_SET_PSPC1_FL1DN_CLEAR_OK 0x0062
//�ֻ�����PSPC1��·1��������ʧ��
#define CFM_APP_SET_PSPC1_FL1DN_CLEAR_FAIL 0x0063
//�ֻ�����PSPC1��·2��������ɹ�
#define CFM_APP_SET_PSPC1_FL2DN_CLEAR_OK 0x0064
//�ֻ�����PSPC1��·2��������ʧ��
#define CFM_APP_SET_PSPC1_FL2DN_CLEAR_FAIL 0x0065
//�ֻ�����PSPC1��·3��������ɹ�
#define CFM_APP_SET_PSPC1_FL3DN_CLEAR_OK 0x0066
//�ֻ�����PSPC1��·3��������ʧ��
#define CFM_APP_SET_PSPC1_FL3DN_CLEAR_FAIL 0x0067
//�ֻ�����PSPC1ʱ��У׼�ɹ�
#define CFM_APP_SET_PSPC1_CLOCK_OK 0x0068
//�ֻ�����PSPC1ʱ��У׼ʧ��
#define CFM_APP_SET_PSPC1_CLOCK_FAIL 0x0069
//�ֻ�����PSPC1����У׼�ɹ�
#define CFM_APP_SET_PSPC1_DATE_OK 0x006a
//�ֻ�����PSPC1����У׼ʧ��
#define CFM_APP_SET_PSPC1_DATE_FAIL 0x006b
//�ֻ�����PSPC1wifi���ӳɹ�
#define CFM_APP_SET_PSPC1_WIFI_OK 0x006c
//�ֻ�����PSPC1wifi����ʧ��
#define CFM_APP_SET_PSPC1_WIFI_FAIL 0x006d
//�ֻ�����PSPC1wifi������ʼʱ��ɹ�
#define CFM_APP_SET_PSPC1_WIFI_STIME_OK 0x006e
//�ֻ�����PSPC1wifi������ʼʱ��ʧ��
#define CFM_APP_SET_PSPC1_WIFI_STIME_FAIL 0x006f
//�ֻ�����PSPC1wifi������ֹʱ��ɹ�
#define CFM_APP_SET_PSPC1_WIFI_ETIME_OK 0x0070
//�ֻ�����PSPC1wifi������ֹʱ��ʧ��
#define CFM_APP_SET_PSPC1_WIFI_ETIME_FAIL 0x0071
//�ֻ���ȡPSPC1�ռ���Ϣ�ɹ�
#define CFM_APP_GET_PSPC1_RECORD_OK 0x0072
//�ֻ���ȡPSPC1�ռ���Ϣʧ��
#define CFM_APP_GET_PSPC1_RECORD_FAIL 0x0073
//�ֻ��յ�PSPC1©��澯��Ϣ�ɹ�
#define CFM_APP_GET_PSPC1_ALARM_LD_OK 0x0074
//�ֻ��յ�PSPC1©��澯��Ϣʧ��
#define CFM_APP_GET_PSPC1_ALARM_LD_FAIL 0x0075
//�ֻ��յ�PSPC1��ѹ�澯��Ϣ�ɹ�
#define CFM_APP_GET_PSPC1_ALARM_GY_OK 0x0076
//�ֻ��յ�PSPC1��ѹ�澯��Ϣʧ��
#define CFM_APP_GET_PSPC1_ALARM_GY_FAIL 0x0077
//�ֻ��յ�PSPC1��ѹ�澯��Ϣ�ɹ�
#define CFM_APP_GET_PSPC1_ALARM_DY_OK 0x0078
//�ֻ��յ�PSPC1��ѹ�澯��Ϣʧ��
#define CFM_APP_GET_PSPC1_ALARM_DY_FAIL 0x0079
//�ֻ��յ�PSPC1�����澯��Ϣ�ɹ�
#define CFM_APP_GET_PSPC1_ALARM_GL_OK 0x007a
//�ֻ��յ�PSPC1�����澯��Ϣʧ��
#define CFM_APP_GET_PSPC1_ALARM_GL_FAIL 0x007b
//�ֻ���ȡĳ�����ʹ������ɹ�
#define CFM_APP_GET_PSPC1_MNDNSYQK_OK 0x007c
//�ֻ���ȡĳ�����ʹ�����ʧ��
#define CFM_APP_GET_PSPC1_MNDNSYQK_FAIL 0x007d
#endif