#include "StdAfx.h"
#include "Lexical.h"

CLexical::CLexical(){
	tokenlist=NULL;
	keyword.clear();
	for(int i=0;i<keywords_size;i++){
		keyword.insert(pair<string,int>(keywords[i],i));
	}
}
CLexical::~CLexical(){
}
bool CLexical::process(int tag){
	int temp=0;
	if(tag==-99)
		return false;//�ʷ���������
	if(tag<0){//����//ʽ��ע��,���������в���֮��
		bufferBack();
		buffer=strtrim(buffer);
		if(tag==-101){//�ַ���
			if(searchKeyword(buffer,temp)==true){
				addToken(temp+401,buffer,row);//�ؼ���
			}else{
				addToken(-tag,buffer,row);//һ���ʶ��
			}
		}else if(tag==-102){
			int length=buffer.length();
			buffer=buffer.substr(1,length-2);
			addToken(-tag,buffer,row);
		}else{
			addToken(-tag,buffer,row);
		}
		buffer="";
		nonterminal=0;
	}else{
		nonterminal=tag;
	}
	return true;
}
void CLexical::addToken(int Id,string content,int row){
	CToken token={Id,content,row};
	tokenlist->push_back(token);
}
bool CLexical::searchKeyword(string key,int &pos){
	map<string,int>::iterator it=keyword.find(key);
	if(it!=keyword.end()){
		pos=it->second;
		return true;
	}
	return false;
}
void CLexical::bufferBack(){
	buffer.erase(buffer.end()-1);
	pos--;
}
bool CLexical::getTokenList(string &source,vector<CToken> *list){
	src=source;
	err="";
	tokenlist=list;
	if(list==NULL)
		return false;
	bool b_tag=true;
	pos=0;
	src.push_back(' ');
	src.push_back(' ');
	nonterminal=0;
	buffer="";
	row=1;
	int t_pos=pos=0;
	tokenlist->clear();
	int length=src.length();
	while(pos<length-1&&b_tag){      
		if(src[pos]=='\n'&&t_pos!=pos){
			row++;
			t_pos=pos;
		}
		buffer.push_back(src[pos]);//������ܼ����˿ո�,֮��ȥ��ǰ��Ŀո�
		b_tag=process(lextable[nonterminal][LexIndex(src[pos])]);
		if(!b_tag){
			string str="��";
			char s[5];
			sprintf_s(s,"%3d",row);
			err+=(str+s+"��:�ʷ���������!");
			return false;
		}
		pos++;
	}
	return b_tag;
}
string CLexical::getErrInfo(){
	return this->err;
}
string strtrim(string &str){
	int len=str.length();
	int s=0;
	int e=len-1;
	while(s<len){
		if(str[s]=='\n'||str[s]==' '||str[s]=='\r'||str[s]=='\t')
			s++;
		else
			break;
	}
	while(e>s){
		if(str[e]=='\n'||str[e]==' '||str[e]=='\r'||str[e]=='\t')
			e--;
		else
			break;;
	}
	if(s==0&&e==len-1)
		return str;
	else if(s>e)
		return "";
	else
		return str.substr(s,e-s+1);
}
