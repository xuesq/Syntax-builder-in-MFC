
// NBuilderDoc.h : CNBuilderDoc ��Ľӿ�
//


#pragma once
#include"Lexical.h"
#include<string>
#include"OutputWnd.h"
#include"MainFrm.h"
using namespace std;

class CNBuilderDoc : public CDocument
{
protected: // �������л�����
	CNBuilderDoc();
	DECLARE_DYNCREATE(CNBuilderDoc)

// ����
public:
// ����
public:
	string GetText();
	COutputWnd* GetOutputWind();
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CNBuilderDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

#ifdef SHARED_HANDLERS
private:
	CString m_strSearchContent;
	CString m_strThumbnailContent;
#endif // SHARED_HANDLERS

public:
	afx_msg void OnLexical();
	afx_msg void OnSyntax();
};
