// CServer.cpp: 实现文件
//

#include "stdafx.h"
#include "MonitorSystem.h"
#include "CServer.h"
#include "CCommt.h"


// CServer

CServer::CServer()
{
	m_pClientTemp = NULL;
}

CServer::~CServer()
{
}

BOOL CServer::StartServer()
{
	if (this->Create(9999)==FALSE)
	{
		::AfxMessageBox(_T("Failed to create the socket!"));
		TRACE("CServer::startServer():Failed to create the socket!\n");
		return FALSE;
	}
	if (this->Listen()==FALSE)
	{
		::AfxMessageBox(_T("Failed to listen!"));
		TRACE("CServer::startServer():Failed to lesten!\n");
		return FALSE;
	}

	::AfxMessageBox(_T("succeed!\n"));
	TRACE("CServer::startServer():succeed!\n");
	return TRUE;
}

BOOL CServer::StopServer()
{
	if (NULL!=m_pClientTemp)
	{
		TRACE("CServer::StopServer():m_pClientTemp->Close()\n");
		m_pClientTemp->Close();
		delete m_pClientTemp;
		m_pClientTemp = NULL;
	}
	this->Close();//关闭服务器套接字
	TRACE("CServer::StopServer(): succeed\n");
	return TRUE;
}

BOOL CServer::Send(CMessage & msg)
{
	if (NULL != m_pClientTemp)
	{
		m_pClientTemp->SendMsg(msg);
	}
	return FALSE;
}


// CServer 成员函数


void CServer::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CCommt* pClient = new CCommt();
	TRACE("pClient = 0x%p!\n", pClient);
	if (this->Accept(*pClient)==FALSE)
	{
		delete pClient;
		pClient = NULL;
	}
	else
	{
		CString strIP = _T("");
		UINT nPort = 0;
		//获取客户端的IP地址和端口号
		if (pClient->GetPeerName(strIP,nPort)==FALSE)
		{
			TRACE("CServer::OnAccept():GetPeerName() Error！\n");
		}
		else
		{
			if (NULL == m_pClientTemp)
			{
				delete m_pClientTemp;
				m_pClientTemp = NULL;
			}

			m_pClientTemp = pClient;//保存当前客户端的socket

		}
	}

	CSocket::OnAccept(nErrorCode);
}
