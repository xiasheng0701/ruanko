
// MonitorDlg.h: 头文件
//

#pragma once
#include "CCommt.h"

// CMonitorDlg 对话框
class CMonitorDlg : public CDialogEx
{
// 构造
public:
	CMonitorDlg(CWnd* pParent = nullptr);	// 标准构造函数
	CString m_strIPPort;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONITOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	//自定义变量
	CCommt* m_pCommt;
private:
	BOOL ConnectServer();//连接服务器
	void DisConnectServer();//断开连接
public:
	afx_msg void OnDestroy();
};
