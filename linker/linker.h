#ifndef _LINKER_
#define _LINKER_
//通用链表节点定义
typedef struct tagnode{
    void* data;            //数据域指针，void类型指针可以指向任何数据类型           
	struct tagnode* next; 
}STNode,*ptrNode;


//通用链表结构体
typedef struct tagList{        
	ptrNode head;   //链表头指针	
	ptrNode tail;   //链表尾指针
	int len;        //链表元素个数
}STList;

//创建一个链表，并初始化，返回一个链表结构体
STList creatList(void);

//销毁一个链表，并根据用户提供的释放函数，释放用户数据
void destroryList(STList*const L,void (*releaseData)(void *));

//新建一个节点加入到链表的尾部，成功返回1，否则0
int pushNodeToEnd(STList*L,void* data);
////新建一个节点加入到链表的头部，成功返回1，否则0
int pushNodeToFront(STList* L,void* data);

//在index位置插入一个节点
int insertNode(STList* L,int index,void *data);

//删除index位置的一个节点
int deletNode(STList* L,int index);

//获取index位置的一个节点，成功返回节点指针，否则返回NULL
ptrNode getNode(STList* L,int index);

//判断链表是否为空，空返回0 否则返回1
int isEmpty(STList* L);
//获取链表的大小，即有几个节点
int getSizeofList(STList* L);
//反转链表，成功返回1，否则返回0
int reverseList(STList* L);
#endif
