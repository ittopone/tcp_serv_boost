#ifndef __DEFINE_PSPC_H__
#define __DEFINE_PSPC_H__
//�豸���Ͷ���
#define DEV_TYPE_PSPC 'p'
//pspc1���豸ϵ�к�
#define DEV_SERIES_PSPC1 0x01
//pspc1���豸ID����
#define LEN_DEV_ID_PSPC1 6
/******************************************ָ��****************************************/
//�ֻ���ȡpspc�豸�б�ָ�0x0014��
#define CMD_APP_GET_PSPC_LIST 0x0014
/******************************************ȷ����****************************************/
//�ֻ���ȡPSPC�豸�б�ɹ�
#define CFM_APP_GET_PSPC_LIST_OK 0x0028
//�ֻ���ȡPSPC�豸�б�ʧ��
#define CFM_APP_GET_PSPC_LIST_FAIL 0x0029
#endif