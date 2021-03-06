// CCommt.cpp: 实现文件
//

#include "stdafx.h"
#include "MonitorSystem.h"
#include "CCommt.h"


// CCommt

CCommt::CCommt()
{
}

CCommt::~CCommt()
{
}


// CCommt 成员函数


//void CCommt::OnClose(int nErrorCode)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	CString strIP = _T("");
//	UINT nPort = 0;
//	this->GetPeerName(strIP, nPort);
//	CString strIPPort = _T("");
//	strIPPort.Format(_T("%s:%04d"), strIP, nPort);
//
//	CSocket::OnClose(nErrorCode);
//}


void CCommt::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CString strIP = _T("");
	UINT nPort = 0;
	this->GetPeerName(strIP, nPort);
	CString strIPPort = _T("");
	strIPPort.Format(_T("%s:%04d"), strIP, nPort);
#ifdef _DEBUG
	char szIP[20] = { 0 };
	int nStrIPLen = strIP.GetLength();
	int nszIPlen = sizeof(szIP) / sizeof(szIP[0]);
	CUtils::ToChars(szIP, strIP, nszIPlen);
	TRACE("CCommt::OnClose():Client IP = %s, PORT = %d exit\n", szIP, nPort);
#endif // _DEBUG


	CSocket::OnClose(nErrorCode);
}


void CCommt::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CMessage msg;
	if (this->ReceiveMsg(msg)==TRUE)
	{
		TRACE(_T("CCommt::OnReceive():将收到的消息发送个MainFame类!\n"));
		AfxGetMainWnd()->SendMessage(WM_RECEIVE_MSG, (WPARAM)&msg, NULL);
	}
	else
	{
		TRACE(_T("CCommt::OnReceive():接收消息失败!\n"));
	}
	CSocket::OnReceive(nErrorCode);
}

BOOL CCommt::ReceiveMsg(CMessage & msg)
{
	//1.接受客户端的消息，先接受消息头
	MESSAGE sMsg;
	int nMsgLen = CSocket::Receive(&sMsg, sizeof(MESSAGE));
	msg.SetMsg(sMsg);//拷贝消息
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

bool CCommt::SendMsg(CMessage & cmsg)
{
	// TODO: 在此处添加实现代码.
	MESSAGE sMsg;//得到MESSAGE结构体
	memset(&sMsg, NULL, sizeof(MESSAGE));
	sMsg.type = cmsg.GetMsgType();
	sMsg.status = cmsg.GetMsgStatus();
	sMsg.data_total_size = cmsg.GetDateTotalSize();
	int nMaxLen = sizeof(sMsg.security) / sizeof(sMsg.security[0]);
	CUtils::ToChars(sMsg.security, cmsg.GetSecurity(), nMaxLen);
	//验证处理
	if (cmsg.GetDateTotalSize()<=0)//此时发送的是命令消息（不带数据区）
	{
		TRACE("CCommt::SendMsg():消息头发送成功");
		return TRUE;
	}

	//错误处理

	//-----------------------------发送消息头 end--------------------------------
	return TRUE;
}
