// CThemeDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "BejeweledSln.h"
#include "CThemeDlg.h"
#include "afxdialogex.h"


// CThemeDlg 对话框

IMPLEMENT_DYNAMIC(CThemeDlg, CDialogEx)

CThemeDlg::CThemeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_THEME_SET_DIALOG, pParent)
{

}

CThemeDlg::~CThemeDlg()
{
}

void CThemeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CThemeDlg, CDialogEx)
END_MESSAGE_MAP()


// CThemeDlg 消息处理程序


