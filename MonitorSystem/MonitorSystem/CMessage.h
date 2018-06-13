#pragma once
#include "MessageType.h"
class CMessage
{
public:
	CMessage();
	CMessage(MESSAGE &sMsg);
	~CMessage();
	void SetSession(const CString &strSession);
	void SetSecurity(const CString &strSecurity);
	void SetMsgId(const int &nMsgId);
	void SetMsgType(const MSGTYPE &nType);
	void SetMsgStatus(const MSGSTATUS &nStatus);
	void SetDateTotalSize(const size_t &nSize);

	CString GetSession();
	CString GetSecurity();
	int GetMsgId();
	MSGTYPE GetMsgType();
	MSGSTATUS GetMsgStatus();
	size_t GetDateTotalSize();
	void SetMsg(MESSAGE sMsg);
private:
	CString		m_strSession;	//��ǿͻ��ˣ����IP��ַ�Ͷ˿ڣ�
	CString		m_strSecurity;	//��֤�롣������û��������룩
	int			m_nMsgId;		//��Ϣ��ʶ
	MSGTYPE		m_nType;			//��Ϣ����
	MSGSTATUS	m_nStatus;		//��Ϣ״̬
	size_t		m_nDateTotalSize;//�����ܴ�С
};
