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
extern char prog[]; //������������ַ�
extern char token[]; //��Ŵ���
extern char ch; //�����ַ�
extern int syn, p, m, n, i; //syn:�ֱ����
extern double sum;
extern int countsyn;
extern int isSignal; //�Ƿ��������(0������1���ţ�2���ţ�
extern int isError;
extern int isDecimal; //�Ƿ���С��
extern double decimal; //С��
extern int isExp; //�Ƿ���ָ��
extern int index; //ָ����
extern int isNegative; //�Ƿ������
extern double temp;
extern int temp2;
extern int repeat; //�Ƿ���������+,-
extern int nextq;
extern int kk; //��ʱ�����ı��
extern int ntc, nfc, nnc, nnb, nna;
extern char *rwtab[] ;
extern struct com
{
	char result[10]; //�ַ������ַ����飩
	char arg1[10];
	char opera[10];
	char arg2[10];
}fourCom[]; //�ṹ������
extern CString output;
void scanner(); //ɨ��
void lrparser();
void staBlock(int *nChain); //����
void staString(int *nChain); //��䴮
void sta(int *nChain); //���
void fuzhi(); //��ֵ���
void tiaojian(int *nChain); //�������
void xunhuan(); //ѭ�����
char* E(); //Expresiion���ʽ
char* T(); //Term��
char* F(); //Factor����
char *newTemp(); //�Զ�������ʱ����
void backpatch(int p, int t); //����
int merge(int p1, int p2); //�ϲ�p1��p2
void emit(char *res, char *num1, char *op, char *num2);