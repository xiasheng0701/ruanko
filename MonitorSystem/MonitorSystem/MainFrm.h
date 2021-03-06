
// MainFrm.h: CMainFrame 类的接口
//

#pragma once
#include "Global.h"
class CMonitorSystemView;
class CThumbView;
class CProcessListView;
class CServer;


class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:
	BOOL Send(CMessage& msg);//给某个客户端发送消息

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	
// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

private:
	//自定义变量
	CSplitterWnd m_splitLeftWnd;//左窗口
	CSplitterWnd m_splitRightWnd;//右窗口
	CMonitorSystemView* m_pMonitorSysView;//客户列表视图
	CProcessListView* m_pCProcessListView;//缩略图
	CThumbView* m_pCThumbView;//显示进程
	BOOL m_bSeverStart;//服务器启动标识
	CServer* m_pServer;//服务器Socket
private:
	afx_msg LRESULT OnReceiveMsg(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	afx_msg void OnSystemStartserver();//启动服务器
	afx_msg void OnSystemStopserver();//停止服务器
	afx_msg void OnDestroy();//窗体销毁
};


