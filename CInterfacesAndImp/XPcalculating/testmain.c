#include "stdio.h"
#include "stdlib.h"
#include "xp.h"


int main()
{
	char x[]="1355660000";  //10λ�� 665531
	char y[]="1227300000";  //10λ�� 37221
	char Tx[10];
	char Ty[10];
	char out[20]={0};
	char outstr[20]={0};
	char qout[10]={0};//��
	char rout[10]={0};//����
	char tmp[20]={0}; //����
	XP_fromstr(10,Tx,x,10,&Tx);  //ת��Ϊ��ֵ���� //����str="1200000" ת��Ϊz={'\1','\2','\0','\0','\0','\0','\0','\0'} ��ֵ����
	XP_fromstr(10,Ty,y,10,&Ty);
 	XP_div(10,qout,Tx,10,Ty,rout,tmp);  //665531/37221 

	XP_tostr(10,qout,outstr,10,&outstr); //��ֵ����ת��Ϊ�ַ�������
	printf("��=%s\n",outstr);

	XP_tostr(10,rout,outstr,10,&outstr);
	printf("����=%s\n",outstr);


	getchar();


}