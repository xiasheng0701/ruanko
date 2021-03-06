
// MonitorSystemView.h: CMonitorSystemView 类的接口
//

#pragma once

#include "MonitorSystemDoc.h"


class CMonitorSystemView : public CTreeView
{
protected: // 仅从序列化创建
	CMonitorSystemView();
	DECLARE_DYNCREATE(CMonitorSystemView)

// 特性
public:
	CMonitorSystemDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMonitorSystemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MonitorSystemView.cpp 中的调试版本
inline CMonitorSystemDoc* CMonitorSystemView::GetDocument() const
   { return reinterpret_cast<CMonitorSystemDoc*>(m_pDocument); }
#endif

