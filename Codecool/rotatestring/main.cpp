#include "iostream"
#include <math.h>
#include "stdlib.h"
using namespace std;
//直接复制串1AABCD为AABCDAABCD  然后直接查找CDAA就可以了  比较让浪费空间
int isRotateString(char* str1,char* str2)
{
	char* temp;
	int str1len=strlen(str1);
	int str2len=strlen(str2);
	if(str1len<str2len)
	{
		temp=(char*)malloc(str2len*2*sizeof(char));
		strcpy(temp,str2);
		strcat(temp,str2);
		if(char* p=strstr(temp,str1))
		{
			return true;
		}
		else
			return false;

	}
	else
	{
		temp=(char*)malloc(str1len*2*sizeof(char));
		strcpy(temp,str1);
		strcat(temp,str1);
		if(char* p=strstr(temp,str2))
			{
				return true;
		    }
		else
			return false;
	}

}

//循环查找，节约空间  比较浪费时间   写得太烂 你们可以改进下！
int isRotateString2(char* str1,char* str2)
{
	int len1=strlen(str1);
	int len2=strlen(str2);
	int isfind=0;
	for(int i=0;i<len1;i++)   //循环查找
	{
		int j=0;
		for(j=0;j<len2;j++)
			{
				if(i+j<len1)
				{
					if(str1[i+j]!=str2[j])
					{
						isfind==1;              //如果不同跳出
						break;
					}
				}
				else
				{
				  if(str1[i+j-len1]!=str2[j]) //如果已经找到串1的尾部回头
				  {
					  isfind==1;
				       break;
				  }
				}	
		   }

		if(isfind==0&&j==len2)      //如果 遍历完了str2 如果没有跳出过 说明被找到
			return 1;
	}
	return 0;
}
int main()
{
	char str1[20],str2[20];
	printf("please input first string\n");
    scanf("%s",&str1);
	printf("please input scend string\n");
	scanf("%s",&str2);
	if(isRotateString2(str1,str2))
		cout<<"TRUE"<<endl;
	else
		cout<<"Fales"<<endl;

	getchar();
}

