#pragma once


// CMusicDlg 对话框

class CMusicDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMusicDlg)

public:
	CMusicDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMusicDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MUSIC_SET_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
