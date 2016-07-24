#include "stdio.h"
#include "stdlib.h"
#include "xp.h"


int main()
{
	char x[]="1355660000";  //10位数 665531
	char y[]="1227300000";  //10位数 37221
	char Tx[10];
	char Ty[10];
	char out[20]={0};
	char outstr[20]={0};
	char qout[10]={0};//商
	char rout[10]={0};//余数
	char tmp[20]={0}; //缓存
	XP_fromstr(10,Tx,x,10,&Tx);  //转换为数值类型 //即从str="1200000" 转化为z={'\1','\2','\0','\0','\0','\0','\0','\0'} 数值类型
	XP_fromstr(10,Ty,y,10,&Ty);
 	XP_div(10,qout,Tx,10,Ty,rout,tmp);  //665531/37221 

	XP_tostr(10,qout,outstr,10,&outstr); //数值类型转换为字符串类型
	printf("商=%s\n",outstr);

	XP_tostr(10,rout,outstr,10,&outstr);
	printf("余数=%s\n",outstr);


	getchar();


}