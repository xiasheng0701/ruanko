
// MainFrm.cpp: CMainFrame 类的实现
//

#include "stdafx.h"
#include "MonitorSystem.h"
#include "MonitorSystemView.h"
#include "CThumbView.h"
#include "CProcessListView.h"
#include "MainFrm.h"
#include "CServer.h"
#include "MonitorSystemDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_MESSAGE(WM_RECEIVE_MSG, &CMainFrame::OnReceiveMsg)
	ON_COMMAND(ID_SYSTEM_STARTSERVER, &CMainFrame::OnSystemStartserver)
	ON_COMMAND(ID_SYSTEM_STOPSERVER, &CMainFrame::OnSystemStopserver)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{	
	m_pServer = NULL;
	m_bSeverStart = FALSE;
	m_bAutoMenuEnable = FALSE;
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{

}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::Send(CMessage & msg)
{
	return m_pServer->Send(msg);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;
	this->SetTitle(_T("远程桌面监控系统"));

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



LRESULT CMainFrame::OnReceiveMsg(WPARAM wParam, LPARAM lParam)
{
	CMessage* pMsg = (CMessage*)wParam;//得到Cmessage对象的指针
	//进行消息的处理

	CMonitorSystemDoc* pDoc = (CMonitorSystemDoc*)this->GetActiveDocument();
	pDoc->MessageHandle(*pMsg);
	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	//创建拆分窗口
	if (!m_splitLeftWnd.CreateStatic(this, 1, 2))
	{
		this->MessageBox(_T("创建拆分窗口失败！"), _T("CMainFarme::OnCreateClient"));
		return FALSE;
	}
	//在m_splitLeftWnd拆分窗口上创建静态拆分窗口(2行1列),放在窗口的第二列
	if (!m_splitRightWnd.CreateStatic(&m_splitLeftWnd, 2, 1, WS_CHILD | WS_VISIBLE, m_splitLeftWnd.IdFromRowCol(0, 1)))
	{
		return FALSE;
	}
	if (!m_splitLeftWnd.CreateView(0, 0, RUNTIME_CLASS(CMonitorSystemView), CSize(0, 0), pContext))
	{
		return FALSE;
	}
	if (!m_splitRightWnd.CreateView(0, 0, RUNTIME_CLASS(CThumbView), CSize(0, 600), pContext))
	{
		return FALSE;
	}
	if (!m_splitRightWnd.CreateView(1, 0, RUNTIME_CLASS(CProcessListView), CSize(0, 0), pContext))
	{
		return FALSE;
	}
	m_splitLeftWnd.SetColumnInfo(0, 200, 0);//设置左右拆分窗口的宽度

	//保存各视图窗口的指针
	m_pMonitorSysView = (CMonitorSystemView*)m_splitLeftWnd.GetPane(0, 0);
	m_pCThumbView = (CThumbView*)m_splitRightWnd.GetPane(0, 0);
	m_pCProcessListView = (CProcessListView*)m_splitRightWnd.GetPane(1, 0);

	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}




void CMainFrame::OnSystemStartserver()
{
	// TODO: 在此添加命令处理程序代码
	CMonitorSystemDoc* pDoc = ((CMonitorSystemDoc*)this->GetActiveDocument());

	if (NULL == m_pServer)
	{
		m_pServer = new CServer();
	}

	if (m_pServer->StartServer())
	{
		pDoc->SetTitle(_T("服务器已启动"));//设置窗口标题
									 // 更新菜单可用性
		GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_SYSTEM_STARTSEVER, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_SYSTEM_STOPSERVER, MF_BYCOMMAND | MF_ENABLED);
		m_bSeverStart = TRUE;
	}
}


void CMainFrame::OnSystemStopserver()
{
	// TODO: 在此添加命令处理程序代码
	CMonitorSystemDoc* pDoc = ((CMonitorSystemDoc*)this->GetActiveDocument());
	pDoc->SetTitle(_T("服务器已关闭"));
	m_bSeverStart = FALSE;
	//更新菜单可用性
	GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_SYSTEM_STARTSEVER, MF_BYCOMMAND | MF_ENABLED);
	GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_SYSTEM_STOPSERVER, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

	if (NULL != m_pServer)
	{
		m_pServer->StopServer();//停止服务器
		m_pServer->Close();//关闭服务器套接字
		delete m_pServer;
		m_pServer = NULL;
		TRACE("CMainFrame::OnSystemStopserver()\n");
	}
}


void CMainFrame::OnDestroy()
{
	CFrameWnd::OnDestroy();

	// TODO: 在此处添加消息处理程序代码

	if (NULL != m_pServer)
	{
		m_pServer->StopServer();//停止服务器
		m_pServer->Close();//关闭服务器套接字
		delete m_pServer;
		m_pServer = NULL;
		TRACE("CMainFrame::OnDestroy()\n");
	}
}
