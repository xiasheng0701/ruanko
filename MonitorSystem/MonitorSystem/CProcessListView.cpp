// CProcessListView.cpp: 实现文件
//

#include "stdafx.h"
#include "MonitorSystem.h"
#include "CProcessListView.h"


// CProcessListView

IMPLEMENT_DYNCREATE(CProcessListView, CView)

CProcessListView::CProcessListView()
{

}

CProcessListView::~CProcessListView()
{
}

BEGIN_MESSAGE_MAP(CProcessListView, CView)
END_MESSAGE_MAP()


// CProcessListView 绘图

void CProcessListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码
}


// CProcessListView 诊断

#ifdef _DEBUG
void CProcessListView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CProcessListView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CProcessListView 消息处理程序
