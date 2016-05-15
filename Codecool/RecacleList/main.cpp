
#include "stdlib.h"
#include "string"
#include "iostream"
using namespace std;

typedef struct tagNODE{      //�����ڵ�
	int data;
	struct tagNODE* next;
}STNODE;

int main()
{
	int N=9;
	int M=5;
	STNODE* Temp;
	STNODE* Head;

	//����ѭ������
	Head=(STNODE*)malloc(sizeof(STNODE));   //ͷ�ڵ�
	Head->data=1; //ͷ�ڵ�ֵΪ1 
	Temp=Head;  

	for(int i=2;i<=N;i++)  //���˽��������ڵ�  β�巨
	{
		STNODE* newNODE=(STNODE*)malloc(sizeof(STNODE));//�½��
		newNODE->data=i;      //��ֵ
		newNODE->next=Head;   //�½ڵ� ����ǰ���һ���ڵ�ָ��ͷ�ڵ㹹��ѭ������
		Temp->next=newNODE;  //��һ�ڵ������½ڵ�
		Temp=newNODE;        //Temp����Ϊ���һ���ڵ� �������� 
	}
	//ѭ�����������

	STNODE* Visit=Head;    //����һ����������ָ�� ��ͷ�ڵ㿪ʼ���� 
	while(1)
	{
		for(int i=1;i<M-1;i++)    //����M��
			Visit=Visit->next;

		printf("%d",Visit->next->data); //�����̭��
		Visit->next=Visit->next->next; //ɾ��Visit��������̭�ڵ�
		Visit=Visit->next;             //�ӵ�ǰ������һ���ڵ㿪ʼ����

		if(Visit->data==Visit->next->data)  //�������� ˵��ѭ��������ֻ��һ���ڵ�
			break;                        //����쵼�˲���
	}
	printf("Lead is %d\n",Visit->data);  
	getchar();
}