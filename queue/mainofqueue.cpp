#include "queue.h"
#include "stdio.h"
#include "stdlib.h"
int main()
{
	Queue IntQueue=creatQueue(); //建立一个队列
	for (int i=0;i<10;i++)
	{
		pushNodeToQueue(&IntQueue,(int*)i);  //向队列加入元素
	}

	for(int i=0;i<10;i++)
	{
		int a=(int)getDataFromQueue(&IntQueue);   //从队列获取元素
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