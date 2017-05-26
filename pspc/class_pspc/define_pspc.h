#ifndef __DEFINE_PSPC_H__
#define __DEFINE_PSPC_H__
//设备类型定义
#define DEV_TYPE_PSPC 'p'
//pspc1的设备系列号
#define DEV_SERIES_PSPC1 0x01
//pspc1的设备ID长度
#define LEN_DEV_ID_PSPC1 6
/******************************************指令****************************************/
//手机获取pspc设备列表指令（0x0014）
#define CMD_APP_GET_PSPC_LIST 0x0014
/******************************************确认码****************************************/
//手机获取PSPC设备列表成功
#define CFM_APP_GET_PSPC_LIST_OK 0x0028
//手机获取PSPC设备列表失败
#define CFM_APP_GET_PSPC_LIST_FAIL 0x0029
#endif