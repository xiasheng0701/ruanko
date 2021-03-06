#pragma once

// CCommt 命令目标
class CMessage;
class CCommt : public CSocket
{
public:
	CCommt(CWnd * pWnd);
	virtual ~CCommt();

	BOOL Connect();
private:
	CWnd * m_pWnd;
public:
	// 发送打包信息
	bool SendMsg(CMessage& cmsg);
	virtual void OnReceive(int nErrorCode);
	BOOL ReceiveMsg(CMessage &cmsg);
};


