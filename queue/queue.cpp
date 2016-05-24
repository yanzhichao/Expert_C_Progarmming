/*************************************************
  File name:     // 文件名
  Author:        Version:          Date:         //
  Description: 
  Function List: // 主要函数列表, 每条记录应包括函数名及功能简要说明
    1. ...
  History:       
    1. Date:
       Author:
       Modification:
    2. ...
*************************************************/
#include "queue.h"
#include "stdlib.h"

/*************************************************
  Function:       // 
  Description:    //创建一个队列
  Input:          // 无
  Output:         // 无
  Return:         //Queue 队列结构体
  Others:         // 无
*************************************************/
Queue creatQueue(void)
{
	Queue Q;
	Q.head=NULL;
	Q.tail=NULL;
	Q.len=0;
	return Q;
}
//销毁一个链表
/*************************************************
  Function:       // 
  Description:    //销毁一个队列
  Input:          //Q 队列结构体指针
                    releaseData  数据域释放函数指针
  Output:         //无
  Return:         //void
  Others:         // 无

*************************************************/
void destroryQueue(Queue* Q,void (*releaseData)(void *))
{
	ptrNode pnode=Q->head;
	ptrNode tempNode;
	
	while(pnode!=NULL)
	{
		tempNode=pnode->next;

		if(releaseData!=NULL)
		   releaseData(pnode->data);
		free(pnode);
		pnode=tempNode;
	}
	Q->head=NULL;
	Q->tail=NULL;
	Q->len=0;
}

//向队列加入一个元素
/*************************************************
  Function:       // 
  Description:    //向队列加入一个新元素
                    队列增加新元素规定只能加入到队列的尾部
					因此直接向尾部插入一个新节点即可
  Input:          //Q 队列指针
                    data  新元素数据域
  Output:         // 无
  Return:         //成功返回 1 否则返回0
  Others:         // 无

*************************************************/
int pushNodeToQueue(Queue* Q,void* data)
{
	ptrNode newNode=(ptrNode)malloc(sizeof(STNode));
	if(newNode==NULL)
		return 0;
	newNode->data=data;
	if(Q->head==NULL)
	{
		newNode->next=NULL;
		Q->head=newNode;
		Q->tail=newNode;
	}
	else
	{
	  Q->tail->next=newNode;
	  newNode->next=NULL;
	  Q->tail=newNode;
	}
}
//从队列获取一个元素
/*************************************************
  Function:       // 
  Description:    //获取一个队列中的元素
                    队列获取元素只允许在队列的头部获取
					并且获取后就将节点从队列中删除
					因此需要脸部，保存节点的数据，然后删除节点

  Input:          //Q 队列结构体指针
                  
  Output:         // 无
  Return:         //void
  Others:         // 无

*************************************************/

void* getDataFromQueue(Queue* Q)
{
	void* data;
	ptrNode tempNode;
	tempNode=Q->head;  //保存当前头节点
	if(tempNode==NULL)
		return (int*)(-1);

	Q->head=tempNode->next; //删除当前头节点
	data=tempNode->data;  //保存数据
	free(tempNode);  //释放当前头节点
	return data;   //返回数据
}


/*************************************************
  Function:       // 
  Description:    //获取队列的长度
  Input:          //Q 队列结构体指针
  Output:         // 无
  Return:         //队列的大小
  Others:         // 无

*************************************************/


int getSizeOfQueue(Queue* Q)
{
        return Q->len;
}
