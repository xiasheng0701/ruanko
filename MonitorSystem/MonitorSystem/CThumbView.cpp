// CThumbView.cpp: 实现文件
//

#include "stdafx.h"
#include "MonitorSystem.h"
#include "CThumbView.h"


// CThumbView

IMPLEMENT_DYNCREATE(CThumbView, CView)

CThumbView::CThumbView()
{

}

CThumbView::~CThumbView()
{
}

BEGIN_MESSAGE_MAP(CThumbView, CView)
END_MESSAGE_MAP()


// CThumbView 绘图

void CThumbView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码
}


// CThumbView 诊断

#ifdef _DEBUG
void CThumbView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CThumbView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CThumbView 消息处理程序
