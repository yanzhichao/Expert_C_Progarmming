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
	for(int i=1;i<=M;i++) //β�巨���������������ֵ
	{
		STNODE* newNODE=(STNODE*)malloc(sizeof(STNODE));
		newNODE->data=rand()%100;
		Temp->next=newNODE;
		newNODE->next=NULL;
		Temp=newNODE;
	}
	//��ӡԭ��������
	for(STNODE* temp=Head->next;temp!=NULL;temp=temp->next)
		printf("%d->",temp->data);
	printf("\n");

	STNODE* Last=Head;
	while(Last->next!=NULL)   //�����нڵ㶼��ɾ����ô����
	{
		STNODE* preMaxNode;   //�洢���ֵ��ǰһ���ڵ�
		preMaxNode=Last;      //Ĭ�����ֵΪ��һ���ڵ�
		STNODE* preNode=Last;      //��ǰ���ʽڵ��ǰһ���ڵ��¼
		for(STNODE* temp=Last;temp!=NULL; preNode=temp,temp=temp->next) //��ͷ���㿪ʼѭ������
		{                                                               //ÿһ�ζ���¼ǰһ���ڵ�
			
			if(preMaxNode->next->data<=temp->data)             //�жϵ�ǰ����Ƿ����֪���ֵ��
			{ 
				preMaxNode=preNode;                 //���ǣ���������ֵ�ڵ��ǰһ���ڵ�
			}                                                                                     
		}
		STNODE* maxNode=preMaxNode->next;       //������һ���ڵ㣬�ɿ����ֵ�ڵ���뵽��ǰ��               
		preMaxNode->next=maxNode->next;                

		maxNode->next=Last->next;   //�����ֵ�Ľ����뵽��ǰ��
		Last->next=maxNode;          
		Last=maxNode;              //����һ���ڵ㿪ʼ��������ʣ�½ڵ㡣
	}
    
	for(STNODE* temp=Head->next;temp!=NULL;temp=temp->next)
		printf("%d->",temp->data);
	getchar();


}
