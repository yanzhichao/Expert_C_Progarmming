//����һ�������ַ�������ʵ�ֵĴ�������
//ʵ��ֻ�ṩ����ķ�������������Խ�磬�����ŵ��쳣���жϣ�
//�û�Ӧ������������Щ���⣬ʵʱ���û���ȫ������һ���ṹ������
//��Щϸ�ڡ�������̬��ȷ���ַ�������Ĵ�С���Լ������ŵı���
#include "xp.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#define  DEBUG 0

#define T XP_T
#define  BASE 10  //���������û����� �����10���Ƶ����� ������Ϊ10

#if DEBUG
char DebugStr[1024];
#endif

//����λ��������yΪ������10���� xΪһ������ z=x/y  
int XP_quotion(int n,T z, T x,int y)
{
	int i;
	unsigned int carry=0;
	if(y>9)  //���ܴ���9
		return -1;

	for(i=n-1;i>=0;i--)
	{
		carry=x[i]+carry*BASE;
		z[i]=carry/y;
		carry=carry%y;
	}
	return carry;
}

//����λ�˷�����yΪ������10���� xΪһ������ z=x*y  
int XP_product(int n,T z,T x, int y)
{
	int i;
	unsigned int carry=0;
	if(y>9)  //���ܴ���9
		return -1;

	for(i=0;i<n;i++)
	{
		carry=x[i]*y+carry;
		z[i]=carry%BASE;
		carry=carry/BASE;
	}
	return carry;
}
//�������� z=x-y��borrow Ϊ��һ�ν�λ��Ĭ��Ϊ0

int XP_sub(int n,T z,T x,T y,int borrow)
{
	int i;
	for(i=0;i<n;i++)
	{
		borrow=x[i]+BASE-borrow-y[i];  //���Ͻ�λȻ�����
		z[i]=borrow%BASE;
		borrow=1-borrow/BASE; //�����λ���õ���  ��ôborrow/BASE=0  borrow=1 ˵����һ��Ҫ�Ƚ���λ��������������Ҫ
	}
	return borrow;
}
//�����ӷ���z=x+y��carry Ϊ��һ�ν�λ��Ĭ��Ϊ0
int XP_add(int n,T z,T x, T y, int carry)
{
	int i;
	for(i=0;i<n;i++)
	{
		carry=carry+x[i]+y[i];
		z[i]=carry%BASE;
		carry/=BASE;
	}
	return carry;
}


//�ĺ�������x��ʵ�ʰ�������Чλ����
//�� x="130000" ����2λ
int XP_length(int n,T x)
{
	while(n>1&&x[n-1]==0)
		n--;
	return n;
}


//�����˷�  z=x*y 
int XP_mul(T z,int n,T x,int m ,T y)
{
	int i,j;
	int carry;
	int carryout=0;
	for(i=0;i<n;i++)
		{
			carry=0;
			for(j=0;j<m;j++)
			{
				carry=x[i]*y[j]+carry+z[i+j];
				z[i+j]=carry%BASE;
				carry=carry/BASE; 
			}
			for(;j<m+n-i;j++)  //�������Ľ�λcarry ����Ӧ�ü���z�����λ��ֻ��n+mλ �������ý�λcarryout��ʾ
			{
				carry+=z[i+j];
				z[i+j]=carry%BASE;
				carry=carry/BASE;
			}
			carryout|=carry;
	    }
	   return carry;
}
//���������Ļ���˼���Ǵӱ������ĸ߼�λ���ܹ���int���£������ڳ����ĸ߼�λ���õ��̣�
//���Ӹߵ��͵ļ��㣬�����Ǳ���ķ�ʽ����
//����������������ٵļ��㣬
//������õķ�ʽ��ÿ�μ���һλ�̣�Ȼ��ӱ������м�ȥ����*�����Ĵ�С��Ȼ����ѭ���ļ���
//�˴����ѵ�������ʲô������ȷ����һλ��
//������õķ�ʽ���ø���λ���������ڸ߶�λ��������ȷ���̣����ַ�ʽȷ�������п��ܻᳬ��
//ʵ�ʵ��̣��������п��ܻ��1�������Ҫͨ���жϴ�С��ȷ��ʵ�ʵ��̡�

int XP_div(int n,T q,T x,int m, T y,T r, T tmp)
{
	int nx=n,my=m;
	n=XP_length(n,x);  //��ȡ������ʵ��λ��
	m=XP_length(m,y); //��ȡ����ʵ��λ��
	if(m==1)
	{
       if(y[0]==0)
		   return 0;
	   r[0]=XP_quotion(nx,q,x,y[0]);
	   memset(r+1,'\0',my-1);
	}
	else if(m>n)         //�����ȱ�����С
	{
		memset(q,'\0',nx); //��Ϊ��
		memcpy(r,x,n);  //������Ϊ����
		memset(r+n,'\0',my-n); //����λ������
	}
	else{
		int k;
		unsigned char *rem =tmp,*dq=tmp+n+1; //��remָ�򱻳�����һ��������dqָ���β��������
		assert(2<=m&&m<=n);
		memcpy(rem,x,n);  //����������ֵ��rem
		rem[n]=0;         //���λ���㣬Ϊ�������
		for(k=n-m;k>=0;k--)   //���Ǵ�n-mλ��ʼ�ģ�Ȼ����������λ�ƶ� ��k
		{
			int qk;
			int i;
			assert(2<=m&&m<=k+m&&k+m<=n);
			{
				int km=k+m;
				unsigned long y2=y[m-1]*BASE+y[m-2];//���������λ��ֵ BASE�˴�Ϊ10����10����
				unsigned long r3=rem[km]*(BASE*BASE)+rem[km-1]*BASE+rem[km-2];//��k+m��ʼһ�κ���1λ����λ����ֵ�����������ĸ���λ
				qk=r3/y2;  //����������λ/�����߶�λ
				if(qk>=BASE)//�����ִ���10
					qk=BASE-1;
			}
			dq[m]=XP_product(m,dq,y,qk);//������Ϊqkʱ qk*y�Ĵ�С����dq  ����*����y�Ĵ�С ��dq=y*qk

			for(i=m;i>0;i--)   ////�ж�dq�Ƿ�ȱ�����С
				if(rem[i+k]!=dq[i])  
					break;            //�����λ��ʼ�Ƚϣ�������ͬʱ���˳�
			if(rem[i+k]<dq[i])        //�˳����жϲ���ͬ����һλ�Ǳ�����rem����dq��
			{
				dq[m]=XP_product(m,dq,y,--qk); //�����dq�� ˵����qkȡ���ˣ�--qk �����¼���dq
			}
			q[k]=qk;   //����qk����
			{
				int borrow;
				assert(0<=k&&k<=k+m);
				borrow=XP_sub(m+1,&rem[k],&rem[k],dq,0);  //�ӳ����и�k+mλ��ȥdq ��Ŀǰ�ĵõ����̵Ĵ�С
				assert(borrow==0);

			}
			//���ƶ�һλ�ظ����ּ��㡣

		}
		
		memcpy(r,rem,m); //��������

		//��q ��rʣ��Ŀռ���0���������
		{ 
			int i;
			for(i=n-m+1;i<nx;i++)
			{
				q[i]=0;
			}
			for(i=m;i<my;i++)
				r[i]=0;

		}
	}
	return 1;

}


//��������������������չ����base ��end  ���ڶԷ�10��������ʱ���໥ת��
//�������еĴ��벢û��ʵ�ֹ��ܣ�һ�������������������⴫�롣

//��strת��ΪXP_T ����  str���͵�λ��ǰ��str="1200000" ��ʾΪ 21. 
//����str="1200000" ת��Ϊz={'\1','\2','\0','\0','\0','\0','\0','\0'} ��ֵ����
int XP_fromstr(int n,T z,const char *str,int base,char** end)
{
      int i;
	  for(i=0;i<n;i++)
	  {
		  z[i]=str[i]-'0';
	  }
}

//����ֵ����ת��Ϊ�ַ������ͣ����ҵ���˳��Ϊ�����Ķ�˳�򣬸�λ��ǰ��
int XP_tostr(int n, T z,char* outstr,int base, char** end)
{
	int i;
	for(i=0;i<n;i++)
	{
		outstr[n-1-i]=z[i]+'0';
	}
}