#pragma once
#include<string>
#include<vector>
#include<map>
#include"Extern.h"
using namespace std;
string strtrim(string &str);//ȥ��str�е�ǰ��ո�,/r,/n,/t
typedef struct CToken{
	int kind;
	string content;
	int row;
}CToken;//������
class CLexical
{
private:
	string src;//Դ����
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

