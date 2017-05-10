
// NBuilderView.cpp : CNBuilderView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "NBuilder.h"
#endif

#include "NBuilderDoc.h"
#include "NBuilderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNBuilderView

IMPLEMENT_DYNCREATE(CNBuilderView, CEditView)

BEGIN_MESSAGE_MAP(CNBuilderView, CEditView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CNBuilderView 构造/析构

CNBuilderView::CNBuilderView()
{
	// TODO: 在此处添加构造代码
}

CNBuilderView::~CNBuilderView()
{
}

BOOL CNBuilderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// 启用换行

	return bPreCreated;
}

void CNBuilderView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CNBuilderView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CNBuilderView 诊断

#ifdef _DEBUG
void CNBuilderView::AssertValid() const
{
	CEditView::AssertValid();
}

void CNBuilderView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CNBuilderDoc* CNBuilderView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNBuilderDoc)));
	return (CNBuilderDoc*)m_pDocument;
}
#endif //_DEBUG


// CNBuilderView 消息处理程序
