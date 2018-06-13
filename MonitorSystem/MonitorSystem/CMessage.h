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
	CString		m_strSession;	//标记客户端（存放IP地址和端口）
	CString		m_strSecurity;	//验证码。（存放用户名和密码）
	int			m_nMsgId;		//消息标识
	MSGTYPE		m_nType;			//消息类型
	MSGSTATUS	m_nStatus;		//消息状态
	size_t		m_nDateTotalSize;//数据总大小
};
