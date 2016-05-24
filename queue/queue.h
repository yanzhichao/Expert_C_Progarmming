#ifndef _QUEUE_
#define _QUEUE_

typedef struct tagnode{
	void* data;            //������ָ�룬void����ָ�����ָ���κ���������           
	struct tagnode* next; 
}STNode,*ptrNode;


typedef struct tagQueue{
	
	ptrNode head;
	ptrNode tail;
	int len;
}Queue;
//����һ������
Queue creatQueue(void);  
//����һ������
void destroryQueue(Queue* Q,void (*releaseData)(void *));
//����м���һ��Ԫ��
int pushNodeToQueue(Queue* Q,void* data);
//�Ӷ��л�ȡһ��Ԫ��
void* getDataFromQueue(Queue* Q);
//��ȡ���еĴ�С
int getSizeOfQueue(Queue* Q);

#endif