#pragma once

#define MAX_DATA_SIZE 2048
///////////////////////////////////////////////////////////////////////
//������ϢЭ��ṹ��������
///////////////////////////////////////////////////////////////////////

//����Ϣ���ͣ�����Լ��MESSAGE�ṹ����type��ֵ
enum MSGTYPE
{
	MT_LOGIN = 1,	//�ͻ��˵�½
	MT_CLIENT_DISCONNECT = 2,	//�ͻ��˶Ͽ�����
	MT_SERVER_DISCONNECT = 3,	//�Ͽ�����������
};

//�쳣����
enum MSGSTATUS
{
	MS_NORMAL = 1,	//����״̬
	MS_FAILED = 2,	//��֤ʧ��
	MS_SUCCEED = 3,	//��֤�ɹ�
};

/** ����Ϣ:������Ϣ�ṹ��
** ˼·:��Ϊ���Ľ�����Ϣ�����ǵ��󲿷ֵ���Ϣ��ֻ�в����Ϳ���ȷ����
** Ϊ�˼��ٿ��ַ����Ĵ������١���������Ϣ�ṹ���嵽��Сװ̬��
** ���ܽ���󲿷ֵ�ͨѶ����
**/
struct MESSAGE
{
	char			session[32];			//���IP��ַ�Ͷ˿ں�
	MSGTYPE		type;				//��Ϣ����
	MSGSTATUS	status;				//Ӧ��״̬
	int			msg_id;				//��Ϣ���кţ�ÿһ��ͨѶ����һ�����к�
	size_t		data_total_size;		//�����ܳ���
	char			security[64];		//��֤�롣������û��������룩
};

//������ݰ�
struct MSGDATA
{
	char			session[32];			//���IP��ַ�Ͷ˿ں�
	int			msg_id;				//��Ϣ���кţ�ÿһ��ͨѶ����һ�����к�
	int			msg_no;				//��Ϣ��ţ���1��ʼ��ţ�
	int			data_size;			//���ݳ���
	//char			data[MAX_DATA_SIZE];//������

};
