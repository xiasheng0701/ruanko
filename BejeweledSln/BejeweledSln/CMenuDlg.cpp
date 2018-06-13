// CMenuDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "BejeweledSln.h"
#include "CMenuDlg.h"
#include "afxdialogex.h"
#include "CSetDlg.h"


// CMenuDlg 对话框

IMPLEMENT_DYNAMIC(CMenuDlg, CDialogEx)

CMenuDlg::CMenuDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MENU_DIALOG, pParent)
{

}

CMenuDlg::~CMenuDlg()
{
}

void CMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMenuDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_PRIMENU, &CMenuDlg::OnBnClickedBtnPrimenu)
	ON_BN_CLICKED(IDC_BTN_RETURN, &CMenuDlg::OnBnClickedBtnReturn)
	ON_BN_CLICKED(IDC_BTN_RESTART, &CMenuDlg::OnBnClickedBtnRestart)
	ON_BN_CLICKED(IDC_BTN_SETGAME, &CMenuDlg::OnBnClickedBtnSetgame)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CMenuDlg::OnBnClickedBtnExit)
END_MESSAGE_MAP()


// CMenuDlg 消息处理程序


void CMenuDlg::OnBnClickedBtnPrimenu()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(1);
}


void CMenuDlg::OnBnClickedBtnReturn()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(2);
}


void CMenuDlg::OnBnClickedBtnRestart()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(3);
}


void CMenuDlg::OnBnClickedBtnSetgame()
{
	// TODO: 在此添加控件通知处理程序代码
	CSetDlg dlg;
	int nResult = dlg.DoModal();
	/*if (nResult == IDOE)
	{
		CDialogEx::OnOK();
		EndDialog(4);
	}*/
}


void CMenuDlg::OnBnClickedBtnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(5);
}