/*************************************************
  File name:     // �ļ���
  Author:        Version:          Date:         //
  Description: 
  Function List: // ��Ҫ�����б�, ÿ����¼Ӧ���������������ܼ�Ҫ˵��
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
  Description:    //����һ������
  Input:          // ��
  Output:         // ��
  Return:         //Queue ���нṹ��
  Others:         // ��
*************************************************/
Queue creatQueue(void)
{
	Queue Q;
	Q.head=NULL;
	Q.tail=NULL;
	Q.len=0;
	return Q;
}
//����һ������
/*************************************************
  Function:       // 
  Description:    //����һ������
  Input:          //Q ���нṹ��ָ��
                    releaseData  �������ͷź���ָ��
  Output:         //��
  Return:         //void
  Others:         // ��

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

//����м���һ��Ԫ��
/*************************************************
  Function:       // 
  Description:    //����м���һ����Ԫ��
                    ����������Ԫ�ع涨ֻ�ܼ��뵽���е�β��
					���ֱ����β������һ���½ڵ㼴��
  Input:          //Q ����ָ��
                    data  ��Ԫ��������
  Output:         // ��
  Return:         //�ɹ����� 1 ���򷵻�0
  Others:         // ��

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
//�Ӷ��л�ȡһ��Ԫ��
/*************************************************
  Function:       // 
  Description:    //��ȡһ�������е�Ԫ��
                    ���л�ȡԪ��ֻ�����ڶ��е�ͷ����ȡ
					���һ�ȡ��ͽ��ڵ�Ӷ�����ɾ��
					�����Ҫ����������ڵ�����ݣ�Ȼ��ɾ���ڵ�

  Input:          //Q ���нṹ��ָ��
                  
  Output:         // ��
  Return:         //void
  Others:         // ��

*************************************************/

void* getDataFromQueue(Queue* Q)
{
	void* data;
	ptrNode tempNode;
	tempNode=Q->head;  //���浱ǰͷ�ڵ�
	if(tempNode==NULL)
		return (int*)(-1);

	Q->head=tempNode->next; //ɾ����ǰͷ�ڵ�
	data=tempNode->data;  //��������
	free(tempNode);  //�ͷŵ�ǰͷ�ڵ�
	return data;   //��������
}


/*************************************************
  Function:       // 
  Description:    //��ȡ���еĳ���
  Input:          //Q ���нṹ��ָ��
  Output:         // ��
  Return:         //���еĴ�С
  Others:         // ��

*************************************************/


int getSizeOfQueue(Queue* Q)
{
        return Q->len;
}
