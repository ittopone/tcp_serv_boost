#ifndef __DEFINE_PSPC1_H__
#define __DEFINE_PSPC1_H__
/******************************************指令****************************************/
//Pspc1登录服务器指令（0x0024）
#define CMD_PSPC1_LOGIN 0x0024
//手机绑定pspc1设备指令（0x0025）
#define CMD_APP_BIND_PSPC1 0x0025
//手机获取pspc1设备运行状态指令（0x0026）
#define CMD_APP_GET_PSPC1_STATUS 0x0026
//手机获取pspc1设备设置参数指令（0x0027）
#define CMD_APP_GET_PSPC1_SET_ARGS 0x0027
//手机设置pspc1设备过流动作电流参数指令（0x0028）
#define CMD_APP_SET_PSPC1_GLDZDL_ARG 0x0028
//手机设置pspc1设备漏流不动作电流参数指令（0x0029）
#define CMD_APP_SET_PSPC1_LLBDZDL_ARG 0x0029
//手机设置pspc1设备漏流动作电流参数指令（0x002a）
#define CMD_APP_SET_PSPC1_LLDZDL_ARG 0x002a
//手机设置pspc1设备过压动作电压参数指令（0x002b）
#define CMD_APP_SET_PSPC1_GYDZDY_ARG 0x002b
//手机设置pspc1设备欠压动作电压参数指令（0x002c）
#define CMD_APP_SET_PSPC1_QYDZDY_ARG 0x002c
//手机设置pspc1设备过流断开动作时间参数指令（0x002d）
#define CMD_APP_SET_PSPC1_GLDKDZSJ_ARG 0x002d
//手机设置pspc1设备过压/欠压断开动作时间参数指令（0x002e）
#define CMD_APP_SET_PSPC1_GYQYDKDZSJ_ARG 0x002e
//手机设置pspc1设备自动重合闸时间参数指令（0x002f）
#define CMD_APP_SET_PSPC1_ZDCHZSJ_ARG 0x002f
//手机设置pspc1设备总电能清零指令（0x0030）
#define CMD_APP_SET_PSPC1_ZDN_CLEAR 0x0030
//手机设置pspc1设备分路1电能清零指令（0x0031）
#define CMD_APP_SET_PSPC1_FL1DN_CLEAR 0x0031
//手机设置pspc1设备分路2电能清零指令（0x0032）
#define CMD_APP_SET_PSPC1_FL2DN_CLEAR 0x0032
//手机设置pspc1设备分路3电能清零指令（0x0033）
#define CMD_APP_SET_PSPC1_FL3DN_CLEAR 0x0033
//手机设置pspc1设备时钟校准指令（0x0034）
#define CMD_APP_SET_PSPC1_CLOCK 0x0034
//手机设置pspc1设备日历校准指令（0x0035）
#define CMD_APP_SET_PSPC1_DATE 0x0035
//手机设置pspc1设备WiFi连接指令（0x0036）
#define CMD_APP_SET_PSPC1_WIFI 0x0036
//手机设置pspc1设备WiFi连接起始时间指令（0x0037）
#define CMD_APP_SET_PSPC1_WIFI_STIME 0x0037
//手机设置pspc1设备WiFi连接终止时间指令（0x0038）
#define CMD_APP_SET_PSPC1_WIFI_ETIME 0x0038
//手机获取pspc1设备日记信息指令（0x0039）
#define CMD_APP_GET_PSPC1_RECORD 0x0039
//Pspc1向手机发送漏电告警指令（0x003a）
#define CMD_PSPC1_SEND_ALARM_LD 0x003a
//Pspc1向手机发送高压告警指令（0x003b）
#define CMD_PSPC1_SEND_ALARM_GY 0x003b
//Pspc1向手机发送低压告警指令（0x003c）
#define CMD_PSPC1_SEND_ALARM_DY 0x003c
//Pspc1向手机发送过流告警指令（0x003d）
#define CMD_PSPC1_SEND_ALARM_GL	0x003d
//手机向pspc1发送获取某年电能使用情况指令（0x003e）
#define CMD_APP_GET_PSPC1_MNDNSYQK 0x003e
/******************************************确认码****************************************/
//Pspc1登录服务器成功
#define CFM_PSPC1_LOGIN_OK 0x0048
//Pspc1登录服务器失败
#define CFM_PSPC1_LOGIN_FAIL 0x0049
//手机绑定PSPC1设备成功
#define CFM_APP_BIND_PSPC1_OK 0x004a
//手机绑定PSPC1设备失败
#define CFM_APP_BIND_PSPC1_FAIL 0x004b
//手机获取pspc1设备运行状态成功
#define CFM_APP_GET_PSPC1_STATUS_OK 0x004c
//手机获取pspc1设备运行状态失败
#define CFM_APP_GET_PSPC1_STATUS_FAIL 0x004d
//手机获取pspc1设置参数成功
#define CFM_APP_GET_PSPC1_SET_ARGS_OK 0x004e
//手机获取pspc1设置参数失败
#define CFM_APP_GET_PSPC1_SET_ARGS_FAIL 0x004f
//手机设置pspc1过流动作电流参数成功
#define CFM_APP_SET_PSPC1_GLDZDL_OK 0x0050
//手机设置pspc1过流动作电流参数失败
#define CFM_APP_SET_PSPC1_GLDZDL_FAIL 0x0051
//手机设置PSPC1漏流不动作电流参数成功
#define CFM_APP_SET_PSPC1_LLBDZDL_OK 0x0052
//手机设置PSPC1漏流不动作电流参数失败
#define CFM_APP_SET_PSPC1_LLBDZDL_FAIL 0x0053
//手机设置PSPC1漏流动作电流参数成功
#define CFM_APP_SET_PSPC1_LLDZDL_OK 0x0054
//手机设置PSPC1漏流动作电流参数失败
#define CFM_APP_SET_PSPC1_LLDZDL_FAIL 0x0055
//手机设置PSPC1过压动作电压参数成功
#define CFM_APP_SET_PSPC1_GYDZDY_OK 0x0056
//手机设置PSPC1过压动作电压参数失败
#define CFM_APP_SET_PSPC1_GYDZDY_FAIL 0x0057
//手机设置PSPC1欠压动作电压参数成功
#define CFM_APP_SET_PSPC1_QYDZDY_OK 0x0058
//手机设置PSPC1欠压动作电压参数失败
#define CFM_APP_SET_PSPC1_QYDZDY_FAIL 0x0059
//手机设置PSPC1过流断开动作时间参数成功
#define CFM_APP_SET_PSPC1_GLDKDZSJ_OK 0x0005a
//手机设置PSPC1过流断开动作时间参数失败
#define CFM_APP_SET_PSPC1_GLDKDZSJ_FAIL 0x005b
//手机设置PSPC1过压/欠压断开动作时间参数成功
#define CFM_APP_SET_PSPC1_GYQYDKDZSJ_OK 0x005c
//手机设置PSPC1过压/欠压断开动作时间参数失败
#define CFM_APP_SET_PSPC1_GYQYDKDZSJ_FAIL 0x005d
//手机设置PSPC1自动重合闸时间参数成功
#define CFM_APP_SET_PSPC1_ZDCHZSJ_OK 0x005e
//手机设置PSPC1自动重合闸时间参数成功
#define CFM_APP_SET_PSPC1_ZDCHZSJ_FAIL 0x005f
//手机设置PSPC1总电能清零成功
#define CFM_APP_SET_PSPC1_ZDN_CLEAR_OK 0x0060
//手机设置PSPC1总电能清零失败
#define CFM_APP_SET_PSPC1_ZDN_CLEAR_FAIL 0x0061
//手机设置PSPC1分路1电能清零成功
#define CFM_APP_SET_PSPC1_FL1DN_CLEAR_OK 0x0062
//手机设置PSPC1分路1电能清零失败
#define CFM_APP_SET_PSPC1_FL1DN_CLEAR_FAIL 0x0063
//手机设置PSPC1分路2电能清零成功
#define CFM_APP_SET_PSPC1_FL2DN_CLEAR_OK 0x0064
//手机设置PSPC1分路2电能清零失败
#define CFM_APP_SET_PSPC1_FL2DN_CLEAR_FAIL 0x0065
//手机设置PSPC1分路3电能清零成功
#define CFM_APP_SET_PSPC1_FL3DN_CLEAR_OK 0x0066
//手机设置PSPC1分路3电能清零失败
#define CFM_APP_SET_PSPC1_FL3DN_CLEAR_FAIL 0x0067
//手机设置PSPC1时钟校准成功
#define CFM_APP_SET_PSPC1_CLOCK_OK 0x0068
//手机设置PSPC1时钟校准失败
#define CFM_APP_SET_PSPC1_CLOCK_FAIL 0x0069
//手机设置PSPC1日历校准成功
#define CFM_APP_SET_PSPC1_DATE_OK 0x006a
//手机设置PSPC1日历校准失败
#define CFM_APP_SET_PSPC1_DATE_FAIL 0x006b
//手机设置PSPC1wifi连接成功
#define CFM_APP_SET_PSPC1_WIFI_OK 0x006c
//手机设置PSPC1wifi连接失败
#define CFM_APP_SET_PSPC1_WIFI_FAIL 0x006d
//手机设置PSPC1wifi连接起始时间成功
#define CFM_APP_SET_PSPC1_WIFI_STIME_OK 0x006e
//手机设置PSPC1wifi连接起始时间失败
#define CFM_APP_SET_PSPC1_WIFI_STIME_FAIL 0x006f
//手机设置PSPC1wifi连接终止时间成功
#define CFM_APP_SET_PSPC1_WIFI_ETIME_OK 0x0070
//手机设置PSPC1wifi连接终止时间失败
#define CFM_APP_SET_PSPC1_WIFI_ETIME_FAIL 0x0071
//手机获取PSPC1日记信息成功
#define CFM_APP_GET_PSPC1_RECORD_OK 0x0072
//手机获取PSPC1日记信息失败
#define CFM_APP_GET_PSPC1_RECORD_FAIL 0x0073
//手机收到PSPC1漏电告警信息成功
#define CFM_APP_GET_PSPC1_ALARM_LD_OK 0x0074
//手机收到PSPC1漏电告警信息失败
#define CFM_APP_GET_PSPC1_ALARM_LD_FAIL 0x0075
//手机收到PSPC1高压告警信息成功
#define CFM_APP_GET_PSPC1_ALARM_GY_OK 0x0076
//手机收到PSPC1高压告警信息失败
#define CFM_APP_GET_PSPC1_ALARM_GY_FAIL 0x0077
//手机收到PSPC1低压告警信息成功
#define CFM_APP_GET_PSPC1_ALARM_DY_OK 0x0078
//手机收到PSPC1低压告警信息失败
#define CFM_APP_GET_PSPC1_ALARM_DY_FAIL 0x0079
//手机收到PSPC1过流告警信息成功
#define CFM_APP_GET_PSPC1_ALARM_GL_OK 0x007a
//手机收到PSPC1过流告警信息失败
#define CFM_APP_GET_PSPC1_ALARM_GL_FAIL 0x007b
//手机获取某年电能使用情况成功
#define CFM_APP_GET_PSPC1_MNDNSYQK_OK 0x007c
//手机获取某年电能使用情况失败
#define CFM_APP_GET_PSPC1_MNDNSYQK_FAIL 0x007d
#endif