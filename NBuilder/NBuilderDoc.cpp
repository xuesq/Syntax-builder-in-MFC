
// NBuilderDoc.cpp : CNBuilderDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "NBuilder.h"
#endif

#include "NBuilderDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CNBuilderDoc

IMPLEMENT_DYNCREATE(CNBuilderDoc, CDocument)

BEGIN_MESSAGE_MAP(CNBuilderDoc, CDocument)
	ON_COMMAND(ID_Lexical, &CNBuilderDoc::OnLexical)
	ON_COMMAND(ID_Syntax, &CNBuilderDoc::OnSyntax)
END_MESSAGE_MAP()


// CNBuilderDoc 构造/析构

CNBuilderDoc::CNBuilderDoc()
{
	// TODO: 在此添加一次性构造代码

}

CNBuilderDoc::~CNBuilderDoc()
{
}

BOOL CNBuilderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	if (!m_viewList.IsEmpty())
	{
		reinterpret_cast<CEditView*>(m_viewList.GetHead())->SetWindowText(NULL);
		//加入改变字体
		CFont cf;
		cf.CreatePointFont(120,"Verdana");
		reinterpret_cast<CEditView*>(m_viewList.GetHead())->GetEditCtrl().SetFont(&cf);
	}
	// (SDI 文档将重用该文档)
	this->SetTitle(_T("NBuilder"));

	return TRUE;
}




// CNBuilderDoc 序列化

void CNBuilderDoc::Serialize(CArchive& ar)
{
	// CEditView 包含一个处理所有序列化的编辑控件
	if (!m_viewList.IsEmpty())
	{
		reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);
	}
#ifdef SHARED_HANDLERS

	if (m_viewList.IsEmpty() && ar.IsLoading())
	{
		CFile* pFile = ar.GetFile();
		pFile->Seek(0, FILE_BEGIN);
		ULONGLONG nFileSizeBytes = pFile->GetLength();
		ULONGLONG nFileSizeChars = nFileSizeBytes/sizeof(TCHAR);
		LPTSTR lpszText = (LPTSTR)malloc(((size_t)nFileSizeChars + 1) * sizeof(TCHAR));
		if (lpszText != NULL)
		{
			ar.Read(lpszText, (UINT)nFileSizeBytes);
			lpszText[nFileSizeChars] = '\0';
			m_strThumbnailContent = lpszText;
			m_strSearchContent = lpszText;
		}
	}
#endif
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CNBuilderDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(m_strThumbnailContent, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CNBuilderDoc::InitializeSearchContent()
{
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 使用整个文本文件作为搜索内容。
	SetSearchContent(m_strSearchContent);
}

void CNBuilderDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CNBuilderDoc 诊断

#ifdef _DEBUG
void CNBuilderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNBuilderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CNBuilderDoc 命令

COutputWnd* CNBuilderDoc::GetOutputWind(){
	return ((CMainFrame*)AfxGetMainWnd())->GetOutputWind();
}

string CNBuilderDoc::GetText(){
	if(!DoFileSave())
		return "";
	CString cspath =this->GetPathName();
	CFile cf;
	cf.Open(cspath,CFile::modeRead);
	string text="";
	char s[1025];
	UINT n=0;
	if(cf.GetLength()!=0){
		while((n=cf.Read(s,1024))>0){
			s[n]='\0';
			text=text+string(s);
		}
	}
	return text;
}

void CNBuilderDoc::OnLexical(){
	string text=GetText();
	if(text.length()<=1)
		return;
	//这里预处理
	CLexical lex;
	vector<CToken> tokenlist;
	lex.getTokenList(text,&tokenlist);
	string err=lex.getErrInfo();
	GetOutputWind()->LexicalOutput(tokenlist);
	GetOutputWind()->LexicalErr(err);
}


void CNBuilderDoc::OnSyntax()
{
	// TODO: 在此添加命令处理程序代码
	string text = GetText();
	if (text.length() <= 1)
		return;
	//char program[80];
	for (int i = 0; text[i] != '#'; i++)
		prog[i] = text[i];
	isError = 0;
	p = 0;
	countsyn = 0;
	isDecimal = 0;
	index = 0;
	repeat = 0;
	kk = 0;
	scanner();
	lrparser();
	for (int i = 1; i < nextq; i++) {
		//string ss1(fourCom[i].arg1);
		//string ss2(fourCom[i].opera);
		//string ss3(fourCom[i].arg2);
		//string ss4(fourCom[i].result);
		//stral += '(';
		////fourCom[1].arg1[0] = { 'h' };
		//stral += ss1;
		////stral += '\t';
		//stral += ss2;
		////stral += '\t';
		//stral += ss3;
		////stral += '\t';
		//stral += ss4;
		//stral += ")";
		//output.AppendFormat("(%5s %5s  %5s  \t%5s )", fourCom[i].arg1, fourCom[i].opera, fourCom[i].arg2, fourCom[i].result);

	}
	GetOutputWind()->SyntaxOutput(text);
}
