#pragma once


// CMenuDlg 对话框

class CMenuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMenuDlg)

public:
	CMenuDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMenuDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MENU_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnPrimenu();
	afx_msg void OnBnClickedBtnReturn();
	afx_msg void OnBnClickedBtnRestart();
	afx_msg void OnBnClickedBtnSetgame();
	afx_msg void OnBnClickedBtnExit();
};
