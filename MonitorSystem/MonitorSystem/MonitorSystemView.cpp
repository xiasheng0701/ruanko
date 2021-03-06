
// MonitorSystemView.cpp: CMonitorSystemView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MonitorSystem.h"
#endif

#include "MonitorSystemDoc.h"
#include "MonitorSystemView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMonitorSystemView

IMPLEMENT_DYNCREATE(CMonitorSystemView, CTreeView)

BEGIN_MESSAGE_MAP(CMonitorSystemView, CTreeView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMonitorSystemView 构造/析构

CMonitorSystemView::CMonitorSystemView()
{
	// TODO: 在此处添加构造代码

}

CMonitorSystemView::~CMonitorSystemView()
{
}

BOOL CMonitorSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CTreeView::PreCreateWindow(cs);
}


void CMonitorSystemView::OnDraw(CDC* /*pDC*/)
{
	CMonitorSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: 在此处为本机数据添加绘制代码
}


void CMonitorSystemView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

}


// CMonitorSystemView 打印

BOOL CMonitorSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMonitorSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMonitorSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMonitorSystemView 诊断

#ifdef _DEBUG
void CMonitorSystemView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CMonitorSystemView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CMonitorSystemDoc* CMonitorSystemView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMonitorSystemDoc)));
	return (CMonitorSystemDoc*)m_pDocument;
}
#endif //_DEBUG


// CMonitorSystemView 消息处理程序
