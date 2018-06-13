#pragma once

// CCommt 命令目标

class CCommt : public CSocket
{
public:
	CCommt();
	virtual ~CCommt();
//	virtual void OnClose(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//自定义函数
	BOOL ReceiveMsg(CMessage &cmsg);
public:
	// 发送打包信息
	bool SendMsg(CMessage& cmsg);
};


