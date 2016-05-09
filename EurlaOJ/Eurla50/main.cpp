#include "iostream"
#include <math.h>
#include "stdlib.h"
using namespace std;

//链表节点结构体
typedef struct tagNode{
	int num;                //质数
	struct tagNode* next;
}stNode,*pStNode;
//链表结构体
typedef struct tagList{
	pStNode head,tail;  //链表头指针和尾指针
	int len;            //链表中的节点总数
}stList;

//质数表从2开始
typedef struct tagPrime{
	int* primeArray;  //存储质数的数组
	int primesize;   //个数
}stPrime,*pstPrime;

//单链表初始化
void InitList(stList* L)
{
	L->head=NULL;
	L->tail=NULL;
	L->len=0;
};

//构建单链表
stList creatList()
{
	stList L;
	InitList(&L);
	return L;
}

//释放单链表  
void destroryList(stList *L)
{
	pStNode pnode=L->head;
	pStNode tempnode;
	while(pnode!=NULL)    //逐个释放申请的节点
	{
		tempnode=pnode->next;
		free(pnode);
		pnode=tempnode;
	}
}

//将一个新节点放入链表的末尾
void pushEndNode(stList *L,int num)  //尾插法
{
   pStNode newNode=(pStNode)malloc(sizeof(stNode));  //申请新节点
   newNode->num=num;                                 //给新节点赋值
   if(L->head==NULL)                                 //如果链表为空则把新节点地址  
   {                                                 //同时赋值给头指针和尾指针
	   L->head=newNode;                              
	   newNode->next=NULL;
	   L->tail=newNode;
   }
   else                                             //如果链表有则插入链表尾部
   {
	   L->tail->next=newNode;
	   newNode->next=NULL;
	   L->tail=newNode;
   }
   L->len++;
}
//将链表转化为数组
int* conventListToArrary(stList *L)               
{
	int* parray=(int *)malloc(L->len*sizeof(int));
	int index=0;
	pStNode pnode=L->head;
	while(pnode!=NULL)        //从头到尾访问
	{
		//cout<<pnode->num<<" ";
		parray[index++]=pnode->num;    
		pnode=pnode->next;
		
	}
    return parray;                  //返回数组的指针
}

//建立质数数组
//stprime 为质数结构体
//nlimit  是连续质数相加总和不超过nlimit
//方法：1.寻找质数方法是 n为质数， 那么n不能被小于根号n的所有
//质数整除。
//      2.为了节约空间将所有质数从2开始一次存入链表中，最后在转换
//数组。
void creatPrimeToArray(stPrime* stprime,int nlimit)
{
	int sqrtn; //根号next
	int top=0;
	int next=3;
	top=0;
	stList prList;
	prList=creatList();      //创建一个列表
	pushEndNode(&prList,2);  //将质数2加入链表
	pStNode pnode=prList.head;
	int temp=2;
	unsigned int sum=2;
	while(1)
	{
		sqrtn=sqrt((double)next);
        pnode=prList.head;    //每次都从头遍历，即从2
		while(pnode->num<=sqrtn)
		{
			if(next%pnode->num==0) break;  //如果被整除那么跳出
			pnode=pnode->next;
		}
		if(pnode->num>sqrtn) {   //如果pnode->num>sqrtn 说明next新的为质数
			sum=sum+next;     //判断加入新质后的和是否超限
			if(sum>nlimit)   //如果超限 寻找完毕。
				break;
			 pushEndNode(&prList,next);//如果没有超限 那么加入新的质数 
			}
		next+=2;     //判断下一个是否为质数  +2是因为所有偶数都是非质数 
	}
	int* pPrime=conventListToArrary(&prList); //转换链表尾数组
	stprime->primeArray=pPrime;     //存入质数结构体
	stprime->primesize=prList.len;  

	destroryList(&prList);   //释放链表
}

//释放质数结构体
void destroryPrimeToArray(stPrime* stprime)
{
	if(stprime&&stprime->primeArray!=NULL)
		 free(stprime->primeArray);  //直接释放数组的指针
}

//判断一个数是否为质数
//判断方法为  判断n是否不能被小于根号n的所有数整除
int isPrime(int n)
{
	int nsqrt=sqrt((double)n);
	int i=0;
	for(i=2;i<=nsqrt;i++)
	{
		if(n%i==0) return false;
	}
	return true;
}

//求数组parray中位置down到up的所有数的和  包括up
unsigned int sumArrayBetwen(int down,int up,int *parray)
{
	unsigned int sum=0;
	for(int i=down;i<=up;i++)
		   {
			   sum+=parray[i];
	       } 
	return sum;
}

int getConsecutivePrimes(int n)
{
	stPrime stprime;
	int top=0;
	int* primes=0;
	creatPrimeToArray(&stprime,n);  //以n为限制，创建质数数组
	primes=stprime.primeArray;     
	top=stprime.primesize;

	//循环查找 0->top ;0->(top-1),1->top;0->(top-2),1->(top-1),2->top;....是否超过n
	//如果超过那么被找到
	int isfind=0;
	unsigned int sum=0;
	for(int j=top-1;j>0;j--)
	{
		for(int i=0;i<top-j;i++)
		{
			sum=sumArrayBetwen(i,i+j,primes);
			if(isPrime(sum)&&sum<n)
			{
				//cout<<"sucessful="<<sum<<endl;
				isfind=1;
				break;
			}			    
		}	
		if (isfind)
			break;
	}
	destroryPrimeToArray(&stprime);
	return sum;
}
int main()
{
	int sum=0;
	sum=getConsecutivePrimes(1000000);
	cout<<"sum="<<sum;
	getchar();
}


void main2()
{
	int* primes=0;
	int top=0;
	stPrime stprime;
	creatPrimeToArray(&stprime,4000);
	primes=stprime.primeArray;
	top=stprime.primesize;
	//primes=(int*)malloc(100000*sizeof(int));
	//	top=makePrime(primes,3943);
	cout<<"top="<<top<<endl;
	int isfind=0;
	for(int j=top-1;j>0;j--)
	{
		for(int i=0;i<top-j;i++)
		{
			int sum=sumArrayBetwen(i,i+j,primes);
			if(isPrime(sum)&&sum<1000000)
			{
				cout<<"sucessful="<<sum<<endl;
				isfind=1;
				break;
			}			    
		}	
		if (isfind)
			break;
	}
	destroryPrimeToArray(&stprime);
	getchar();
}


//生成从2开始的N个质数，方式是如果是一个数a是质数，那么a不会被比根号a小的所有质数整除。
int  makePrime(int *primes,int nlimit)
{
	int j,i=1,sqrtn;
	int top=0;
	int next=3;
	primes[0]=2;
	top=0;
	while(1)
	{
		j=0;
		sqrtn=sqrt((double)next);
		while(primes[j]<=sqrtn)
		{
			if(next%primes[j]==0) break;
			j++;
		}
		if(primes[j]>sqrtn) {
			if(next>nlimit) break;
			primes[i]=next;
			top=i;
			i++;}
		next+=2;     
	}
	return top;
}