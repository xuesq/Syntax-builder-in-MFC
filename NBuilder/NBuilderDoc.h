
// NBuilderDoc.h : CNBuilderDoc 类的接口
//


#pragma once
#include"Lexical.h"
#include<string>
#include"OutputWnd.h"
#include"MainFrm.h"
using namespace std;

class CNBuilderDoc : public CDocument
{
protected: // 仅从序列化创建
	CNBuilderDoc();
	DECLARE_DYNCREATE(CNBuilderDoc)

// 特性
public:
// 操作
public:
	string GetText();
	COutputWnd* GetOutputWind();
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CNBuilderDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
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
