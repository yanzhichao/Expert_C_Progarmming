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
	for(int i=1;i<=M;i++) //β�巨������������˳��ֵ
	{
		STNODE* newNODE=(STNODE*)malloc(sizeof(STNODE));
		newNODE->data=i;
		Temp->next=newNODE;
		newNODE->next=NULL;
		Temp=newNODE;
	}
	//��ӡԭ��������
	for(STNODE* temp=Head->next;temp!=NULL;temp=temp->next)
		printf("%d->",temp->data);
	printf("\n");
	//���з�ת�� 
	//Ҫ���з�ת���Ҫ������ָ��
	STNODE* Revese=NULL;   //�Ѿ���ת������
    STNODE* Visit=Head->next;//��ǰ��Ҫ��ת�Ľڵ�
	STNODE* Last=Head->next; //��û�з�ת������
    
	while(Visit!=NULL)    //��ǰ��Ҫ��ת��Ϊ�� ��ô����
	{  
        Last=Last->next;  //λ��ת�ڵ����һλ

		Visit->next=Revese; //����ǰ�����뵽�Ѿ���ת������ͷ��
		Revese=Visit;     //�Ѿ���ת��ͷ����ɵ�ǰ���
		Visit=Last;	      //��ǰ������Ϊ��δ��ת�Ľڵ㣬ѭ��������ת
	}
	STNODE* newHead=(STNODE *)malloc(sizeof(STNODE)); //����һ���µ�ͷָ��ָ��ת������
	newHead->next=Revese;

	//��ӡ��ת������
	for(STNODE* temp=newHead->next;temp!=NULL;temp=temp->next)
		printf("%d->",temp->data);
} 

