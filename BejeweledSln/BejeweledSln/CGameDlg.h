#pragma once
#include "CGameLogic.h"

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HICON m_hIcon;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	void InitWnd();//初始化窗口
	void InitPicture();//初始化图片
	void DrawGameArea();//绘制地图						
	void GetElemLUxy(PICELEM picElem, int &nX, int &nY);// 计算图片元素左上角坐标
	CRect GetElemRect(PICELEM picElem);	//计算图片元素所在矩形区域
	void DrawTipFrame(PICELEM picElem);	//绘制边框
	void ChangeCartoon();	//交换动画
	void RemoeveCartoon();
	void DisplayScore();
	void GameOver();
	void Restart();
protected:
	CDC m_dcMem; //内存DC
	CDC m_dcBg;  //背景内存dc
	CDC m_dcMask;//掩码
	CDC m_dcElem;//图片
	CDC m_dcRemove;//消除
	CDC m_dcPause;
	CDC m_dcCache;

	CGameLogic m_GameLogic;
	CRect m_rtGame;

	bool m_bFirstElem;//是否为第一个图片
	PICELEM m_picElemFirst;//第一个图片
	PICELEM m_picElemSecond;//第二个图片
	CFont m_Font;//字体
	bool m_bPlaying;//游戏是否进行
	bool m_bPause;
public:
	afx_msg void OnPaint();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_stcScore;
	
	CProgressCtrl m_progTime;
	
	CButton m_btnTip;
	CButton m_btnPause;
	afx_msg void OnBnClickedBtnTip();
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnBnClickedBtnMenu();
};
