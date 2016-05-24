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

#include "linker.h"
#include "stdlib.h"

/*************************************************
  Function:       // 
  Description:    //初始化新建的链表
  Input:          //L 链表结构体指针
  Output:         // 无
  Return:         //void
  Others:         // 无

*************************************************/
static void initList(STList* L)
{
    L->head=NULL;  
	L->tail=NULL;
	L->len	=0;

}


/*************************************************
  Function:       // 
  Description:    ////创建一个链表，并初始化，返回一个链表结构体
  Input:          //无
  Output:         // 无
  Return:         //新建的链表结构体
  Others:         // 无

*************************************************/
STList creatList(void)
{
	STList L;
	initList(&L);
	return L;
}

/*************************************************
  Function:     
  Description:   销毁一个链表
  Input:         L： 链表结构体
                 releaseData： 用户自定义的释放内存函数，如果不需要则传入NULL
  Output:        无
  Return:        无
  Others:        无
*************************************************/

void destroryList(STList *const L,void (*releaseData)(void *))
{
	ptrNode pnode=L->head;
	ptrNode tempNode;

	while(pnode!=NULL)
	{
		tempNode=pnode->next;

		//用户数据释放
		if(releaseData!=NULL)
	    	releaseData(pnode->data);

		free(pnode);
		pnode=tempNode;
	}
	L->head=NULL;
	L->tail=NULL;
	L->len=0;  //节点赋值为0
}

/*************************************************
  Function:     
  Description:   向链表的尾部插入一个值
  Input:         L： 链表结构体
                 data 插入值的指针
  Output:        无
  Return:        成功返回1 否则返回0
  Others:        无
*************************************************/
int pushNodeToEnd(STList*L,void* data)
{
	ptrNode newNode=(ptrNode)malloc(sizeof(STNode));
	if(!newNode)
		return 0;

	newNode->data=data;
	//插入操作
	if(L->head==NULL)  //如果是第一个节点
	{   
		L->head=newNode;    //头指针指向新节点
	    newNode->next=NULL;  
		L->tail=newNode;    //尾指针也指向新节点
	} 
	else             //如果不是第一个节点
	{
	  L->tail->next=newNode;  //在尾指针后面插入新节点
	  newNode->next=NULL;    
	  L->tail=newNode;       //尾指针后移指向新节点
	}
	L->len++;            //节点数加1
	return 1;
}

/*************************************************
  Function:     
  Description:   向链表的头部插入一个节点
  Input:         L： 链表结构体
                 data 插入值的指针
  Output:        无
  Return:        成功返回1 否则返回0
  Others:        无
*************************************************/
int pushNodeToFront(STList* L,void* data)
{
	ptrNode newNode=(ptrNode)malloc(sizeof(STNode));
	if(!newNode)
		return 0;
	newNode->data=data;

	if(L->head==NULL)  //如果为第一个节点
	{
      L->head=newNode;    //头节点指向新节点
	  newNode->next=NULL;
	  L->tail=newNode;    //尾结点也直线新节点
	}
	else   //如果不是第一个节点	
	{
		newNode->next=L->head; //新节点指向第一个节点  
		L->head=newNode;     //头节点变为新节点
	}
	L->len++;       //节点个数加1
	return 1;
}

/*************************************************
  Function:     
  Description:   向链表的第index位置的后面插入一个节点
  Input:         L： 链表结构体
                 index  节点索引
                 data 插入值的指针
  Output:        无
  Return:        成功返回1 否则返回0
  Others:        无
*************************************************/
int insertNode(STList* L,int index,void *data)
{
	if(index<0||index>L->len)   //如果index超过限制
		return 0;               //返回
	if(0==index)                //如果插入到第一个节点前面，那么就是插入到列表头部
		pushNodeToFront(L,data);
	else                       //否则插入到第一个
	{
	   //先寻找到第Index个节点
		ptrNode tempNode=L->head;
		while(--index)  //移动index次
		{
			tempNode=tempNode->next;
		}

		//插入新的节点
		ptrNode newNode=(ptrNode)malloc(sizeof(STNode));
		newNode->data=data;
		newNode->next=tempNode->next;  //插入节点到第Index个节点的之后
		tempNode->next=newNode;
		L->len++;
	}
	return 1;
}
/*************************************************
  Function:     
  Description:   删除第index个节点
  Input:         L： 链表结构体
                 index  节点索引
  Output:        无
  Return:        成功返回1 否则返回0
  Others:        无
*************************************************/
int deletNode(STList* L,int index)
{
	if(index<0||L->len<1)   //如果index超过限制
		return 0;           //那么返回


	ptrNode freeNode;           
	ptrNode tempNode=L->head;

	if(index==1)   //如果是第一个节点
	{
        freeNode=tempNode;      //保存第一个节点用于释放
		L->head=tempNode->next; //头指针指向第二个节点
		free(freeNode);        //释放节点
		L->len--;
	}
	else             //否则
	{ 
		//寻找到第index节点的前一个节点
		index--;          
		while(--index)
		{
			tempNode=tempNode->next;
		}

		//删除第index个节点
		freeNode=tempNode->next;
		tempNode->next=freeNode->next;
		free(freeNode);
		L->len--;
	}
	return 1;
}



/*************************************************
  Function:     
  Description:   获得第index个节点
  Input:         L： 链表结构体
                 data 插入值的指针
  Output:        无
  Return:        返回节点指针
  Others:        无
*************************************************/
ptrNode getNode(STList* L,int index)
{
	if(index<1||index>L->len)
		return NULL;

	ptrNode tempNode=L->head;
	while(--index)
		tempNode=tempNode->next;
	return tempNode;
}

/*************************************************
  Function:     
  Description:   判断链表是否为空
  Input:         L： 链表结构体
               
  Output:        无
  Return:        成功返回1 否则返回0
  Others:        无
*************************************************/
int isEmpty(STList* L)
{
	return (L->len? 1:0);
}

/*************************************************
  Function:     
  Description:   统计链表的大小，即节点个数
  Input:         L： 链表结构体
              
  Output:        无
  Return:        节点的个数
  Others:        无
*************************************************/
int getSizeofList(STList* L)
{
	return L->len;
}

/*************************************************
  Function:     
  Description:   反转链表
  Input:         L： 链表结构体
  Output:        无
  Return:        成功返回1 否则返回0 
  Others:        无
*************************************************/
int reverseList(STList* L)
{
	ptrNode reversNode=NULL;
	ptrNode visitNode=L->head;
	ptrNode LastNode=L->head;
	while(visitNode!=NULL)
	{
		LastNode=LastNode->next;
		visitNode->next=reversNode;
		reversNode=visitNode;
		visitNode=LastNode;
	}
	L->tail=L->head;
	L->head=reversNode;
	return 1;
}