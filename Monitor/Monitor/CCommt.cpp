// CCommt.cpp: 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "CCommt.h"


// CCommt

CCommt::CCommt(CWnd * pWnd) : m_pWnd(pWnd)
{
}

CCommt::~CCommt()
{
}

BOOL CCommt::Connect()
{
	if (this->Create() == FALSE)
	{
		TRACE("Failed to create the socket!\n");
		return FALSE;
	}
	//服务器端IP地址和端口号
	CString strIP = _T("192.168.171.164");
	UINT nPort = 9999;
	if (CSocket::Connect(strIP,nPort)==FALSE)
	{
		TRACE("Failed to Connect!\n");
		return FALSE;
	}

	TRACE("Succeed to Connect the Server!\n");
	return TRUE;
}


// CCommt 成员函数


// 发送打包信息
bool CCommt::SendMsg(CMessage& msg)
{
	// TODO: 在此处添加实现代码.
	MESSAGE sMsg;//得到MESSAGE结构体
	memset(&sMsg, NULL, sizeof(MESSAGE));
	sMsg.type = msg.GetMsgType();
	sMsg.status = msg.GetMsgStatus();
	sMsg.data_total_size = msg.GetDateTotalSize();
	int nMaxLen = sizeof(sMsg.security) / sizeof(sMsg.security[0]);
	CUtils::ToChars(sMsg.security, msg.GetSecurity(), nMaxLen);
	//发送消息头
	int nLen = CSocket::Send(&sMsg, sizeof(MESSAGE));

	//错误处理

	//-----------------------------发送消息头 end--------------------------------
	return TRUE;
}


void CCommt::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CMessage msg;
	if (this->ReceiveMsg(msg) == TRUE)
	{
		
		m_pWnd->SendMessage(WM_RECEIVE_MSG, (WPARAM)&msg, NULL);
	}
	else
	{
		TRACE(_T("CCommt::OnReceive():接收消息失败!\n"));
	}
	TRACE(_T("CSocket::OnReceive(nErrorCode);\n"));
	CSocket::OnReceive(nErrorCode);
}

BOOL CCommt::ReceiveMsg(CMessage & cmsg)
{
	MESSAGE sMsg;
	int nMsgLen = CSocket::Receive(&sMsg, sizeof(MESSAGE));
	cmsg.SetMsg(sMsg);//拷贝消息
	BOOL bFlag = FALSE;
	//2.消息验证
	//3.判断收到的数据是否正确
	//4.判断是否还有数据区待接受
	if (sMsg.data_total_size == 0)
	{
		bFlag = TRUE;
		return bFlag;
	}
	return bFlag;
}
