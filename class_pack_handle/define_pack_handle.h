#ifndef __DEFINE_PACK_HANDLE_H__
#define __DEFINE_PACK_HANDLE_H__

/******************************************ָ��****************************************/
//�ֻ�appע�������ָ�0x0001��
#define CMD_APP_REGISTER 0x0001
//�ֻ�app��¼������ָ�0x0002��
#define CMD_APP_LOGIN 0x0002
//�ֻ��޸��û��ǳ�ָ�0x0003��
#define CMD_APP_MODIFY_UNAME 0x0003
//�ֻ��޸��û�����ָ�0x0004��
#define CMD_APP_MODIFY_PSWD 0x0004
/******************************************ȷ����****************************************/
//ע��ɹ�
#define CFM_APP_REGISTER_OK 0x0000
//ע��ʧ��
#define CFM_APP_REGISTER_FAIL 0x0001
//��ע��
#define CFM_APP_REGISTER_EXIST 0x0002
//��¼�ɹ�
#define CFM_APP_LOGIN_OK 0x0003
//��¼ʧ��
#define CFM_APP_LOGIN_FAIL 0x0004
//δע��
#define CFM_APP_NOT_REGISTER 0x0005
//�޸��û��ǳƳɹ�
#define CFM_APP_MODIFY_UNAME_OK 0x0006
//�޸��û��ǳ�ʧ��
#define CFM_APP_MODIFY_UNAME_FAIL 0x0007
//�޸��û�����ɹ�
#define CFM_APP_MODIFY_PSWD_OK 0x0008
//�޸��û�����ʧ��
#define CFM_APP_MODIFY_PSWD_FAIL 0x0009
#endif