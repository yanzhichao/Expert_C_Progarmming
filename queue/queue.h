#ifndef _QUEUE_
#define _QUEUE_

typedef struct tagnode{
	void* data;            //数据域指针，void类型指针可以指向任何数据类型           
	struct tagnode* next; 
}STNode,*ptrNode;


typedef struct tagQueue{
	
	ptrNode head;
	ptrNode tail;
	int len;
}Queue;
//创建一个链表
Queue creatQueue(void);  
//销毁一个链表
void destroryQueue(Queue* Q,void (*releaseData)(void *));
//向队列加入一个元素
int pushNodeToQueue(Queue* Q,void* data);
//从队列获取一个元素
void* getDataFromQueue(Queue* Q);
//获取队列的大小
int getSizeOfQueue(Queue* Q);

#endif