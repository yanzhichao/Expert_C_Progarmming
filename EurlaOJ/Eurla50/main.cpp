#include "iostream"
#include <math.h>
#include "stdlib.h"
using namespace std;

//����ڵ�ṹ��
typedef struct tagNode{
	int num;                //����
	struct tagNode* next;
}stNode,*pStNode;
//����ṹ��
typedef struct tagList{
	pStNode head,tail;  //����ͷָ���βָ��
	int len;            //�����еĽڵ�����
}stList;

//�������2��ʼ
typedef struct tagPrime{
	int* primeArray;  //�洢����������
	int primesize;   //����
}stPrime,*pstPrime;

//�������ʼ��
void InitList(stList* L)
{
	L->head=NULL;
	L->tail=NULL;
	L->len=0;
};

//����������
stList creatList()
{
	stList L;
	InitList(&L);
	return L;
}

//�ͷŵ�����  
void destroryList(stList *L)
{
	pStNode pnode=L->head;
	pStNode tempnode;
	while(pnode!=NULL)    //����ͷ�����Ľڵ�
	{
		tempnode=pnode->next;
		free(pnode);
		pnode=tempnode;
	}
}

//��һ���½ڵ���������ĩβ
void pushEndNode(stList *L,int num)  //β�巨
{
   pStNode newNode=(pStNode)malloc(sizeof(stNode));  //�����½ڵ�
   newNode->num=num;                                 //���½ڵ㸳ֵ
   if(L->head==NULL)                                 //�������Ϊ������½ڵ��ַ  
   {                                                 //ͬʱ��ֵ��ͷָ���βָ��
	   L->head=newNode;                              
	   newNode->next=NULL;
	   L->tail=newNode;
   }
   else                                             //������������������β��
   {
	   L->tail->next=newNode;
	   newNode->next=NULL;
	   L->tail=newNode;
   }
   L->len++;
}
//������ת��Ϊ����
int* conventListToArrary(stList *L)               
{
	int* parray=(int *)malloc(L->len*sizeof(int));
	int index=0;
	pStNode pnode=L->head;
	while(pnode!=NULL)        //��ͷ��β����
	{
		//cout<<pnode->num<<" ";
		parray[index++]=pnode->num;    
		pnode=pnode->next;
		
	}
    return parray;                  //���������ָ��
}

//������������
//stprime Ϊ�����ṹ��
//nlimit  ��������������ܺͲ�����nlimit
//������1.Ѱ������������ nΪ������ ��ôn���ܱ�С�ڸ���n������
//����������
//      2.Ϊ�˽�Լ�ռ佫����������2��ʼһ�δ��������У������ת��
//���顣
void creatPrimeToArray(stPrime* stprime,int nlimit)
{
	int sqrtn; //����next
	int top=0;
	int next=3;
	top=0;
	stList prList;
	prList=creatList();      //����һ���б�
	pushEndNode(&prList,2);  //������2��������
	pStNode pnode=prList.head;
	int temp=2;
	unsigned int sum=2;
	while(1)
	{
		sqrtn=sqrt((double)next);
        pnode=prList.head;    //ÿ�ζ���ͷ����������2
		while(pnode->num<=sqrtn)
		{
			if(next%pnode->num==0) break;  //�����������ô����
			pnode=pnode->next;
		}
		if(pnode->num>sqrtn) {   //���pnode->num>sqrtn ˵��next�µ�Ϊ����
			sum=sum+next;     //�жϼ������ʺ�ĺ��Ƿ���
			if(sum>nlimit)   //������� Ѱ����ϡ�
				break;
			 pushEndNode(&prList,next);//���û�г��� ��ô�����µ����� 
			}
		next+=2;     //�ж���һ���Ƿ�Ϊ����  +2����Ϊ����ż�����Ƿ����� 
	}
	int* pPrime=conventListToArrary(&prList); //ת������β����
	stprime->primeArray=pPrime;     //���������ṹ��
	stprime->primesize=prList.len;  

	destroryList(&prList);   //�ͷ�����
}

//�ͷ������ṹ��
void destroryPrimeToArray(stPrime* stprime)
{
	if(stprime&&stprime->primeArray!=NULL)
		 free(stprime->primeArray);  //ֱ���ͷ������ָ��
}

//�ж�һ�����Ƿ�Ϊ����
//�жϷ���Ϊ  �ж�n�Ƿ��ܱ�С�ڸ���n������������
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

//������parray��λ��down��up���������ĺ�  ����up
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
	creatPrimeToArray(&stprime,n);  //��nΪ���ƣ�������������
	primes=stprime.primeArray;     
	top=stprime.primesize;

	//ѭ������ 0->top ;0->(top-1),1->top;0->(top-2),1->(top-1),2->top;....�Ƿ񳬹�n
	//���������ô���ҵ�
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


//���ɴ�2��ʼ��N����������ʽ�������һ����a����������ôa���ᱻ�ȸ���aС����������������
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