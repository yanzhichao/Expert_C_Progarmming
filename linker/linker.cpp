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

#include "linker.h"
#include "stdlib.h"

/*************************************************
  Function:       // 
  Description:    //��ʼ���½�������
  Input:          //L ����ṹ��ָ��
  Output:         // ��
  Return:         //void
  Others:         // ��

*************************************************/
static void initList(STList* L)
{
    L->head=NULL;  
	L->tail=NULL;
	L->len	=0;

}


/*************************************************
  Function:       // 
  Description:    ////����һ����������ʼ��������һ������ṹ��
  Input:          //��
  Output:         // ��
  Return:         //�½�������ṹ��
  Others:         // ��

*************************************************/
STList creatList(void)
{
	STList L;
	initList(&L);
	return L;
}

/*************************************************
  Function:     
  Description:   ����һ������
  Input:         L�� ����ṹ��
                 releaseData�� �û��Զ�����ͷ��ڴ溯�����������Ҫ����NULL
  Output:        ��
  Return:        ��
  Others:        ��
*************************************************/

void destroryList(STList *const L,void (*releaseData)(void *))
{
	ptrNode pnode=L->head;
	ptrNode tempNode;

	while(pnode!=NULL)
	{
		tempNode=pnode->next;

		//�û������ͷ�
		if(releaseData!=NULL)
	    	releaseData(pnode->data);

		free(pnode);
		pnode=tempNode;
	}
	L->head=NULL;
	L->tail=NULL;
	L->len=0;  //�ڵ㸳ֵΪ0
}

/*************************************************
  Function:     
  Description:   �������β������һ��ֵ
  Input:         L�� ����ṹ��
                 data ����ֵ��ָ��
  Output:        ��
  Return:        �ɹ�����1 ���򷵻�0
  Others:        ��
*************************************************/
int pushNodeToEnd(STList*L,void* data)
{
	ptrNode newNode=(ptrNode)malloc(sizeof(STNode));
	if(!newNode)
		return 0;

	newNode->data=data;
	//�������
	if(L->head==NULL)  //����ǵ�һ���ڵ�
	{   
		L->head=newNode;    //ͷָ��ָ���½ڵ�
	    newNode->next=NULL;  
		L->tail=newNode;    //βָ��Ҳָ���½ڵ�
	} 
	else             //������ǵ�һ���ڵ�
	{
	  L->tail->next=newNode;  //��βָ���������½ڵ�
	  newNode->next=NULL;    
	  L->tail=newNode;       //βָ�����ָ���½ڵ�
	}
	L->len++;            //�ڵ�����1
	return 1;
}

/*************************************************
  Function:     
  Description:   �������ͷ������һ���ڵ�
  Input:         L�� ����ṹ��
                 data ����ֵ��ָ��
  Output:        ��
  Return:        �ɹ�����1 ���򷵻�0
  Others:        ��
*************************************************/
int pushNodeToFront(STList* L,void* data)
{
	ptrNode newNode=(ptrNode)malloc(sizeof(STNode));
	if(!newNode)
		return 0;
	newNode->data=data;

	if(L->head==NULL)  //���Ϊ��һ���ڵ�
	{
      L->head=newNode;    //ͷ�ڵ�ָ���½ڵ�
	  newNode->next=NULL;
	  L->tail=newNode;    //β���Ҳֱ���½ڵ�
	}
	else   //������ǵ�һ���ڵ�	
	{
		newNode->next=L->head; //�½ڵ�ָ���һ���ڵ�  
		L->head=newNode;     //ͷ�ڵ��Ϊ�½ڵ�
	}
	L->len++;       //�ڵ������1
	return 1;
}

/*************************************************
  Function:     
  Description:   ������ĵ�indexλ�õĺ������һ���ڵ�
  Input:         L�� ����ṹ��
                 index  �ڵ�����
                 data ����ֵ��ָ��
  Output:        ��
  Return:        �ɹ�����1 ���򷵻�0
  Others:        ��
*************************************************/
int insertNode(STList* L,int index,void *data)
{
	if(index<0||index>L->len)   //���index��������
		return 0;               //����
	if(0==index)                //������뵽��һ���ڵ�ǰ�棬��ô���ǲ��뵽�б�ͷ��
		pushNodeToFront(L,data);
	else                       //������뵽��һ��
	{
	   //��Ѱ�ҵ���Index���ڵ�
		ptrNode tempNode=L->head;
		while(--index)  //�ƶ�index��
		{
			tempNode=tempNode->next;
		}

		//�����µĽڵ�
		ptrNode newNode=(ptrNode)malloc(sizeof(STNode));
		newNode->data=data;
		newNode->next=tempNode->next;  //����ڵ㵽��Index���ڵ��֮��
		tempNode->next=newNode;
		L->len++;
	}
	return 1;
}
/*************************************************
  Function:     
  Description:   ɾ����index���ڵ�
  Input:         L�� ����ṹ��
                 index  �ڵ�����
  Output:        ��
  Return:        �ɹ�����1 ���򷵻�0
  Others:        ��
*************************************************/
int deletNode(STList* L,int index)
{
	if(index<0||L->len<1)   //���index��������
		return 0;           //��ô����


	ptrNode freeNode;           
	ptrNode tempNode=L->head;

	if(index==1)   //����ǵ�һ���ڵ�
	{
        freeNode=tempNode;      //�����һ���ڵ������ͷ�
		L->head=tempNode->next; //ͷָ��ָ��ڶ����ڵ�
		free(freeNode);        //�ͷŽڵ�
		L->len--;
	}
	else             //����
	{ 
		//Ѱ�ҵ���index�ڵ��ǰһ���ڵ�
		index--;          
		while(--index)
		{
			tempNode=tempNode->next;
		}

		//ɾ����index���ڵ�
		freeNode=tempNode->next;
		tempNode->next=freeNode->next;
		free(freeNode);
		L->len--;
	}
	return 1;
}



/*************************************************
  Function:     
  Description:   ��õ�index���ڵ�
  Input:         L�� ����ṹ��
                 data ����ֵ��ָ��
  Output:        ��
  Return:        ���ؽڵ�ָ��
  Others:        ��
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
  Description:   �ж������Ƿ�Ϊ��
  Input:         L�� ����ṹ��
               
  Output:        ��
  Return:        �ɹ�����1 ���򷵻�0
  Others:        ��
*************************************************/
int isEmpty(STList* L)
{
	return (L->len? 1:0);
}

/*************************************************
  Function:     
  Description:   ͳ������Ĵ�С�����ڵ����
  Input:         L�� ����ṹ��
              
  Output:        ��
  Return:        �ڵ�ĸ���
  Others:        ��
*************************************************/
int getSizeofList(STList* L)
{
	return L->len;
}

/*************************************************
  Function:     
  Description:   ��ת����
  Input:         L�� ����ṹ��
  Output:        ��
  Return:        �ɹ�����1 ���򷵻�0 
  Others:        ��
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