//这是一种利用字符串数组实现的大数运算
//实现只提供计算的方法，并不考虑越界，正负号等异常的判断，
//用户应该主动考虑这些问题，实时上用户完全可以用一个结构来管理
//这些细节。包括动态的确定字符串数组的大小。以及正负号的保存
#include "xp.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#define  DEBUG 0

#define T XP_T
#define  BASE 10  //这里是设置基数的 如果是10进制的运算 则设置为10

#if DEBUG
char DebugStr[1024];
#endif

//单数位除法，即y为不超过10的数 x为一个大数 z=x/y  
int XP_quotion(int n,T z, T x,int y)
{
	int i;
	unsigned int carry=0;
	if(y>9)  //不能大于9
		return -1;

	for(i=n-1;i>=0;i--)
	{
		carry=x[i]+carry*BASE;
		z[i]=carry/y;
		carry=carry%y;
	}
	return carry;
}

//单数位乘法，即y为不超过10的数 x为一个大数 z=x*y  
int XP_product(int n,T z,T x, int y)
{
	int i;
	unsigned int carry=0;
	if(y>9)  //不能大于9
		return -1;

	for(i=0;i<n;i++)
	{
		carry=x[i]*y+carry;
		z[i]=carry%BASE;
		carry=carry/BASE;
	}
	return carry;
}
//大数减法 z=x-y，borrow 为上一次借位，默认为0

int XP_sub(int n,T z,T x,T y,int borrow)
{
	int i;
	for(i=0;i<n;i++)
	{
		borrow=x[i]+BASE-borrow-y[i];  //向上借位然后相减
		z[i]=borrow%BASE;
		borrow=1-borrow/BASE; //如果借位被用掉了  那么borrow/BASE=0  borrow=1 说明下一次要先将借位减掉，否则则不需要
	}
	return borrow;
}
//大数加法，z=x+y，carry 为上一次进位，默认为0
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


//改函数返回x中实际包含的有效位数数
//如 x="130000" 返回2位
int XP_length(int n,T x)
{
	while(n>1&&x[n-1]==0)
		n--;
	return n;
}


//大数乘法  z=x*y 
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
			for(;j<m+n-i;j++)  //处理最后的进位carry 这里应该假设z的最大位数只有n+m位 超过则用进位carryout表示
			{
				carry+=z[i+j];
				z[i+j]=carry%BASE;
				carry=carry/BASE;
			}
			carryout|=carry;
	    }
	   return carry;
}
//大数除法的基本思想是从被除数的高几位（能够被int容下）来除于除数的高几位来得到商，
//即从高到低的计算，与我们笔算的方式相似
//问题在于如何来快速的计算，
//这里采用的方式是每次计算一位商，然后从被除数中减去该商*除数的大小，然后再循环的计算
//此处的难点在于用什么方法来确定这一位商
//这里采用的方式是用高三位除数来处于高二位被除数来确定商，这种方式确定的商有可能会超过
//实际的商，理论上有可能会大1，因此需要通过判断大小来确定实际的商。

int XP_div(int n,T q,T x,int m, T y,T r, T tmp)
{
	int nx=n,my=m;
	n=XP_length(n,x);  //求取被除数实际位数
	m=XP_length(m,y); //求取除数实际位数
	if(m==1)
	{
       if(y[0]==0)
		   return 0;
	   r[0]=XP_quotion(nx,q,x,y[0]);
	   memset(r+1,'\0',my-1);
	}
	else if(m>n)         //除数比被除数小
	{
		memset(q,'\0',nx); //商为零
		memcpy(r,x,n);  //余数即为除数
		memset(r+n,'\0',my-n); //其他位置置零
	}
	else{
		int k;
		unsigned char *rem =tmp,*dq=tmp+n+1; //用rem指向被除数第一个数，用dq指向结尾后两个数
		assert(2<=m&&m<=n);
		memcpy(rem,x,n);  //将被除数赋值给rem
		rem[n]=0;         //最高位补零，为方便计算
		for(k=n-m;k>=0;k--)   //商是从n-m位开始的，然后依此往低位移动 即k
		{
			int qk;
			int i;
			assert(2<=m&&m<=k+m&&k+m<=n);
			{
				int km=k+m;
				unsigned long y2=y[m-1]*BASE+y[m-2];//除数最高两位的值 BASE此处为10，即10进制
				unsigned long r3=rem[km]*(BASE*BASE)+rem[km-1]*BASE+rem[km-2];//从k+m开始一次后移1位的三位数的值，即被除数的高三位
				qk=r3/y2;  //被除数高三位/除数高二位
				if(qk>=BASE)//当出现大于10
					qk=BASE-1;
			}
			dq[m]=XP_product(m,dq,y,qk);//计算商为qk时 qk*y的大小存入dq  即商*除数y的大小 即dq=y*qk

			for(i=m;i>0;i--)   ////判断dq是否比被除数小
				if(rem[i+k]!=dq[i])  
					break;            //从最高位开始比较，当不相同时就退出
			if(rem[i+k]<dq[i])        //退出后判断不相同的这一位是被除数rem大还是dq大
			{
				dq[m]=XP_product(m,dq,y,--qk); //如果是dq大 说明商qk取大了，--qk ，重新计算dq
			}
			q[k]=qk;   //将商qk存下
			{
				int borrow;
				assert(0<=k&&k<=k+m);
				borrow=XP_sub(m+1,&rem[k],&rem[k],dq,0);  //从除数中高k+m位减去dq 即目前的得到的商的大小
				assert(borrow==0);

			}
			//后移动一位重复这种计算。

		}
		
		memcpy(r,rem,m); //保存余数

		//将q 和r剩余的空间用0填充避免错误
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


//以下两个函数，具有扩展参数base 和end  用于对非10进制运算时的相互转换
//但是现有的代码并没有实现功能，一次这两个参数可以随意传入。

//从str转换为XP_T 类型  str类型低位在前。str="1200000" 表示为 21. 
//即从str="1200000" 转化为z={'\1','\2','\0','\0','\0','\0','\0','\0'} 数值类型
int XP_fromstr(int n,T z,const char *str,int base,char** end)
{
      int i;
	  for(i=0;i<n;i++)
	  {
		  z[i]=str[i]-'0';
	  }
}

//从数值类型转换为字符串类型，并且调整顺序为正常阅读顺序，高位在前。
int XP_tostr(int n, T z,char* outstr,int base, char** end)
{
	int i;
	for(i=0;i<n;i++)
	{
		outstr[n-1-i]=z[i]+'0';
	}
}