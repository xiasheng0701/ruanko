// CLoginDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN_DIALOG1, pParent)
	,m_pCommt(NULL)
	,m_strIPPort(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_strUserName);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_MESSAGE(WM_RECEIVE_MSG, &CLoginDlg::Receive)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnOk)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


// 连接服务器
bool CLoginDlg::ConnectServer()
{
	// TODO: 在此处添加实现代码.
	if (NULL == m_pCommt)
	{
		m_pCommt = new CCommt(this);
		if (m_pCommt->Connect())
		{
			CString strIP = _T("");
			UINT nPort = 0;
			m_pCommt->GetSockName(strIP, nPort);
			m_strIPPort.Format(_T("%s:%04d"), strIP, nPort);
		}
		else
		{
			delete m_pCommt;
			m_pCommt = NULL;
			return FALSE;
		}
	}
	return true;
}


// 断开连接
bool CLoginDlg::DisconnectServer()
{
	// TODO: 在此处添加实现代码
	if (NULL != m_pCommt)
	{
		m_pCommt->Close();
		delete m_pCommt;
		m_pCommt = NULL;
		TRACE(_T("断开与服务器的连接!\n"));
		return true;
	}
	return false;
}

bool CLoginDlg::DoUserLogin(CString strUserName, CString strPassword)
{
	CString strSeparator = _T("#%@");//分隔符
	CString strSecurity = strUserName + strSeparator + strPassword + strSeparator;
	CMessage cmsg;
	cmsg.SetMsgType(MT_LOGIN);
	cmsg.SetMsgStatus(MS_NORMAL);
	cmsg.SetSession(m_strIPPort);
	cmsg.SetSecurity(strSecurity);

	if (m_pCommt->SendMsg(cmsg))
	{
		return true;
	}
	return false;
}

LRESULT CLoginDlg::Receive(WPARAM wParam, LPARAM lParam)
{
	CMessage* pMsg = (CMessage*)wParam;//得到Cmessage对象的指针
	if (pMsg->GetMsgStatus()==MS_SUCCEED)
	{
		TRACE("登陆验证成功!\n");
		this->DisconnectServer();//验证成功后断开连接
		CDialogEx::OnOK();//销毁登陆对话框
	}
	else
	{
		TRACE("登陆验证失败!\n");
		this->MessageBox(_T("登陆失败"), _T("登陆"));
		if (NULL != m_pCommt)
		{
			m_pCommt->Close();
			delete m_pCommt;
			m_pCommt = NULL;
		}
	}
	return 0;
}


void CLoginDlg::OnOk()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData(TRUE);
	if (m_strUserName.IsEmpty() || m_strPassword.IsEmpty())
	{
		this->MessageBox(_T("用户名、密码不能为空!\n"), _T("Error"));
		return;
	}
	if (this->ConnectServer()==false)
	{
		this->MessageBox(_T("连接服务器失败！"), _T("ERROR"));
		return;
	}
	if (this->DoUserLogin(m_strUserName, m_strPassword) == FALSE)
	{
		this->MessageBox(_T("用户登录失败！"), _T("ERROR"));
		return;
	}
	TRACE(_T("连接服务器成功！\n"));
	//CDialogEx::OnOK();
}


BOOL CLoginDlg::OnInitDialog()
{
	// TODO:  在此添加额外的初始化
	
	CDialogEx::OnInitDialog();
	//添加任务栏图标
	this->ModifyStyleEx(0, WS_EX_APPWINDOW);
	this->CenterWindow();
	this->ShowWindow(SW_SHOW);
	//禁止改变对话框大小
	this->ModifyStyle(WS_THICKFRAME, 0, SWP_FRAMECHANGED | SWP_DRAWFRAME);
	//禁用菜单项
	GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_CHANGE_USER, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_USER_ONLINE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_USER_OFFLINE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::OnDestroy()
{
	this->DisconnectServer();
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}
