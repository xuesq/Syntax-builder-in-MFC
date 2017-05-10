
// NBuilderView.h : CNBuilderView 类的接口
//

#pragma once


class CNBuilderView : public CEditView
{
protected: // 仅从序列化创建
	CNBuilderView();
	DECLARE_DYNCREATE(CNBuilderView)

// 特性
public:
	CNBuilderDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CNBuilderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // NBuilderView.cpp 中的调试版本
inline CNBuilderDoc* CNBuilderView::GetDocument() const
   { return reinterpret_cast<CNBuilderDoc*>(m_pDocument); }
#endif

