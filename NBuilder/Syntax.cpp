#pragma once
#include "StdAfx.h"
#include "Syntax.h"

//#define _CRT_SECURE_NO_WARNINGS
char prog[80]; //������������ַ�
char token[8]; //��Ŵ���
char ch; //�����ַ�
int syn=0, p = 0, m = 0, n = 0, i = 0; //syn:�ֱ����
double sum = 0;
int countsyn = 0;
int isSignal = 0; //�Ƿ��������(0������1���ţ�2���ţ�
int isError = 0;
int isDecimal = 0; //�Ƿ���С��
double decimal = 0; //С��
int isExp = 0; //�Ƿ���ָ��
int index = 0; //ָ����
int isNegative = 0; //�Ƿ������
double temp = 0;
int temp2 = 0;
int repeat = 0; //�Ƿ���������+,-
int nextq = 0;
int kk; //��ʱ�����ı��
int ntc, nfc, nnc =0, nnb = 0, nna = 0;
string stral; 
char *rwtab[9] = { "main","int","float","double","char","if","else","do","while" };
struct com fourCom[20]; //�ṹ������
CString output = _T("");
void readin() {
	int aaaa = 1;
}
void lrparser()
{
	stral.erase();
	int nChain;
	nfc = ntc = 1;
	nextq = 1;
	if (syn == 1) //main
	{
		scanner();
		if (syn == 26) //(
		{
			scanner();
			if (syn == 27) //)
			{
				scanner();
				staBlock(&nChain);
			}
			else
				stral += "ȱ��������";
		}
		else
			stral += "ȱ��������";
	}
	else
		stral += "ȱ��main";
}

//<����> ::= '{'<��䴮>'}'

void staBlock(int *nChain) //����
{
	if (syn == 28) //{
	{
		scanner();
		staString(nChain); //backpatch(*nChain,nextq);
		if (syn == 29) //}
			scanner(); //����һ��
		else
			stral += "ȱ��}��";
	}
	else
		stral += "ȱ��{��";

} //<��䴮>::=<���>{;<���>};
void staString(int *nChain) //��䴮
{
	sta(nChain);
	backpatch(*nChain, nextq);
	while (syn == 31) //;
	{
		scanner();
		sta(nChain);
	} //backpatch(*nChain,nextq-1);

}

void sta(int *nChain) //���
{
	if (syn == 10)
	{
		fuzhi(); //*nChain=0;
	}
	else if (syn == 6) //if
	{
		tiaojian(nChain);
	}
	else if (syn == 8) //do
		xunhuan();
} //<�������>->if(<����>)<����>
void tiaojian(int *nChain)
{

	char res[10], num1[10], num2[10], op[10];
	int nChainTemp; //<����>-><���ʽ><��ϵ�����><���ʽ>
	if (syn == 6) //if
	{
		scanner(); //strcpy(num1,E());
		if (syn == 26) //(
		{
			scanner();
			strcpy(num1, E());
			if ((syn <= 37) && (syn >= 32))
			{
				switch (syn)
				{
				case 32: strcpy(op, ">");
					break;
				case 33: strcpy(op, ">=");
					break;
				case 34: strcpy(op, "<");
					break;
				case 35: strcpy(op, "<=");
					break;
				case 36: strcpy(op, "==");
					break;
				case 37: strcpy(op, "!=");
					break;
				default:stral += "error";
				}
			}
			scanner();
			strcpy(num2, E());
			strcat(num1, op);
			strcat(num1, num2); //nfc=nextq+1;
			ntc = nextq; //��סif���λ��
			emit("0", "if", num1, "goto");
			nfc = nextq; //if�б��ʽΪ��
			emit("0", "", "", "goto");  //��һ��0�ѻ���
			backpatch(ntc, nextq); //ntc���ӵ�������Ԫʽ������nextq
		}
		if (syn == 27) //)
			scanner();
		staBlock(&nChainTemp); //����
		*nChain = merge(nChainTemp, nfc);
	}
} //<ѭ�����>::=do <����>while <����>
void xunhuan()
{
	char res[10], num1[10], num2[10], op[10];
	int nChainTemp;
	if (syn == 8) //do
	{
		nnc = nextq; //��סif���λ�ã�emit֮��nextq�ͱ���
					 //emit("0","if",num1,"goto");
		scanner();
		staBlock(&nChainTemp); //����
		if (syn == 9) //while
		{
			scanner();
			if (syn == 26) //(
			{
				scanner();
				strcpy(num1, E());
				if ((syn <= 37) && (syn >= 32))
				{
					switch (syn)
					{
					case 32: strcpy(op, ">");
						break;
					case 33: strcpy(op, ">=");
						break;
					case 34: strcpy(op, "<");
						break;
					case 35: strcpy(op, "<=");
						break;
					case 36: strcpy(op, "==");
						break;
					case 37: strcpy(op, "!=");
						break;
					default: stral += "error";
					}
				}
				scanner();
				strcpy(num2, E());
				strcat(num1, op);
				strcat(num1, num2);
				nnb = nextq;
				emit("0", "if", num1, "goto");
				backpatch(nnb, nnc);
				nna = nextq;
				emit("0", "", "", "goto");
				backpatch(nna, nextq);
			}
			if (syn == 27) //)
				scanner();
		}
	}
}
void fuzhi() //��ֵ���ֻ��1��������
{
	char res[10], num[10]; //num������
	if (syn == 10) //�ַ���
	{
		strcpy(res, token); //���
		scanner();
		if (syn == 21) //=
		{
			scanner();
			strcpy(num, E());
			emit(res, num, "=", "");
		}
		else
		{
			stral += "ȱ��=��";
		}
	}
}
char* E() //Expression���ʽ
{
	char *res, *num1, *op, *num2;
	res = (char *)malloc(10);
	num1 = (char *)malloc(10);
	op = (char *)malloc(10);
	num2 = (char *)malloc(10);
	strcpy(num1, T());
	while ((syn == 22) || (syn == 23)) //+ -
	{
		if (syn == 22) //+
			strcpy(op, "+");
		else
			strcpy(op, "-");
		scanner();
		strcpy(num2, T());
		strcpy(res, newTemp());
		emit(res, num1, op, num2);
		strcpy(num1, res);
	}
	return num1;
}
char* T() //Term��
{

	char *res, *num1, *op, *num2;
	res = (char *)malloc(10);
	num1 = (char *)malloc(10);
	op = (char *)malloc(10);
	num2 = (char *)malloc(10);
	strcpy(num1, F());
	while ((syn == 24) || (syn == 25)) //* /
	{
		if (syn == 24)
			strcpy(op, "*");
		else
			strcpy(op, "/");
		scanner();
		strcpy(num2, F());
		strcpy(res, newTemp());
		emit(res, num1, op, num2);
		strcpy(num1, res);
	}
	return num1;
}
char* F() //Factor����
{
	char *res;
	res = (char *)malloc(10);
	if (syn == 10) //�ַ���
	{
		strcpy(res, token);
		scanner();
	}
	else if (syn == 20) //��������
	{
		_itoa((int)sum, res, 10); //����ת��Ϊ�ַ���
		scanner();
	}
	else if (syn == 26) //(
	{
		scanner();
		res = E();
		if (syn == 27) //)
		{
			scanner();
		}
		else isError = 1;
	}
	else
		isError = 1;
	return res;
}
char *newTemp()
{
	char *p;
	char varTemp[10];
	p = (char *)malloc(10);
	kk++;
	_itoa(kk, varTemp, 10);
	strcpy(p + 1, varTemp);
	p[0] = 'T';
	return p;
} //��p�����ӵ�ÿ����Ԫʽ�ĵ��ĸ�����������t
void backpatch(int p, int t)
{
	int w, circle = p;
	while (circle) //circle��Ϊ0��ʱ��
	{
		w = atoi(fourCom[circle].result); //��Ԫʽcircle���ķ�������
										  //strcpy(fourCom[circle].result,t); //��t�����Ԫʽcircle�ĵ��ķ���
		sprintf(fourCom[circle].result, "%d", t);
		circle = w; //w��¼������������һ����Ԫʽ���ƶ���
	}
	return;
}
int merge(int p1, int p2) //�ϲ�p1��p2
{
	char circle, nResult;
	if (p2 == 0)
		nResult = p1;
	else
	{
		nResult = circle = p2;
		while (atoi(fourCom[circle].result)) //��Ԫʽ���ĸ�������Ϊ0
		{
			circle = atoi(fourCom[circle].result); //strcpy(fourCom[circle].result,p1);
			sprintf(fourCom[circle].result, "%s", p1);
		} //Ŀ������p1��ֵ����0
	}
	return nResult; //p2��ͷ��p1����0������p2���
}
void emit(char *res, char *num1, char *op, char *num2)
{
	strcpy(fourCom[nextq].result, res);
	strcpy(fourCom[nextq].arg1, num1);
	strcpy(fourCom[nextq].opera, op);
	strcpy(fourCom[nextq].arg2, num2);
	nextq++;
}
void scanner()
{
	sum = 0;
	decimal = 0;
	m = 0;
	for (n = 0; n<8; n++)
		token[n] = NULL;
	ch = prog[p++]; //��prog�ж���һ���ַ���ch��
	while (ch == ' ' || ch == '\n'||ch=='\r') //�������ַ�����Ч���룩
		ch = prog[p++];
	if (((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z'))) //ch����ĸ�ַ�
	{
		while (((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) || ((ch >= '0') && (ch <= '9')))
		{
			token[m++] = ch; //ch=>token
			ch = prog[p++]; //����һ���ַ�
		}
		token[m++] = '\0';
		p--; //����һ��
		syn = 10; //��ʶ��
				  //�����"begin","if","then","while","do","end"��ʶ���е�һ��
		for (n = 0; n<9; n++)
			if (strcmp(token, rwtab[n]) == 0)
			{
				syn = n + 1;
				break;
			}
	}
	else if ((ch >= '0') && (ch <= '9'))
	{
	IsNum:
		if (isSignal == 1)
		{
			//token[m++]='-';
		}
		while ((ch >= '0') && (ch <= '9'))
		{
			sum = sum * 10 + ch - '0'; //ch�����ֱ����ǵ����ַ���ŵ�
			ch = prog[p++];
		}
		if (ch == '.')
		{
			isDecimal = 1;
			ch = prog[p++];
			countsyn = 0; //֮ǰ��������,123.123+123.123#�������������޷�ʶ��
			while ((ch >= '0') && (ch <= '9'))
			{ //pow(x,y)����x��y����
				temp = (ch - '0')*pow(0.1, ++countsyn);
				decimal = decimal + temp; //AddToDec();
				ch = prog[p++];
			}
			sum = sum + decimal;
		}
		if (ch == 'e' || ch == 'E')
		{
			isExp = 1;
			ch = prog[p++];
			if (ch == '-')
			{
				isNegative = 1;
				ch = prog[p++];
			}
			while ((ch >= '0') && (ch <= '9'))
			{ //ָ��
				index = index * 10 + ch - '0';
				ch = prog[p++];
			}
			//10����
			//123e3����123*10(3)
			//sum=sum*pow(10,index);�Ǵ����
			if (isNegative)
				sum = sum*pow(0.1, index);
			else
				sum = sum*pow(10, index);
		}
		if (isSignal == 1)
		{
			sum = -sum;
			isSignal = 0;
		}
		p--;
		syn = 20;
	}
	else switch (ch)
	{
	case '<':
		m = 0;
		token[m++] = ch;
		ch = prog[p++];
		if (ch == '=')
		{
			syn = 35;
			token[m++] = ch;
		}
		else
		{
			syn = 34;
			p--;
		}
		break;
	case '>':
		m = 0;
		token[m++] = ch;
		ch = prog[p++];
		if (ch == '=')
		{
			syn = 33;
			token[m++] = ch;
		}
		else
		{
			syn = 32;
			p--;
		}
		break;
	case '=':
		m = 0;
		token[m++] = ch;
		ch = prog[p++];
		if (ch == '=')
		{
			syn = 36;
			token[m++] = ch;
		}
		else
		{
			syn = 21;
			p--;
		}
		break;
	case '+': temp2 = prog[p];
		token[m++] = ch;
		if ((temp2 >= '0') && (temp2 <= '9') && (repeat == 1))
		{
			isSignal = 2;
			ch = prog[p++];
			repeat = 0;
			goto IsNum;
		}
		if (((temp2 == '+') || (temp2 == '-')) && (repeat == 0)) //����ظ����ַ��ţ��Ž���ߵ�+��-��Ϊ������
		{
			repeat = 1; //ch=prog[p++];
		}
		syn = 22;
		break;
	case '-':
		temp2 = prog[p];
		token[m++] = ch;
		if ((temp2 >= '0') && (temp2 <= '9') && (repeat == 1))
		{
			isSignal = 1;
			ch = prog[p++]; //����-����һ���ַ�
			repeat = 0;
			goto IsNum;//ת�����ֵ�ʶ��
		}
		if (((temp2 == '+') || (temp2 == '-')) && (repeat == 0)) //����ظ����ַ��ţ��Ž���ߵ�+��-��Ϊ������
		{
			repeat = 1; //Ԥ�Ի��ظ�
						//ch=prog[p++];
						//����һ���ַ�
		}
		syn = 23;
		break;
	case '*':
		temp2 = prog[p];
		token[m++] = ch;
		if (temp2 == '+')
		{
			isSignal = 2;
			repeat = 1;
		}
		else if (temp2 == '-')
		{
			isSignal = 1;
			repeat = 1;
		}
		syn = 24;
		break;
	case '/': syn = 25;
		token[m++] = ch;
		break;
	case '(':
		temp2 = prog[p];
		token[m++] = ch;
		if (temp2 == '+')
		{
			isSignal = 2;
			repeat = 1;
		}
		else if (temp2 == '-')
		{
			isSignal = 1;
			repeat = 1;
		}
		syn = 26;
		break;
	case ')':
		syn = 27;
		token[m++] = ch;
		break;
	case '{':
		syn = 28;
		token[m++] = ch;
		break;
	case '}':
		syn = 29;
		token[m++] = ch;
		break;
	case ',':
		syn = 30;
		token[m++] = ch;
		break;
	case ';':
		syn = 31;
		token[m++] = ch;
		break;
	case'#':
		syn = 0;
		token[m++] = ch;
		break;
	default:
		syn = -1;
	}
}
