// CSetDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "BejeweledSln.h"
#include "CSetDlg.h"
#include "afxdialogex.h"


// CSetDlg 对话框

IMPLEMENT_DYNAMIC(CSetDlg, CDialogEx)

CSetDlg::CSetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SET_DIALOG, pParent)
{

}

CSetDlg::~CSetDlg()
{
}

void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SET, m_tabSet);
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialogEx)
END_MESSAGE_MAP()


// CSetDlg 消息处理程序


void CSetDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


BOOL CSetDlg::OnInitDialog()
{
	// TODO: 在此处添加实现代码.
	m_tabSet.InsertItem(0, _T("主题设置"));
	m_tabSet.InsertItem(1, _T("音效设置"));
	//m_ThemeDlg.Creat(IDD_THEME_SET_DIALOG, &m_tabSet);
	//m_MusicDlg.Creat(IDD_MUSIC_SET_DIALOG, &m_tabSet);

	CRect cTabRect;
	m_tabSet.GetClientRect(&cTabRect);
	cTabRect.top += 22;
	cTabRect.bottom -= 4;
	cTabRect.left += 2;
	cTabRect.right -= 4;

	m_ThemeDlg.ShowWindow(TRUE);
	m_MusicDlg.ShowWindow(FALSE);

	return TRUE;
}
