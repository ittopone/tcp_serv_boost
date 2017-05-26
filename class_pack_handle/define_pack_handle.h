#ifndef __DEFINE_PACK_HANDLE_H__
#define __DEFINE_PACK_HANDLE_H__

/******************************************指令****************************************/
//手机app注册服务器指令（0x0001）
#define CMD_APP_REGISTER 0x0001
//手机app登录服务器指令（0x0002）
#define CMD_APP_LOGIN 0x0002
//手机修改用户昵称指令（0x0003）
#define CMD_APP_MODIFY_UNAME 0x0003
//手机修改用户密码指令（0x0004）
#define CMD_APP_MODIFY_PSWD 0x0004
/******************************************确认码****************************************/
//注册成功
#define CFM_APP_REGISTER_OK 0x0000
//注册失败
#define CFM_APP_REGISTER_FAIL 0x0001
//已注册
#define CFM_APP_REGISTER_EXIST 0x0002
//登录成功
#define CFM_APP_LOGIN_OK 0x0003
//登录失败
#define CFM_APP_LOGIN_FAIL 0x0004
//未注册
#define CFM_APP_NOT_REGISTER 0x0005
//修改用户昵称成功
#define CFM_APP_MODIFY_UNAME_OK 0x0006
//修改用户昵称失败
#define CFM_APP_MODIFY_UNAME_FAIL 0x0007
//修改用户密码成功
#define CFM_APP_MODIFY_PSWD_OK 0x0008
//修改用户密码失败
#define CFM_APP_MODIFY_PSWD_FAIL 0x0009
#endif