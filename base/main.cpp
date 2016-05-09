#include "cv.h";
#include "iostream"
using namespace std;
typedef  int myint ;


 myint sx ;
typedef struct STNODE
{
	int a;
	int *b;
	struct STNODE* node;

} STNODE,*pSTNODE;


int a[6]={1,1,2,4,5,6};

char * printArray1(char **a)
{
	int length=sizeof(a);
	cout<<"length="<<length<<endl;
	printf("%c",*(a+2));
	return *a;
}

char * printArray(char a[1][10])
{
	int length=sizeof(a);
	a[2][0]=0x31;
	cout<<"length="<<length<<endl;
	printf("%s",*(a+2));
	return *a;
}

void printArrayUsual(int* a,int width,int height)
{
	for(int j=0;j<height;j++)
	{
		for(int i=0;i<width;i++)
			cout<<(a+j*width)[i]<<" ";
		cout<<endl;
	}
}

void printArrayString(char** a,int nlines)
{
	for(int i=0;i<nlines;i++)
	{
		printf("%s\n",a[i]);
	}
}

//求小于n的一千以下的所有3和5的倍数的和
int sumThe3and4Multiper(int n)
{
	int MultipleThr=1;
	int MultipleFive=1;
	int sum=0;
	int i=0;
	while(MultipleThr<n)
	{
		i++;
		if((MultipleFive=5*i)<n)
		{ 
			sum+=MultipleFive;
		}

		if((MultipleThr=3*i)<1000&&MultipleThr%5!=0)
		{
			sum+=MultipleThr;
		}        
	}
	return sum;
}

int sumofEvenValuedInFibonacci(int n)
{
	int fir=1,sced=2;
	int next=3;
	int sum=2;
	while(next<n)
	{
		int temp=next;
		next=next+sced;
		sced=temp;
		if(next%2==0)
			sum+=next;
	}
	return sum;
}
int main()
{
	cout<<sumofEvenValuedInFibonacci(4000000)<<endl;
    getchar();
}


void f(void)
{

	

	char  tr[3][10]={"test1","stt1"};
	char  tr3[4][15]={"sdd3","xtdt"};
	char* s[2];
	s[0]=&tr[0][0];
	s[1]=&tr[1][0];
	printArrayString(s,2);
	s[0]=&tr3[0][0];
	s[1]=&tr3[1][0];
	printArrayString(s,2);
}