#include "iostream"
#include <math.h>
#include "stdlib.h"
#include "linker.h"
using namespace std;
typedef struct tagStudentID{
	char name;
	int ID;
}StudentID;

StudentID* newData(char name,int ID)
{
	StudentID* newNode=(StudentID*)malloc(sizeof(StudentID));
	if(newNode==NULL)
		return NULL;

	newNode->ID=ID;
	newNode->name=name;
	return newNode;

}

void relaseData(void* data)
{
	free((int*)data);
}

int printNode(StudentID* node)
{
	if(node==NULL)
		return 0;
	printf("(%c,%d)",node->name,node->ID);
	return 1;
}

//���Խӿ�
int main()
{
	int sum=0;
	cout<<"ͨ�����Ͳ���"<<endl;
	STList IntList=creatList();  //����һ������

	//���������ӽڵ�
	//��ʽ1 ͨ�õ���������䷽ʽ
	//ֱ��malloc�ڵ�������򣬴�ʱ��Ҫ�ṩ
	//�ڵ��������½�������������������
	//�ͽڵ��������ͷź��������ڽڵ���������ͷ�
	for(int i=0;i<10;i++)
	{
	 StudentID* newNode=newData('A'+i,i);  //�½��ڵ�������

	 pushNodeToEnd(&IntList,newNode);   //���ڵ��������
	}

	//��ӡ����
	STNode* tempNode=IntList.head;
	while(tempNode!=NULL)
	{
		printNode((StudentID*)tempNode->data);
		cout<<"->";
		tempNode=tempNode->next;
	}
	cout<<endl;
	//����һЩ�������������
	StudentID* insertOne=newData('Z',15);  //����һ���½ڵ�
    insertNode(&IntList,5,insertOne);

	deletNode(&IntList,3);   //ɾ��һ���ڵ�

	//��ӡ�����������
	tempNode=IntList.head;
	while(tempNode!=NULL)
	{
		printNode((StudentID*)tempNode->data);
		cout<<"->";
		tempNode=tempNode->next;
	}
	cout<<endl;

	reverseList(&IntList);  //��ת����
	//ͨ����������������,��ӡ����ת�������
	for(int i=1;i<=IntList.len;i++)
	{
		printNode((StudentID*)getNode(&IntList,i)->data);
		cout<<"->";
	}

	destroryList(&IntList,relaseData); //�����б�ʱ����Ҫ�����������ͷź���ָ��


	//���ڼ����͵������� ��int���ͣ�������ǿ��ת��ֱ��
	//��ֵ�������ṩ������û�����
	cout<<endl;
	cout<<"�����Ͳ���"<<endl;
	for(int i=0;i<10;i++)
	{
		pushNodeToFront(&IntList,(int*)i);  //ֱ��ǿ��ת������i����ָ����
	}
	 tempNode=IntList.head;
	while(tempNode!=NULL)
	{
		cout<<(int)(tempNode->data)<<"->"; //����ʱ��ֱ��ת��Ϊint���ͼ���
		tempNode=tempNode->next;
	}
	cout<<endl;
	insertNode(&IntList,10,(int*)51);

	deletNode(&IntList,3);
    tempNode=IntList.head;
	while(tempNode!=NULL)
	{
        
		cout<<(int)(tempNode->data)<<"->"; //����ʱ��ֱ��ת��Ϊint���ͼ���
 		tempNode=tempNode->next;
	}

	cout<<endl;

	reverseList(&IntList);
	for(int i=1;i<=IntList.len;i++)
	{
	    cout<<(int)(getNode(&IntList,i)->data)<<"->";
	}

    destroryList(&IntList,NULL); //��������ʱ������Ҫ���������ͷź���
	cout<<endl;
	cout<<"isEmpty="<<isEmpty(&IntList)<<endl;
	getchar();
}



