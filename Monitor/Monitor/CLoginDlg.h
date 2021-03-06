#pragma once
#include "CCommt.h"

// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	// 连接服务器
	bool ConnectServer();
	// 断开连接
	bool DisconnectServer();
	bool DoUserLogin(CString strUserName, CString strPassword);
	afx_msg LRESULT Receive(WPARAM wParam, LPARAM lParam);
private:
	//自定义变量
	CString m_strUserName;// 用户名
	CString m_strPassword;// 密码
	CString m_strIPPort;// 客户端IP地址和端口号
	CCommt* m_pCommt; //客户端socket
public:
	afx_msg void OnOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
};
