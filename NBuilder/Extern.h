#pragma once
#include<string>
using namespace std;
/*
��ʶ��              ID:101 (����ĸ���»��߿�ͷ,���������������ĸ���»���)
�ַ�������        ID:102,����û�д���ת���ַ���
�ַ�����           ID:103,����û�д���ת���ַ�
��������           ID:104
��ͨʵ��           ID:105
ָ��+/-��ѧ      ID:106
ָ����+/-��ѧ   ID:107
Ԥ����              ID:108
ע��                 ID:109

//�������ID:˵��,() [] .�ڽ������,���ﲻ���� , ? :  sizeof Ҳû����
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

//�����ID:
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


//�ؼ���ID
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
extern string keywords[];//�ؼ��ֱ�
extern string oprations[];//��������
extern string interpunctions[];//�����
extern short lextable[65][36];//�ʷ�����״̬ת����
int LexIndex(char ch);//�����ַ�ch��lextable�е��к�
