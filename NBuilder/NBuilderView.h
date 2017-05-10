
// NBuilderView.h : CNBuilderView ��Ľӿ�
//

#pragma once


class CNBuilderView : public CEditView
{
protected: // �������л�����
	CNBuilderView();
	DECLARE_DYNCREATE(CNBuilderView)

// ����
public:
	CNBuilderDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CNBuilderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // NBuilderView.cpp �еĵ��԰汾
inline CNBuilderDoc* CNBuilderView::GetDocument() const
   { return reinterpret_cast<CNBuilderDoc*>(m_pDocument); }
#endif

