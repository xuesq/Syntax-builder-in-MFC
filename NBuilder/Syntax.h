#pragma once
#include<string>
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include"Extern.h"
using namespace std;
void outww();
extern string stral;
extern char prog[]; //存放所有输入字符
extern char token[]; //存放词组
extern char ch; //单个字符
extern int syn, p, m, n, i; //syn:种别编码
extern double sum;
extern int countsyn;
extern int isSignal; //是否带正负号(0不带，1负号，2正号）
extern int isError;
extern int isDecimal; //是否是小数
extern double decimal; //小数
extern int isExp; //是否是指数
extern int index; //指数幂
extern int isNegative; //是否带负号
extern double temp;
extern int temp2;
extern int repeat; //是否连续出现+,-
extern int nextq;
extern int kk; //临时变量的标号
extern int ntc, nfc, nnc, nnb, nna;
extern char *rwtab[] ;
extern struct com
{
	char result[10]; //字符串（字符数组）
	char arg1[10];
	char opera[10];
	char arg2[10];
}fourCom[]; //结构体数组
extern CString output;
void scanner(); //扫描
void lrparser();
void staBlock(int *nChain); //语句块
void staString(int *nChain); //语句串
void sta(int *nChain); //语句
void fuzhi(); //赋值语句
void tiaojian(int *nChain); //条件语句
void xunhuan(); //循环语句
char* E(); //Expresiion表达式
char* T(); //Term项
char* F(); //Factor因子
char *newTemp(); //自动生成临时变量
void backpatch(int p, int t); //回填
int merge(int p1, int p2); //合并p1和p2
void emit(char *res, char *num1, char *op, char *num2);