#pragma once
#include<string>
#include<vector>
#include<map>
#include"Extern.h"
using namespace std;
string strtrim(string &str);//去掉str中的前后空格,/r,/n,/t
typedef struct CToken{
	int kind;
	string content;
	int row;
}CToken;//单词类
class CLexical
{
private:
	string src;//源代码
	map<string,int>keyword;
	string buffer;
	string err;
	int row;
	int nonterminal;
	int pos;
	vector<CToken>*tokenlist;
	bool process(int tag);
	void addToken(int Id,string content,int row);
	bool searchKeyword(string key,int &pos);
	void bufferBack();
public:
	CLexical();
	~CLexical();
	bool getTokenList(string &source,vector<CToken> *list);
	string getErrInfo();
};

