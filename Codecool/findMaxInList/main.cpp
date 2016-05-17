#include "stdlib.h"
#include "stdio.h"
#include "time.h"
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


	while(Head->next!=NULL)   //�����нڵ㶼��ɾ����ô����
	{
		STNODE* preMaxNode;   //�洢���ֵ��ǰһ���ڵ㣬����ɾ�����ֵ�ڵ�
		preMaxNode=Head;      //Ĭ�����ֵΪ��һ���ڵ�
		STNODE* preNode;      //��ǰ���ʽڵ��ǰһ���ڵ��¼
		for(STNODE* temp=Head;temp!=NULL;preNode=temp, temp=temp->next) //��ͷ���㿪ʼѭ������
		{                                                               //ÿһ�ζ���¼ǰһ���ڵ�
			if(preMaxNode->next->data<=temp->data)             //�жϵ�ǰ����Ƿ����֪���ֵ��
			{ 
				preMaxNode=preNode;                 //���ǣ���������ֵ�ڵ��ǰһ���ڵ�
  			}                                                                                     
		}
		printf("%d->",preMaxNode->next->data);  //����ڵ�ֵ

		//ɾ����ǰ���ֵ�ڵ�
		STNODE* maxNode=preMaxNode->next;                      
		preMaxNode->next=maxNode->next;
		free(maxNode);
	}
			
			
getchar();


}