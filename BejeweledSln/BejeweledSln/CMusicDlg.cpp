// CMusicDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "BejeweledSln.h"
#include "CMusicDlg.h"
#include "afxdialogex.h"


// CMusicDlg 对话框

IMPLEMENT_DYNAMIC(CMusicDlg, CDialogEx)

CMusicDlg::CMusicDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MUSIC_SET_DIALOG, pParent)
{

}

CMusicDlg::~CMusicDlg()
{
}

void CMusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMusicDlg, CDialogEx)
END_MESSAGE_MAP()


// CMusicDlg 消息处理程序
