
#pragma once
#include"Lexical.h"
#include"NBuilder.h"
#include"Syntax.h"
/////////////////////////////////////////////////////////////////////////////
// COutputList ����

class COutputList : public CListBox
{
// ����
public:
	COutputList();

// ʵ��
public:
	virtual ~COutputList();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
//	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCopyAll();
	afx_msg void OnClearAll();
};

class COutputWnd : public CDockablePane
{
// ����
public:
	COutputWnd();
	void UpdateFonts();
	void LexicalOutput(vector<CToken> &tokenlist);
	void SyntaxOutput(string text);
	void LexicalErr(string &err);
// ����
protected:
	CMFCTabCtrl	m_wndTabs;

	COutputList m_wndOutputBuild;
	COutputList m_wndOutputDebug;
	COutputList m_wndOutputFind;

protected:

	void AdjustHorzScroll(CListBox& wndListBox);

// ʵ��
public:
	virtual ~COutputWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

//extern COutputWnd  *OutputPane;