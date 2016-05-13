#include "stdlib.h"
#include "string"
#include "iostream"
using namespace std;

unsigned int sumTheOnesInAInter(unsigned int N)
{
	unsigned int sum=0;
	while(N!=0)
	{
		if(N%10==1)sum++;
		N=N/10;

	}
	return sum;
}

unsigned int f(unsigned int n)
{
	unsigned int sum=0;
	for(unsigned int i=1;i<=n;i++)
		sum+=sumTheOnesInAInter(i);
	return sum;
}



int main()
{
   cout<<f(10000000);
   getchar();
}