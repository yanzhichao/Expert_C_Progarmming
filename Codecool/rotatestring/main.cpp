#include "iostream"
#include <math.h>
#include "stdlib.h"
using namespace std;
//ֱ�Ӹ��ƴ�1AABCDΪAABCDAABCD  Ȼ��ֱ�Ӳ���CDAA�Ϳ�����  �Ƚ����˷ѿռ�
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

//ѭ�����ң���Լ�ռ�  �Ƚ��˷�ʱ��   д��̫�� ���ǿ��ԸĽ��£�
int isRotateString2(char* str1,char* str2)
{
	int len1=strlen(str1);
	int len2=strlen(str2);
	int isfind=0;
	for(int i=0;i<len1;i++)   //ѭ������
	{
		int j=0;
		for(j=0;j<len2;j++)
			{
				if(i+j<len1)
				{
					if(str1[i+j]!=str2[j])
					{
						isfind==1;              //�����ͬ����
						break;
					}
				}
				else
				{
				  if(str1[i+j-len1]!=str2[j]) //����Ѿ��ҵ���1��β����ͷ
				  {
					  isfind==1;
				       break;
				  }
				}	
		   }

		if(isfind==0&&j==len2)      //��� ��������str2 ���û�������� ˵�����ҵ�
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

