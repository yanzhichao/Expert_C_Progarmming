#include "queue.h"
#include "stdio.h"
#include "stdlib.h"
int main()
{
	Queue IntQueue=creatQueue(); //����һ������
	for (int i=0;i<10;i++)
	{
		pushNodeToQueue(&IntQueue,(int*)i);  //����м���Ԫ��
	}

	for(int i=0;i<10;i++)
	{
		int a=(int)getDataFromQueue(&IntQueue);   //�Ӷ��л�ȡԪ��
		printf("%d ",a);
	}
	printf("\n");
	for (int i=0;i<10;i++)
	{
		pushNodeToQueue(&IntQueue,(int*)i);
	}
	//destroryQueue(&IntQueue,NULL);
	for(int i=0;i<10;i++)
	{
		int a=(int)getDataFromQueue(&IntQueue);
		printf("%d ",a);
	}
	getchar();
}