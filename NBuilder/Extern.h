#pragma once
#include<string>
using namespace std;
/*
标识符              ID:101 (以字母或下划线开头,后面可以是数字字母或下划线)
字符串常量        ID:102,这里没有处理转意字符串
字符常量           ID:103,这里没有处理转意字符
整数常量           ID:104
普通实型           ID:105
指数+/-科学      ID:106
指数无+/-科学   ID:107
预处理              ID:108
注释                 ID:109

//运算符的ID:说明,() [] .在界符中有,这里不给出 , ? :  sizeof 也没给出
->           ID:201
++          ID:202
--            ID:203
!              ID:204
~             ID:205
-              ID:206
+             ID:207
&             ID:208
*             ID:209
/              ID:210
%            ID:211
<<           ID:212
>>           ID:213
<             ID:214
<=          ID:215
>             ID:216
>=           ID:217
==           ID:218
!=            ID:219
^             ID:220
|              ID:221
&&           ID:222
||             ID:223
=             ID:224
*=           ID:225
/=           ID:226
%=          ID:227
+=           ID:228
-=           ID:229
<<=       ID:230
>>=        ID:231
&=         ID:232
^=         ID:233
|=           ID:234

//界符的ID:
(                     ID:301
)                     ID:302
{                    ID:303
}                    ID:304
[                     ID:305
]                     ID:306
,                     ID:307
.                     ID:308
;                     ID:309
:                     ID:310
?                     ID:311
#                    ID:312


//关键字ID
auto               ID:401
double            ID:402
int                  ID:403
struct             ID:404
break             ID:405
else                ID:406
long               ID:407
switch            ID:408
case               ID:409
enum             ID:410
register          ID:411
typedef          ID:412 
char               ID:413
extern           ID:414
return            ID:415
union             ID:416
const             ID:417
float               ID:418
short             ID:419
unsigned        ID:420
continue        ID:421
for                 ID:422
signed            ID:423
void               ID:424
default            ID:425
goto              ID:426
sizeof            ID:427
volatile            ID:428
do                ID:429
if                   ID:430
static             ID:431
while              ID:432
*/


#define keywords_size 32
#define oprations_size 34
#define interpunctions_size 11
extern string keywords[];//关键字表
extern string oprations[];//操作符表
extern string interpunctions[];//界符表
extern short lextable[65][36];//词法分析状态转换表
int LexIndex(char ch);//返回字符ch的lextable中的列号
