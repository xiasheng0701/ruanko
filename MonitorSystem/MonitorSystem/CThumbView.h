#pragma once


// CThumbView 视图

class CThumbView : public CView
{
	DECLARE_DYNCREATE(CThumbView)

protected:
	CThumbView();           // 动态创建所使用的受保护的构造函数
	virtual ~CThumbView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


