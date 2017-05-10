
#include "stdafx.h"

#include "OutputWnd.h"
#include "Resource.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar
//COutputWnd  *OutputPane;
COutputWnd::COutputWnd()
{
	//OutputPane=this;
}

COutputWnd::~COutputWnd()
{
}

BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建选项卡窗口:
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("未能创建输出选项卡窗口\n");
		return -1;      // 未能创建
	}

	// 创建输出窗格:
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

	if (!m_wndOutputBuild.Create(dwStyle, rectDummy, &m_wndTabs, 2) ||
		!m_wndOutputDebug.Create(dwStyle, rectDummy, &m_wndTabs, 3) ||
		!m_wndOutputFind.Create(dwStyle, rectDummy, &m_wndTabs, 4))
	{
		TRACE0("未能创建输出窗口\n");
		return -1;      // 未能创建
	}

	UpdateFonts();

	CString strTabName;
	BOOL bNameValid;

	// 将列表窗口附加到选项卡:
	bNameValid = strTabName.LoadString(IDS_BUILD_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputBuild, strTabName, (UINT)0);
	bNameValid = strTabName.LoadString(IDS_DEBUG_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputDebug, strTabName, (UINT)1);
	bNameValid = strTabName.LoadString(IDS_FIND_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputFind, strTabName, (UINT)2);
	return 0;
}

void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// 选项卡控件应覆盖整个工作区:
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void COutputWnd::AdjustHorzScroll(CListBox& wndListBox)
{
	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&afxGlobalData.fontRegular);

	int cxExtentMax = 0;

	for (int i = 0; i < wndListBox.GetCount(); i ++)
	{
		CString strItem;
		wndListBox.GetText(i, strItem);

		cxExtentMax = max(cxExtentMax, dc.GetTextExtent(strItem).cx);
	}

	wndListBox.SetHorizontalExtent(cxExtentMax);
	dc.SelectObject(pOldFont);
}

void COutputWnd::LexicalOutput(vector<CToken> &tokenlist){
	int length=tokenlist.size();
	m_wndOutputBuild.AddString(_T("词法分析结果:"));
	for(int i=0;i<length;i++){
		CString cs=_T("");
		cs.AppendFormat("%03d行ID=%3d:",tokenlist.at(i).row,tokenlist.at(i).kind);
		cs.Append(tokenlist.at(i).content.c_str());
		m_wndOutputBuild.AddString(cs);
	}
}

void COutputWnd::SyntaxOutput(string text) {
	m_wndOutputBuild.AddString(_T("生成四元式代码:"));
	m_wndOutputBuild.AddString(text.c_str());
	m_wndOutputBuild.AddString(stral.c_str());
	//m_wndOutputBuild.AddString(output);
	for (int i = 1; i<nextq; i++) {
		/*CString cs = _T("");
		cs.AppendFormat("(%5s %5s  %5s  \t%5s )", fourCom[i].arg1, fourCom[i].opera, fourCom[i].arg2, fourCom[i].result);
		m_wndOutputBuild.AddString(cs);*/
		output = _T("");
		output.AppendFormat("%d", i);
		output.AppendFormat("(%5s %5s  %5s  \t%5s )", fourCom[i].arg1, fourCom[i].opera, fourCom[i].arg2, fourCom[i].result);
		
		m_wndOutputBuild.AddString(output);
	}
}

void COutputWnd::LexicalErr(string &err){
	if(err.size()>0){
		m_wndOutputBuild.AddString(err.c_str());
	}
}

void COutputWnd::UpdateFonts()
{
	m_wndOutputBuild.SetFont(&afxGlobalData.fontRegular);
	m_wndOutputDebug.SetFont(&afxGlobalData.fontRegular);
	m_wndOutputFind.SetFont(&afxGlobalData.fontRegular);
}


COutputList::COutputList()
{
}

COutputList::~COutputList()
{
}

BEGIN_MESSAGE_MAP(COutputList, CListBox)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_WINDOWPOSCHANGING()
	ON_COMMAND(ID_COPY_ALL, &COutputList::OnCopyAll)
	ON_COMMAND(ID_CLEAR_ALL, &COutputList::OnClearAll)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputList 消息处理程序

void COutputList::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_OUTPUT_POPUP);

	CMenu* pSumMenu = menu.GetSubMenu(0);
	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMainFrame))){
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;
		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;
		((CMainFrame*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
	SetFocus();
}

void COutputList::OnEditCopy()
{
	int item=GetCurSel();
	CString   source;
	this->GetText(item,source);
	if(OpenClipboard()){   
		HGLOBAL   clipbuffer;   
		char   *   buffer;   
		EmptyClipboard();   
		clipbuffer=GlobalAlloc(GMEM_DDESHARE, source.GetLength()+1);   
		buffer=(char*)GlobalLock(clipbuffer);   
		strcpy_s(buffer, source.GetLength()+1,  LPCSTR(source));   
		GlobalUnlock(clipbuffer);   
		SetClipboardData(CF_TEXT,clipbuffer);   
		CloseClipboard();   
	 }   
}

void COutputList::OnEditClear()
{
	DeleteString(GetCurSel());
}

void COutputList::OnCopyAll()
{
	int item=GetCount();
	CString   source;
	for(int i=0;i<item;i++){
		CString temp;
		this->GetText(i,temp);
		source+=temp+_T("\r\n");
	}
	if(OpenClipboard()){   
		HGLOBAL   clipbuffer;   
		char   *   buffer;   
		EmptyClipboard();   
		clipbuffer=GlobalAlloc(GMEM_DDESHARE, source.GetLength()+1);   
		buffer=(char*)GlobalLock(clipbuffer);   
		strcpy_s(buffer, source.GetLength()+1,  LPCSTR(source));   
		GlobalUnlock(clipbuffer);   
		SetClipboardData(CF_TEXT,clipbuffer);   
		CloseClipboard();   
	 }   
}

void COutputList::OnClearAll()
{
	int item=GetCount();
	for(int i=0;i<item;i++)
		this->DeleteString(0);
}
