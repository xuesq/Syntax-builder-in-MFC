#pragma once
#include "StdAfx.h"
#include "Syntax.h"

//#define _CRT_SECURE_NO_WARNINGS
char prog[80]; //存放所有输入字符
char token[8]; //存放词组
char ch; //单个字符
int syn=0, p = 0, m = 0, n = 0, i = 0; //syn:种别编码
double sum = 0;
int countsyn = 0;
int isSignal = 0; //是否带正负号(0不带，1负号，2正号）
int isError = 0;
int isDecimal = 0; //是否是小数
double decimal = 0; //小数
int isExp = 0; //是否是指数
int index = 0; //指数幂
int isNegative = 0; //是否带负号
double temp = 0;
int temp2 = 0;
int repeat = 0; //是否连续出现+,-
int nextq = 0;
int kk; //临时变量的标号
int ntc, nfc, nnc =0, nnb = 0, nna = 0;
string stral; 
char *rwtab[9] = { "main","int","float","double","char","if","else","do","while" };
struct com fourCom[20]; //结构体数组
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
				stral += "缺少右括号";
		}
		else
			stral += "缺少左括号";
	}
	else
		stral += "缺少main";
}

//<语句块> ::= '{'<语句串>'}'

void staBlock(int *nChain) //语句块
{
	if (syn == 28) //{
	{
		scanner();
		staString(nChain); //backpatch(*nChain,nextq);
		if (syn == 29) //}
			scanner(); //读下一个
		else
			stral += "缺少}号";
	}
	else
		stral += "缺少{号";

} //<语句串>::=<语句>{;<语句>};
void staString(int *nChain) //语句串
{
	sta(nChain);
	backpatch(*nChain, nextq);
	while (syn == 31) //;
	{
		scanner();
		sta(nChain);
	} //backpatch(*nChain,nextq-1);

}

void sta(int *nChain) //语句
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
} //<条件语句>->if(<条件>)<语句块>
void tiaojian(int *nChain)
{

	char res[10], num1[10], num2[10], op[10];
	int nChainTemp; //<条件>-><表达式><关系运算符><表达式>
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
			ntc = nextq; //记住if语句位置
			emit("0", "if", num1, "goto");
			nfc = nextq; //if中表达式为假
			emit("0", "", "", "goto");  //第一个0已回填
			backpatch(ntc, nextq); //ntc链接的所有四元式都回填nextq
		}
		if (syn == 27) //)
			scanner();
		staBlock(&nChainTemp); //语句块
		*nChain = merge(nChainTemp, nfc);
	}
} //<循环语句>::=do <语句块>while <条件>
void xunhuan()
{
	char res[10], num1[10], num2[10], op[10];
	int nChainTemp;
	if (syn == 8) //do
	{
		nnc = nextq; //记住if语句位置，emit之后nextq就变了
					 //emit("0","if",num1,"goto");
		scanner();
		staBlock(&nChainTemp); //语句块
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
void fuzhi() //赋值语句只有1个操作数
{
	char res[10], num[10]; //num操作数
	if (syn == 10) //字符串
	{
		strcpy(res, token); //结果
		scanner();
		if (syn == 21) //=
		{
			scanner();
			strcpy(num, E());
			emit(res, num, "=", "");
		}
		else
		{
			stral += "缺少=号";
		}
	}
}
char* E() //Expression表达式
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
char* T() //Term项
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
char* F() //Factor因子
{
	char *res;
	res = (char *)malloc(10);
	if (syn == 10) //字符串
	{
		strcpy(res, token);
		scanner();
	}
	else if (syn == 20) //二进制数
	{
		_itoa((int)sum, res, 10); //整数转换为字符串
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
} //将p所链接的每个四元式的第四个分量都回填t
void backpatch(int p, int t)
{
	int w, circle = p;
	while (circle) //circle不为0的时候
	{
		w = atoi(fourCom[circle].result); //四元式circle第四分量内容
										  //strcpy(fourCom[circle].result,t); //把t填进四元式circle的第四分量
		sprintf(fourCom[circle].result, "%d", t);
		circle = w; //w记录的是链条上下一个四元式，移动！
	}
	return;
}
int merge(int p1, int p2) //合并p1和p2
{
	char circle, nResult;
	if (p2 == 0)
		nResult = p1;
	else
	{
		nResult = circle = p2;
		while (atoi(fourCom[circle].result)) //四元式第四个分量不为0
		{
			circle = atoi(fourCom[circle].result); //strcpy(fourCom[circle].result,p1);
			sprintf(fourCom[circle].result, "%s", p1);
		} //目的是用p1的值覆盖0
	}
	return nResult; //p2是头，p1覆盖0，接在p2后边
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
	ch = prog[p++]; //从prog中读出一个字符到ch中
	while (ch == ' ' || ch == '\n'||ch=='\r') //跳过空字符（无效输入）
		ch = prog[p++];
	if (((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z'))) //ch是字母字符
	{
		while (((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) || ((ch >= '0') && (ch <= '9')))
		{
			token[m++] = ch; //ch=>token
			ch = prog[p++]; //读下一个字符
		}
		token[m++] = '\0';
		p--; //回退一格
		syn = 10; //标识符
				  //如果是"begin","if","then","while","do","end"标识符中的一个
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
			sum = sum * 10 + ch - '0'; //ch中数字本身是当做字符存放的
			ch = prog[p++];
		}
		if (ch == '.')
		{
			isDecimal = 1;
			ch = prog[p++];
			countsyn = 0; //之前忘了清零,123.123+123.123#两个浮点数就无法识别
			while ((ch >= '0') && (ch <= '9'))
			{ //pow(x,y)计算x的y次幂
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
			{ //指数
				index = index * 10 + ch - '0';
				ch = prog[p++];
			}
			//10的幂
			//123e3代表123*10(3)
			//sum=sum*pow(10,index);是错误的
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
		if (((temp2 == '+') || (temp2 == '-')) && (repeat == 0)) //如果重复出现符号，才将后边的+，-视为正负号
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
			ch = prog[p++]; //读“-”下一个字符
			repeat = 0;
			goto IsNum;//转到数字的识别
		}
		if (((temp2 == '+') || (temp2 == '-')) && (repeat == 0)) //如果重复出现符号，才将后边的+，-视为正负号
		{
			repeat = 1; //预言会重复
						//ch=prog[p++];
						//读下一个字符
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
