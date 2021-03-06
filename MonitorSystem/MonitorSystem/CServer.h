#pragma once

// CServer 命令目标
class CCommt;
class CServer : public CSocket
{
public:
	CServer();
	virtual ~CServer();

	BOOL StartServer();
	BOOL StopServer();
	BOOL Send(CMessage &msg);
private:
	CCommt * m_pClientTemp;
public:
	virtual void OnAccept(int nErrorCode);
};


