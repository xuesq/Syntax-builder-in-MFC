
// NBuilderDoc.cpp : CNBuilderDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CNBuilderDoc ����/����

CNBuilderDoc::CNBuilderDoc()
{
	// TODO: �ڴ����һ���Թ������

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
		//����ı�����
		CFont cf;
		cf.CreatePointFont(120,"Verdana");
		reinterpret_cast<CEditView*>(m_viewList.GetHead())->GetEditCtrl().SetFont(&cf);
	}
	// (SDI �ĵ������ø��ĵ�)
	this->SetTitle(_T("NBuilder"));

	return TRUE;
}




// CNBuilderDoc ���л�

void CNBuilderDoc::Serialize(CArchive& ar)
{
	// CEditView ����һ�������������л��ı༭�ؼ�
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

// ����ͼ��֧��
void CNBuilderDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CNBuilderDoc::InitializeSearchContent()
{
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ʹ�������ı��ļ���Ϊ�������ݡ�
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

// CNBuilderDoc ���

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


// CNBuilderDoc ����

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
	//����Ԥ����
	CLexical lex;
	vector<CToken> tokenlist;
	lex.getTokenList(text,&tokenlist);
	string err=lex.getErrInfo();
	GetOutputWind()->LexicalOutput(tokenlist);
	GetOutputWind()->LexicalErr(err);
}


void CNBuilderDoc::OnSyntax()
{
	// TODO: �ڴ���������������
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
