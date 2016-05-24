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

//测试接口
int main()
{
	int sum=0;
	cout<<"通用类型测试"<<endl;
	STList IntList=creatList();  //创建一个链表

	//给链表增加节点
	//方式1 通用的数据域分配方式
	//直接malloc节点的数据域，此时需要提供
	//节点数据域新建函数，来创建数据域
	//和节点数据域释放函数来用于节点数据域的释放
	for(int i=0;i<10;i++)
	{
	 StudentID* newNode=newData('A'+i,i);  //新建节点数据域

	 pushNodeToEnd(&IntList,newNode);   //将节点接入链表
	}

	//打印链表
	STNode* tempNode=IntList.head;
	while(tempNode!=NULL)
	{
		printNode((StudentID*)tempNode->data);
		cout<<"->";
		tempNode=tempNode->next;
	}
	cout<<endl;
	//进行一些链表的其他操作
	StudentID* insertOne=newData('Z',15);  //插入一个新节点
    insertNode(&IntList,5,insertOne);

	deletNode(&IntList,3);   //删除一个节点

	//打印操作后的链表
	tempNode=IntList.head;
	while(tempNode!=NULL)
	{
		printNode((StudentID*)tempNode->data);
		cout<<"->";
		tempNode=tempNode->next;
	}
	cout<<endl;

	reverseList(&IntList);  //反转链表
	//通过索引俩访问链表,打印被反转后的链表
	for(int i=1;i<=IntList.len;i++)
	{
		printNode((StudentID*)getNode(&IntList,i)->data);
		cout<<"->";
	}

	destroryList(&IntList,relaseData); //销毁列表时，需要传入数据域释放函数指针


	//对于简单类型的数据域 如int类型，可以用强制转换直接
	//赋值，不必提供额外的用户函数
	cout<<endl;
	cout<<"简单类型测试"<<endl;
	for(int i=0;i<10;i++)
	{
		pushNodeToFront(&IntList,(int*)i);  //直接强制转换，把i当成指针用
	}
	 tempNode=IntList.head;
	while(tempNode!=NULL)
	{
		cout<<(int)(tempNode->data)<<"->"; //访问时，直接转换为int类型即可
		tempNode=tempNode->next;
	}
	cout<<endl;
	insertNode(&IntList,10,(int*)51);

	deletNode(&IntList,3);
    tempNode=IntList.head;
	while(tempNode!=NULL)
	{
        
		cout<<(int)(tempNode->data)<<"->"; //访问时，直接转换为int类型即可
 		tempNode=tempNode->next;
	}

	cout<<endl;

	reverseList(&IntList);
	for(int i=1;i<=IntList.len;i++)
	{
	    cout<<(int)(getNode(&IntList,i)->data)<<"->";
	}

    destroryList(&IntList,NULL); //清理链表时，不需要传入数据释放函数
	cout<<endl;
	cout<<"isEmpty="<<isEmpty(&IntList)<<endl;
	getchar();
}



