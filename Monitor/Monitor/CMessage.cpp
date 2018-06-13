#include "stdafx.h"
#include "CMessage.h"


CMessage::CMessage()
{
	m_strSession = _T("");
	m_nMsgId = -1;
	m_nDateTotalSize = 0;
	m_nType = MSGTYPE(0);
	m_nStatus = MSGSTATUS(0);
}

CMessage::CMessage(MESSAGE & sMsg)
{
	m_strSession = _T("");
	m_nMsgId = -1;
	m_nDateTotalSize = 0;
	m_nType = MSGTYPE(0);
	m_nStatus = MSGSTATUS(0);

	this->SetMsg(sMsg);
}


CMessage::~CMessage()
{
}

void CMessage::SetSession(const CString & strSession)
{
	m_strSession = strSession;
}

CString CMessage::GetSession()
{
	return m_strSession;
}

void CMessage::SetSecurity(const CString & strSecurity)
{
	m_strSecurity = strSecurity;
}

CString CMessage::GetSecurity()
{
	return m_strSecurity;
}

void CMessage::SetMsgId(const int & nMsgId)
{
	m_nMsgId = nMsgId;
}

int CMessage::GetMsgId()
{
	return m_nMsgId;
}

void CMessage::SetMsgType(const MSGTYPE & nType)
{
	m_nType = nType;
}

MSGTYPE CMessage::GetMsgType()
{
	return m_nType;
}

void CMessage::SetMsgStatus(const MSGSTATUS & nStatus)
{
	m_nStatus = nStatus;
}

MSGSTATUS CMessage::GetMsgStatus()
{
	return m_nStatus;
}

void CMessage::SetDateTotalSize(const size_t & nSize)
{
	m_nDateTotalSize = nSize;
}

size_t CMessage::GetDateTotalSize()
{
	return m_nDateTotalSize;
}

void CMessage::SetMsg(MESSAGE sMsg)
{
	m_strSession = sMsg.session;
	m_nMsgId = sMsg.msg_id;
	m_nDateTotalSize = sMsg.data_total_size;
	m_nType = sMsg.type;
	m_nStatus = sMsg.status;
	m_strSecurity = sMsg.security;
}
