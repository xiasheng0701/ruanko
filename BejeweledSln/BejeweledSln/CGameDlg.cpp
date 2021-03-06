// CGameDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "BejeweledSln.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include "Global.h"
#include "CMenuDlg.h"
#include"BejeweledSlnDlg.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_rtGame.top = GAME_Y;
	m_rtGame.left = GAME_X;
	m_rtGame.bottom = m_rtGame.top + PIC_HEIGHT * GAME_ROW;
	m_rtGame.right = m_rtGame.left + PIC_WIDTH * GAME_COL;

	m_bFirstElem = true;

	m_bPlaying = true;

	m_bPause = false;
}

CGameDlg::~CGameDlg()
{
	m_dcBg.DeleteDC();
	m_dcMem.DeleteDC();
	m_dcElem.DeleteDC();
	m_dcMask.DeleteDC();
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SCORE, m_stcScore);
	DDX_Control(pDX, IDC_PROGRESS_TIME, m_progTime);
	DDX_Control(pDX, IDC_BTN_TIP,m_btnTip);
	DDX_Control(pDX, IDC_BTN_PAUSE, m_btnPause);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_TIP, &CGameDlg::OnBnClickedBtnTip)
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CGameDlg::OnBnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_MENU, &CGameDlg::OnBnClickedBtnMenu)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	this->ModifyStyleEx(0, WS_EX_APPWINDOW);//显示任务栏

	InitWnd();
	m_GameLogic.BuildMap();
	InitPicture();
	DrawGameArea();
	// TODO:  在此添加额外的初始化
	SetTimer(1, 1000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::InitWnd()
{
	SetWindowPos(NULL, 0, 0, WIDTH, HEIGHT, SWP_NOMOVE);
	CClientDC dc(this);
	CBitmap bmpBg;
	bmpBg.LoadBitmapW(IDB_BMP_BG);
	m_dcBg.CreateCompatibleDC(&dc);
	m_dcBg.SelectObject(bmpBg);

	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, WIDTH, HEIGHT);
	m_dcMem.CreateCompatibleDC(&dc);
	m_dcMem.SelectObject(bmpMem);

	m_dcMem.BitBlt(0, 0, WIDTH, HEIGHT, &m_dcBg, 0, 0, SRCCOPY);	
	m_stcScore.MoveWindow(500, 100, 125, 70);
	m_Font.CreatePointFont(180, _T("宋体"));
	m_stcScore.SetFont(&m_Font);
	m_progTime.MoveWindow(GAME_X, GAME_Y + PIC_HEIGHT * GAME_ROW, GAME_COL*PIC_WIDTH, 30);
	m_progTime.SetRange(0, 60);
	m_progTime.SetPos(60);
	m_progTime.SetStep(-1);
	m_btnTip.MoveWindow(475, 350, 87, 50);
	m_btnPause.MoveWindow(580, 350, 87, 50);
	// TODO: 在此处添加实现代码.
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, WIDTH, HEIGHT, &m_dcMem, 0, 0, SRCCOPY);
}


void CGameDlg::InitPicture()
{
	CClientDC dc(this);

	CBitmap bmpMask;
	bmpMask.LoadBitmap(IDB_BMP_MASK);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(bmpMask);

	CBitmap bmpElem;
	bmpElem.LoadBitmap(IDB_BMP_ELEM);
	m_dcElem.CreateCompatibleDC(&dc);
	m_dcElem.SelectObject(bmpElem);

	CBitmap bmpRemove;
	bmpRemove.LoadBitmap(IDB_BMP_REMOVE);
	m_dcRemove.CreateCompatibleDC(&dc);
	m_dcRemove.SelectObject(bmpRemove);

	CBitmap bmpPause;
	bmpPause.LoadBitmap(IDB_BMP_PAUSE);
	m_dcPause.CreateCompatibleDC(&dc);
	m_dcPause.SelectObject(bmpPause);

	CBitmap bmpCache;
	bmpCache.CreateCompatibleBitmap(&dc,256,256);
	m_dcCache.CreateCompatibleDC(&dc);
	m_dcCache.SelectObject(bmpCache);

	// TODO: 在此处添加实现代码.
}

void CGameDlg::DrawGameArea()
{
	//将m_dcMem游戏区域还原为背景图片
	m_dcMem.BitBlt(GAME_X, GAME_Y, PIC_WIDTH*GAME_COL, PIC_HEIGHT*GAME_ROW, &m_dcBg, GAME_X, GAME_Y, SRCCOPY);
	int nPicNum = INIT_PIC_NUM;
	int nWndX = 0;
	int nWndY = 0;
	int nPicX = 0;
	int nPicY = 0;
	for (int i = 0; i < GAME_ROW; i++)
	{
		for (int j = 0; j < GAME_COL; j++)
		{
			nPicNum = m_GameLogic.GetPicNum(i, j);
			nWndX = GAME_X + PIC_WIDTH * j;
			nWndY = GAME_Y + PIC_HEIGHT * i;
			nPicY = nPicNum * PIC_HEIGHT;
			nPicX = 0;

			//背景与掩码相或
			m_dcMem.BitBlt(nWndX, nWndY, PIC_WIDTH, PIC_HEIGHT, &m_dcMask, nPicX, nPicY, SRCPAINT);
			//再与图片元素想与
			m_dcMem.BitBlt(nWndX, nWndY, PIC_WIDTH, PIC_HEIGHT, &m_dcElem, nPicX, nPicY, SRCAND);
		}
	}
	InvalidateRect(&m_rtGame, FALSE);
}


void CGameDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(!m_bPlaying)
		return CDialogEx::OnLButtonDown(nFlags, point);
	//判断点击坐标是否超出游戏矩形区域
	if (!m_rtGame.PtInRect(point))
	{
		return CDialogEx::OnLButtonDown(nFlags, point);
	}
	//由点击的坐标计算行列
	int nRow = (point.y - GAME_Y) / PIC_HEIGHT;
	int nCol = (point.x - GAME_X) / PIC_WIDTH;
	//获取图片元素
	PICELEM picElem = m_GameLogic.GetPicElem(nRow, nCol);
	DrawTipFrame(picElem);//绘制提示框
	if (m_bFirstElem)
		m_picElemFirst = picElem;
	else
	{
		m_picElemSecond = picElem;
		if (m_GameLogic.IsNeighbour(m_picElemFirst, m_picElemSecond))
		{
			ChangeCartoon();
			m_GameLogic.ExchangeMap(m_picElemFirst, m_picElemSecond);
			if (m_GameLogic.IsExchange(m_picElemFirst, m_picElemSecond))
			{
				do {
					m_GameLogic.RecordRemove();

					//消子操作
					RemoeveCartoon();
					m_GameLogic.PicDown();
					DrawGameArea();
					DisplayScore();
					m_GameLogic.DeleteRecord();
				} while (m_GameLogic.IsMapRemove());
				
				if (!m_GameLogic.CanExchange())
				{
					m_GameLogic.BuildMap();
					DrawGameArea();
				}
				
			}
			else
			{
				//交换回来
				ChangeCartoon();
				m_GameLogic.ExchangeMap(m_picElemFirst, m_picElemSecond);
			}
			//换操作
		}
		else
		{
			//去掉提示框
			CRect rect1 = GetElemRect(m_picElemFirst) + GetElemRect(m_picElemSecond);
			InvalidateRect(&rect1, false);
		}
	}
		m_bFirstElem = !m_bFirstElem;
		CDialogEx::OnLButtonDown(nFlags, point);
}


// 计算图片元素左上角坐标
void CGameDlg::GetElemLUxy(PICELEM picElem, int & nX, int & nY)
{
	nX = picElem.nCol*PIC_WIDTH + GAME_X;
	nY = picElem.nRow*PIC_HEIGHT + GAME_Y;
}

CRect CGameDlg::GetElemRect(PICELEM picElem)
{
	int nX = 0;
	int nY = 0;
	GetElemLUxy(picElem, nX, nY);
	return CRect(nX, nY, nX + PIC_WIDTH, nY + PIC_HEIGHT);
}

void CGameDlg::DrawTipFrame(PICELEM picElem)
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame = GetElemRect(picElem);
	dc.FrameRect(rtTipFrame, &brush);
}

void CGameDlg::ChangeCartoon()
{
	int nFlag = 0;//定义一个标志
	PICELEM elemLU = m_picElemFirst;//定义左上图片
	PICELEM elemRD = m_picElemSecond;//定义右下图片元素
	if (m_picElemFirst.nRow == m_picElemSecond.nRow)//行相等横向交换
	{
		nFlag = 1;
		if (m_picElemFirst.nCol>m_picElemSecond.nCol)
		{
			elemRD = m_picElemFirst;
			elemLU = m_picElemSecond;
		}
	}
	if (m_picElemFirst.nCol==m_picElemSecond.nCol)//列相当，纵向交换
	{
		nFlag = 2;
		if (m_picElemFirst.nRow>m_picElemSecond.nRow)
		{
			elemRD = m_picElemFirst;
			elemLU = m_picElemSecond;
		}
	}
	//获取左上宝石的目的坐标
	int nLUWndX = 0;
	int nLUWndY = 0;
	GetElemLUxy(elemLU, nLUWndX, nLUWndY);
	//获取左上宝石的源坐标
	int nLUPicX = 0;
	int nLUPicY = elemLU.nPicNum*PIC_HEIGHT;
	//获取右下宝石的目的坐标
	int nRDWndX = 0;
	int nRDWndY = 0;
	GetElemLUxy(elemRD, nRDWndX, nRDWndY);
	//获取右下宝石的源坐标
	int nRDPicX = 0;
	int nRDPicY = elemRD.nPicNum*PIC_HEIGHT;

	int nNum = 0;//偏移次数
	while (nNum < 5)
	{
		nNum++;
		if (nFlag == 1)//横向
		{
			m_dcMem.BitBlt(nLUWndX, nLUWndY, PIC_WIDTH * 2, PIC_HEIGHT, &m_dcBg, nLUWndX, nLUWndY, SRCCOPY);

			m_dcMem.BitBlt((nLUWndX + nNum * MOVE_PIXEL), nLUWndY, PIC_WIDTH, PIC_HEIGHT, &m_dcMask, nLUPicX, nLUPicY, SRCPAINT);
			m_dcMem.BitBlt((nLUWndX + nNum * MOVE_PIXEL), nLUWndY, PIC_WIDTH, PIC_HEIGHT, &m_dcElem, nLUPicX, nLUPicY, SRCAND);

			m_dcMem.BitBlt((nRDWndX - nNum * MOVE_PIXEL), nRDWndY, PIC_WIDTH, PIC_HEIGHT, &m_dcMask, nRDPicX, nRDPicY, SRCPAINT);
			m_dcMem.BitBlt((nRDWndX - nNum * MOVE_PIXEL), nRDWndY, PIC_WIDTH, PIC_HEIGHT, &m_dcElem, nRDPicX, nRDPicY, SRCAND);
		}
		else
		{
			m_dcMem.BitBlt(nLUWndX, nLUWndY, PIC_WIDTH , PIC_HEIGHT*2, &m_dcBg, nLUWndX, nLUWndY, SRCCOPY);

			m_dcMem.BitBlt(nLUWndX, (nLUWndY + nNum * MOVE_PIXEL), PIC_WIDTH, PIC_HEIGHT, &m_dcMask, nLUPicX, nLUPicY, SRCPAINT);
			m_dcMem.BitBlt(nLUWndX, (nLUWndY + nNum * MOVE_PIXEL), PIC_WIDTH, PIC_HEIGHT, &m_dcElem, nLUPicX, nLUPicY, SRCAND);

			m_dcMem.BitBlt(nRDWndX, (nRDWndY - nNum * MOVE_PIXEL), PIC_WIDTH, PIC_HEIGHT, &m_dcMask, nRDPicX, nRDPicY, SRCPAINT);
			m_dcMem.BitBlt(nRDWndX, (nRDWndY - nNum * MOVE_PIXEL), PIC_WIDTH, PIC_HEIGHT, &m_dcElem, nRDPicX, nRDPicY, SRCAND);
		}
		CRect rect = GetElemRect(elemLU) + GetElemRect(elemRD);
		InvalidateRect(&rect, false);
		UpdateWindow();
		Sleep(50);
	}
}

void CGameDlg::RemoeveCartoon()
{
	PICELEM picElem;
	int nWndX = 0;
	int nWndY = 0;
	CRect rtRemove;
	int nRemoveNum = m_GameLogic.GetRemoveNum();

	for (int i = 0; i < nRemoveNum; i++)
	{
		picElem = m_GameLogic.GetRemoveElem(i);
		GetElemLUxy(picElem, nWndX, nWndY);
		m_dcMem.BitBlt(nWndX, nWndY, PIC_WIDTH, PIC_HEIGHT, &m_dcRemove, 0,0, SRCCOPY);
		rtRemove += GetElemRect(picElem);
	}
	InvalidateRect(&rtRemove, false);
	UpdateWindow();
	Sleep(300);
}

void CGameDlg::DisplayScore()
{
	CString str;
	str.Format(_T("%d"), m_GameLogic.GetTotalScore());
	m_stcScore.SetWindowText(str);
	CRect rtStc;
	m_stcScore.GetWindowRect(&rtStc);
	ScreenToClient(&rtStc);
	InvalidateRect(&rtStc, false);
}

void CGameDlg::GameOver()
{
	m_bPlaying = false;
	m_progTime.ShowWindow(SW_HIDE);
	m_btnPause.EnableWindow(false);
	m_btnTip.EnableWindow(false);
}

void CGameDlg::Restart()
{
	m_GameLogic.BuildMap();
	DrawGameArea();
	//初始化数据
	m_bFirstElem = true;
	m_bPlaying = true;
	m_bPause = false;
	//设置控件
	m_GameLogic.SetTotalScore(0);
	DisplayScore();
	m_progTime.SetPos(60);
	m_progTime.ShowWindow(SW_SHOW);
	m_btnPause.EnableWindow(true);
	m_btnTip.EnableWindow(true);

	SetTimer(1, 1000, NULL);

	//播放游戏音乐
	//CConfigLogic logicConfig;
	//logicConfig.PlayNewGameSound();

}


HBRUSH CGameDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_SCORE)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		return(HBRUSH)::GetStockObject(HOLLOW_BRUSH);
	}
	else
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
		return hbr;
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1)
	{
		if (m_bPlaying)
		{
			m_progTime.StepIt();
			int nTime = m_progTime.GetPos();
			if (nTime==0)
			{
				KillTimer(1);
				GameOver();
				MessageBox(_T("很遗憾，时间到了！！"));
			}
			else
			{
				if (m_GameLogic.GetTotalScore() >= 1000)
				{
					KillTimer(1);
					GameOver();
					MessageBox(_T("你赢了！！"));
				}
			}
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CGameDlg::OnBnClickedBtnTip()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_bPlaying)
		return;
	DrawTipFrame(m_GameLogic.m_aTip[0]);
	DrawTipFrame(m_GameLogic.m_aTip[1]);
	Sleep(500);
	CRect rect = GetElemRect(m_GameLogic.m_aTip[0]) + GetElemRect(m_GameLogic.m_aTip[1]);
	InvalidateRect(&rect, false);
}


void CGameDlg::OnBnClickedBtnPause()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bPlaying = !m_bPlaying;
	m_bPause = !m_bPause;
	CRect rtPause(97, 97, 353, 353);//暂停区域矩形
	if (m_bPause)
	{
		SetDlgItemText(IDC_BTN_PAUSE, _T("继续"));
		m_dcCache.BitBlt(0, 0, 256, 256, &m_dcMem, 97, 97, SRCCOPY);
		m_dcMem.BitBlt(97, 97, 256, 256, &m_dcPause, 0, 0, SRCCOPY);
		GetDlgItem(IDC_PROGRESS_TIME)->ShowWindow(SW_HIDE);
	}
	else
	{
		SetDlgItemText(IDC_BTN_PAUSE, _T("暂停"));
		m_dcMem.BitBlt(97, 97, 256, 256, &m_dcCache, 0, 0, SRCCOPY);
		GetDlgItem(IDC_PROGRESS_TIME)->ShowWindow(SW_SHOW);
	}
	InvalidateRect(&rtPause, false);
}


void CGameDlg::OnBnClickedBtnMenu()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bPlaying = false;
	CMenuDlg dlg;
	int nResult = dlg.DoModal();

	if (nResult == 1)
	{
		CDialogEx::OnOK();
		CBejeweledSlnDlg dlg;
		dlg.DoModal();
	}
	if (nResult == 2)
	{
		m_bPlaying = true;
	}
	if (nResult == 3)
	{
		Restart();
	}
	if (nResult == 4)
	{
		m_bPlaying = true;
		//UpdateTheme();
		//UpdateMusic();
	}
	if (nResult == 5)
	{
		CDialogEx::OnClose();
	}
}
