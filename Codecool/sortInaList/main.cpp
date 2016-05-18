#include "stdlib.h"
#include "stdio.h"
#include "time.h"
typedef struct tagNODE{
	int data;
	struct tagNODE* next;
}STNODE;

int main()
{
	int M=10;
	STNODE* Head;
	Head=(STNODE*)malloc(sizeof(STNODE));
	STNODE* Temp=Head;
	srand(time(0));
	for(int i=1;i<=M;i++) //尾插法建立单链表，随机赋值
	{
		STNODE* newNODE=(STNODE*)malloc(sizeof(STNODE));
		newNODE->data=rand()%100;
		Temp->next=newNODE;
		newNODE->next=NULL;
		Temp=newNODE;
	}
	//打印原来的链表
	for(STNODE* temp=Head->next;temp!=NULL;temp=temp->next)
		printf("%d->",temp->data);
	printf("\n");

	STNODE* Last=Head;
	while(Last->next!=NULL)   //当所有节点都被删除那么结束
	{
		STNODE* preMaxNode;   //存储最大值的前一个节点
		preMaxNode=Last;      //默认最大值为第一个节点
		STNODE* preNode=Last;      //当前访问节点的前一个节点记录
		for(STNODE* temp=Last;temp!=NULL; preNode=temp,temp=temp->next) //从头几点开始循环访问
		{                                                               //每一次都记录前一个节点
			
			if(preMaxNode->next->data<=temp->data)             //判断当前结点是否比已知最大值大
			{ 
				preMaxNode=preNode;                 //若是，则更新最大值节点的前一个节点
			}                                                                                     
		}
		STNODE* maxNode=preMaxNode->next;       //连接下一个节点，松开最大值节点插入到最前面               
		preMaxNode->next=maxNode->next;                

		maxNode->next=Last->next;   //将最大值的结点插入到最前面
		Last->next=maxNode;          
		Last=maxNode;              //从下一个节点开始接着排列剩下节点。
	}
    
	for(STNODE* temp=Head->next;temp!=NULL;temp=temp->next)
		printf("%d->",temp->data);
	getchar();


}
