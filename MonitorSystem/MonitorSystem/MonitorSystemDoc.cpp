
// MonitorSystemDoc.cpp: CMonitorSystemDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MonitorSystem.h"
#endif

#include "MonitorSystemDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMonitorSystemDoc

IMPLEMENT_DYNCREATE(CMonitorSystemDoc, CDocument)

BEGIN_MESSAGE_MAP(CMonitorSystemDoc, CDocument)
END_MESSAGE_MAP()


// CMonitorSystemDoc 构造/析构

CMonitorSystemDoc::CMonitorSystemDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMonitorSystemDoc::~CMonitorSystemDoc()
{
}

BOOL CMonitorSystemDoc::MessageHandle(CMessage & msg)
{
	if (this->ValidSecurity(msg)==FALSE)
	{
		TRACE("CMonitorSystemDoc::MessageHandle:ValidSecurity失败!\n");
		TRACE("CMonitorSystemDoc::MessageHandle:发送用户登陆失败消息!\n");
		//发送用户登陆失败的消息
		CMessage cmsg;
		cmsg.SetMsgType(MT_LOGIN);
		cmsg.SetMsgStatus(MS_FAILED);
		cmsg.SetSession(msg.GetSession());
		cmsg.SetSecurity(msg.GetSecurity());
		// 发送用户登陆失败的消息
		((CMainFrame*)AfxGetMainWnd())->Send(cmsg);
		return FALSE;
	}
	switch (msg.GetMsgType())
	{
	case MT_LOGIN:
	{
		this->DoLogin(msg);
		TRACE("CMonitorSystemDoc::MessageHandle:MT_LOGIN!\n");
		break;
	}
	default:
		break;
	}
	return TRUE;
}

BOOL CMonitorSystemDoc::ValidSecurity(CMessage & sMsg)
{
	CString strUserNameMatch = _T("ruanko");//要匹配的用户名
	CString strPasswordMatch = _T("123456");//要匹配的密码
	//得到用户名和密码信息
	CString strContent = sMsg.GetSecurity();
	CString strTemp = strContent;
	CString strSeparator = _T("#%@");
	int nIndex = strTemp.Find(strSeparator);
	CString strUserName = CUtils::GetSubString(strTemp, 0, nIndex);
	nIndex = strTemp.Find(strSeparator);
	CString strPassword = CUtils::GetSubString(strTemp, 0, nIndex);
	if ((strUserName== strUserNameMatch)&&(strPassword== strPasswordMatch))
	{
		TRACE(" CMonitorSystemDoc::ValidSecurity():用户信息验证成功！\n");
		return TRUE;
	}
	else
	{
		TRACE(" CMonitorSystemDoc::ValidSecurity():用户信息验证失败！\n");
		return FALSE;
	}
}

BOOL CMonitorSystemDoc::DoLogin(CMessage & msg)
{
	//发送用户登陆成功的反馈消息
	TRACE(" CMonitorSystemDoc::DoLogin():用户登陆成功反馈消息！\n");
	CMessage cmsg;
	cmsg.SetMsgType(MT_LOGIN);
	cmsg.SetMsgStatus(MS_SUCCEED);
	cmsg.SetSession(msg.GetSession());
	cmsg.SetSecurity(msg.GetSecurity());
	((CMainFrame*)AfxGetMainWnd())->Send(cmsg);
	return TRUE;
}

BOOL CMonitorSystemDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	this->SetTitle(_T("服务器未启动"));
	return TRUE;
}




// CMonitorSystemDoc 序列化

void CMonitorSystemDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMonitorSystemDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMonitorSystemDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMonitorSystemDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMonitorSystemDoc 诊断

#ifdef _DEBUG
void CMonitorSystemDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMonitorSystemDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMonitorSystemDoc 命令
