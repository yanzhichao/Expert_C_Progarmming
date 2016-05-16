#include "stdlib.h"
#include "stdio.h"
typedef struct tagNODE{
	int data;
	struct tagNODE* next;
}STNODE;

int main()
{
	int M=9;
	STNODE* Head;
	Head=(STNODE*)malloc(sizeof(STNODE));
	STNODE* Temp=Head;
	for(int i=1;i<=M;i++) //尾插法建立单链表，按顺序赋值
	{
		STNODE* newNODE=(STNODE*)malloc(sizeof(STNODE));
		newNODE->data=i;
		Temp->next=newNODE;
		newNODE->next=NULL;
		Temp=newNODE;
	}
	//打印原来的链表
	for(STNODE* temp=Head->next;temp!=NULL;temp=temp->next)
		printf("%d->",temp->data);
	printf("\n");
	//进行反转。 
	//要进行反转大概要有三个指针
	STNODE* Revese=NULL;   //已经反转的链表
    STNODE* Visit=Head->next;//当前需要反转的节点
	STNODE* Last=Head->next; //还没有反转的链表
    
	while(Visit!=NULL)    //当前需要反转的为空 那么结束
	{  
        Last=Last->next;  //位反转节点后移一位

		Visit->next=Revese; //将当前结点插入到已经反转的链表头部
		Revese=Visit;     //已经反转的头部变成当前结点
		Visit=Last;	      //当前结点更换为还未反转的节点，循环继续反转
	}
	STNODE* newHead=(STNODE *)malloc(sizeof(STNODE)); //申请一个新的头指针指向反转的链表
	newHead->next=Revese;

	//打印反转的链表
	for(STNODE* temp=newHead->next;temp!=NULL;temp=temp->next)
		printf("%d->",temp->data);
} 

