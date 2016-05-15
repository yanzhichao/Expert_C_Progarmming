
#include "stdlib.h"
#include "string"
#include "iostream"
using namespace std;

typedef struct tagNODE{      //声明节点
	int data;
	struct tagNODE* next;
}STNODE;

int main()
{
	int N=9;
	int M=5;
	STNODE* Temp;
	STNODE* Head;

	//建立循环链表
	Head=(STNODE*)malloc(sizeof(STNODE));   //头节点
	Head->data=1; //头节点值为1 
	Temp=Head;  

	for(int i=2;i<=N;i++)  //依此建立其他节点  尾插法
	{
		STNODE* newNODE=(STNODE*)malloc(sizeof(STNODE));//新结点
		newNODE->data=i;      //赋值
		newNODE->next=Head;   //新节点 即当前最后一个节点指向头节点构成循环链表
		Temp->next=newNODE;  //上一节点连接新节点
		Temp=newNODE;        //Temp复制为最后一个节点 继续插入 
	}
	//循环链表建立完毕

	STNODE* Visit=Head;    //定义一个访问链表指针 从头节点开始访问 
	while(1)
	{
		for(int i=1;i<M-1;i++)    //访问M次
			Visit=Visit->next;

		printf("%d",Visit->next->data); //输出淘汰者
		Visit->next=Visit->next->next; //删除Visit链表中淘汰节点
		Visit=Visit->next;             //从当前结点的下一个节点开始访问

		if(Visit->data==Visit->next->data)  //如果相等了 说明循环链表中只有一个节点
			break;                        //因此领导人产生
	}
	printf("Lead is %d\n",Visit->data);  
	getchar();
}