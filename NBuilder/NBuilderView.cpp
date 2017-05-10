
// NBuilderView.cpp : CNBuilderView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CNBuilderView ����/����

CNBuilderView::CNBuilderView()
{
	// TODO: �ڴ˴���ӹ������
}

CNBuilderView::~CNBuilderView()
{
}

BOOL CNBuilderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// ���û���

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


// CNBuilderView ���

#ifdef _DEBUG
void CNBuilderView::AssertValid() const
{
	CEditView::AssertValid();
}

void CNBuilderView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CNBuilderDoc* CNBuilderView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNBuilderDoc)));
	return (CNBuilderDoc*)m_pDocument;
}
#endif //_DEBUG


// CNBuilderView ��Ϣ�������
