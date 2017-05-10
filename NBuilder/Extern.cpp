#include "StdAfx.h"
#include "Extern.h"

//操作符表ID=index+201
string oprations[]={
	"->","++","--","!","~","-","+","&","*","/","%","<<",">>","<",
	"<=",">",">=","==","!=","^","|","&&","||","=","*=","/=","%=",
	"+=","-=","<<=",">>=","&=","^=","|="
};

//界符表 ID=index+301
string interpunctions[]={
	"(", ")", "{", "}", "[", "]", ",", ".", ";", ":","?","#"
};

//关键字表,ID=index+401
string keywords[]={
	"auto", "double", "int", "struct",
	"break", "else", "long", "switch",
	"case", "enum", "register", "typedef", 
	"char", "extern", "return", "union",
	"const", "float", "short", "unsigned",
	"continue", "for", "signed", "void",
	"default", "goto", "sizeof", "volatile",
	"do", "if", "static", "while"
};

//词法分析状态转换表,其中-99表示当前状态下不能输入对应的字符,分析出错
short lextable[65][36]={
	//        1         2       3      4      5        6       7      8        9        10   11    12    13     14    15   16     17     18     19     20   21      22    23     24    25     26      27     28    29      30     31     32     33    34      35     36
	//       空格     \r      \n     tab     _     字母      E      e      数字      !      "       %      &      '       (      )       *       +       ,       -       .        /       :       ;       <       =       >       ?       [        ]       ^       {       |       }       ~      其他 
/* 00*/	{  0,      0 ,     0,      0,     1,      1,       1,     1,      7,       27,    2,    35,   30,     4,    52,  53,     33,    24,   58,     20,  59,    13,    61,   60,      37,     45,  41,  62,   56,     57,   47,    54,   50,    55,     29,    -99}, 
/* 01*/	{-101,-101,-101,-101,   1,      1,       1,     1,       1,   -101,-101, -101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101, -101,   -101, -101-101,  -101,-101,-101,-101,  -101},
/* 02*/	{   2,  -99,  -99,       2,    2,      2,       2,     2,      2,        2,    3,      2,      2,     2,     2,     2,    2,       2,       2,     2,     2,      2,      2,     2,      2,      2,      2,       2,      2,      2,     2,       2,      2,     2,     2,       2},
/* 03*/	{-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102,-102, -102,-102,-102,-102,-102,-102,-102},
/* 04*/	{  5,   -99,  -99,      5,     5,      5,       5,     5,      5,        5,     5,      5,      5,     5,    5,    5,      5,       5,      5,      5,     5,     5,      5,      5,      5,     5,      5,        5,      5,      5,     5,      5,      5,      5,     5,       5},
/* 05*/	{-99,  -99, -99,    -99, -99,  -99,     -99, -99,  -99,     -99,  -99,   -99,  -99,     6, -99, -99,  -99,   -99,   -99,   -99, -99,  -99,  -99,   -99,   -99,  -99,  -99,    -99,   -99,   -99,  -99,  -99,  -99,   -99,  -99,    -99},
/* 06*/	{-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103},
/* 07*/	{-104,-104, -104, -104, -104,-104,  10,  10,    7,      -104,-104,-104,-104,-104,-104,-104,-104,-104,-104, -104,  8,-104,  -104,  -104, -104,-104,-104,  -104, -104, -104,-104,-104,-104, -104,-104, -104},
/* 08*/	{-99,  -99, -99,   -99, -99,  -99,     -99,    -99,   9,    -99,   -99,    -99,   -99,  -99,-99,-99,  -99,    -99,  -99,   -99,  -99,  -99,   -99,  -99,   -99,  -99,  -99,   -99,   -99,    -99, -99,   -99,   -99,    -99, -99,    -99},
/* 09*/	{-105,-105,-105,-105,-105,-105,     10,   10,     9,  -105, -105, -105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105, -105,-105,-105, -105 ,-105,  -105, -105,-105, -105, -105, -105,-105},
/* 10*/	{ -99, -99, -99,   -99,  -99,  -99,   -99,   -99,     12,   -99,   -99,  -99,  -99,  -99,  -99,  -99, -99,   11,  -99,    11,   -99,  -99,  -99,  -99,   -99,  -99,  -99,  -99, -99,   -99,  -99,   -99,    -99,  -99,    -99,     -99},
/* 11*/	{-106,-106,-106,-106,-106,-106,-106,-106,    11,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106},
/* 12*/	{-107,-107,-107,-107,-107,-107,-107,-107,    12,-107,-107,-107,-107,-107,-107,-107,-107,-107,-107,-107,-107,-107,-107,-107,-107,-107,-107,-107,-107,-107,-107,-107,-107,-107,-107,-107},
/* 13*/	{-210, -99, -99, -210, -210,-210,-210, -210, -210,  -210, -210,-210,-210,-210,-210,-210,16, -210,-210,-210,-210,    14,-210,-210,  -210,  19,-210,-210,-210,-210,-210,-210,-210,-210,          -210,   -210},
/* 14*/	{14,   14,     15,  14,    14,      14,   14,    14,     14,      14,   14,   14,     14,   14,    14,  14,   14,   14,   14,   14,   14,      14,   14,   14,    14,   14,     14,   14,     14,    14,    14,    14,   14,    14,    14,     14},
/* 15*/	{-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109},
/* 16*/	{16,   16,    16,    16,   16,     16,    16,   16,      16,      16,   16,   16,     16,   16,    16,  16,   17,   16,      16,   16,    16,   16,  16,   16,    16,    16,    16,   16,     16,    16,     16,    16,   16,   16,      16,     16},
/* 17*/	{16,   16,   16,    16,    16,    16,     16,    16,     16,     16,    16,   16,     16,   16,    16,  16,   17,   16,     16,    16,    16,   18,  16,   16,    16,    16,    16,   16,     16,     16,    16,    16,   16,   16,      16,     16},
/* 18*/	{-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109,-109},
/* 19*/	{-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226,-226},
	//        1         2       3      4      5        6       7       8        9        10     11     12     13      14      15     16      17     18     19     20    21      22     23     24     25      26      27     28     29      30      31      32      33     34      35      36
	//       空格     \r      \n     tab     _     字母      E       e      数字      !        "        %       &        '        (         )        *       +       ,       -        .        /        :       ;        <       =       >       ?        [        ]        ^        {        |        }       ~       其他 
/* 20*/	{-206,-206,-206,-206,-206, -206, -206, -206, -206,  -206, -206, -206, -206, -206,  -206,  -206, -206, -206, -206,  23,-206, -206,-206,-206, -206,     21,    22, -206, -206, -206, -206,  -206,  -206,-206,  -206,  -206},
/* 21*/	{-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229,-229},
/* 22*/	{-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201,-201},
/* 23*/	{-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203,-203},
/* 24*/	{-207,-207,-207,-207,-207, -207, -207, -207, -207,  -207, -207, -207, -207, -207,  -207,  -207, -207,    26, -207,-207,-207,-207,-207,-207, -207,     25, -207, -207,-207, -207,  -207, -207,  -207,-207,  -207,  -207},
/* 25*/	{-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228,-228},
/* 26*/	{-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202,-202},
/* 27*/	{-204,-204,-204,-204,-204, -204,-204, -204, -204,   -204 ,-204,-204,  -204, -204,  -204,  -204, -204, -204, -204, -204,-204,-204,-204,-204,-204,     28,-204, -204,-204, -204,  -204,  -204, -204, -204, -204,  -204},
/* 28*/	{-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219,-219},
/* 29*/	{-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205,-205},
/* 30*/	{-208,-208,-208,-208,-208, -208,-208,-208, -208,   -208,  -208,-208,    32,  -208,  -208,  -208,  -208, -208,-208, -208,-208,-208,-208,-208,-208,      31,-208, -208, -208, -208, -208, -208,  -208,-208, -208,   -208},
/* 31*/	{-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232,-232},
/* 32*/	{-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222,-222},
/* 33*/	{-209,-209,-209,-209,-209,-209,-209,-209,-209,    -209,   -209,-209,  -209,-209,  -209,  -209,   -209, -209,-209, -209,-209,-209,-209,-209,-209,     34, -209, -209, -209, -209, -209, -209, -209, -209, -209,   -209},
/* 34*/	{-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225,-225},
/* 35*/	{-211,-211,-211,-211,-211,-211,-211,-211,-211,     -211,  -211, -211, -211,-211,  -211,  -211,   -211, -211, -211, -211,-211,-211,-211,-211,-211,    36,-211, -211,-211, -211, -211, -211,  -211, -211, -211,   -211},
/* 36*/	{-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227,-227},
/* 37*/	{-214,-214,-214,-214,-214,-214,-214,-214,-214,   -214,   -214, -214,  -214,-214,  -214,  -214,   -214,-214,-214,-214,   -214,-214,-214,-214,   38,     40,-214,-214,-214,-214, -214,-214,   -214, -214, -214,   -214},
/* 38*/	{-212,-212,-212,-212,-212,-212,-212,-212,-212,  -212,    -212,-212,  -212, -212,  -212,  -212,   -212,-212,-212,-212,  -212, -212,-212,-212, -212,    39,-212,-212,-212,-212,-212,-212,   -212,  -212,   -212,  -212},
/* 39*/	{-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230,-230},
/* 40*/	{-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215,-215},
	//        1         2       3      4      5        6       7       8      9     10     11     12     13     14     15     16      17     18     19     20    21      22     23     24     25      26      27     28     29      30      31      32      33     34      35      36
	//       空格     \r      \n     tab     _     字母      E       e   数字      !        "     %       &       '       (         )        *       +       ,       -        .        /        :       ;        <       =       >       ?        [        ]        ^        {        |        }       ~       其他 
/* 41*/	{-216,-216,-216,-216,-216, -216,-216,-216,-216,-216,-216, -216,-216, -216, -216, -216, -216, -216, -216, -216, -216, -216,-216,-216 ,-216,   44,    42, -216, -216, -216, -216, -216,  -216, -216, -216,   -216},
/* 42*/	{-213,-213,-213,-213,-213, -213,-213,-213,-213,-213,-213, -213,-213, -213, -213, -213, -213, -213, -213, -213, -213, -213,-213,-213, -213,   43, -213,-213,-213, -213, -213, -213,  -213,  -213,-213,  -213},
/* 43*/	{-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231,-231},
/* 44*/	{-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217,-217},
/* 45*/	{-224,-224,-224,-224,-224, -224,-224,-224,-224,-224,-224,-224,-224,-224,  -224,  -224, -224, -224, -224, -224, -224, -224,-224,-224, -224,   46,-224,-224,-224,-224, -224 , -224,  -224, -224, -224,  -224},
/* 46*/	{-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218,-218},
/* 47*/	{-220,-220,-220,-220,-220,-220,-220,-220,-220, -220,-220,-220,-220,-220  ,-220,  -220,  -220,-220, -220, -220, -220, -220 ,-220, -220,-220,  48,-220,-220,-220,-220,-220,-220,-220,-220,-220,-220},
/* 48*/	{-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233,-233},
/* 49*/	{-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223,-223},
/* 50*/	{-221,-221,-221,-221,-221,-221,-221,-221,-221, -221,-221,-221, -221,-221,-221,   -221,  -221,  -221,  -221,-221,-221,-221, -221, -221, -221,   51 ,-221,-221, -221,-221,  -221, -221,   49, -221    ,-221,-221},
/* 51*/	{-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234,-234},
/* 52*/	{-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301,-301},
/* 53*/	{-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302,-302},
/* 54*/	{-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303,-303},
/* 55*/	{-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304,-304},
/* 56*/	{-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305,-305},
/* 57*/	{-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306,-306},
/* 58*/	{-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307,-307},
/* 59*/	{-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308,-308},
/* 60*/	{-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309,-309},
/* 61*/	{-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310,-310},
/* 62*/	{-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311,-311},
/* 63*/	{0},
/* 64*/	{0}
};

int LexIndex(char ch){//返回字符ch的lextable中的列号
	switch(ch){
	case ' ':
		return 0;
	case '\r':
		return 1;
	case '\n':
		return 2;
	case '\t':
		return 3;
	case '_':
		return 4;
	case '!':
		return 9;
	case '"':
		return 10;
	case '%':
		return 11;
	case '&':
		return 12;
	case '\'':
		return 13;
	case '(':
		return 14;
	case ')':
		return 15;
	case '*':
		return 16;
	case '+':
		return 17;
	case ',':
		return 18;
	case '-':
		return 19;
	case '.':
		return 20;
	case '/':
		return 21;
	case ':':
		return 22;
	case ';':
		return 23;
	case '<':
		return 24;
	case '=':
		return 25;
	case '>':
		return 26;
	case '?':
		return 27;
	case '[':
		return 28;
	case ']':
		return 29;
	case '^':
		return 30;
	case '{':
		return 31;
	case '|':
		return 32;
	case '}':
		return 33;
	case '~':
		return 34;
	}
	if(ch=='e')
		return 7;
	if(ch=='E')
		return 6;
	if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
		return 5;
	if(ch<='9'&&ch>='0')
		return 8;
	return 35;
}