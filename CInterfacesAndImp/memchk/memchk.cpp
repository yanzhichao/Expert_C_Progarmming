#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#include "except.h"

#include "mem.h"

//������ʵ�ֵ���һ�����������ڴ������
//Ϊ��ʹ��malloc��������������ͬһ��ַ���Σ�ͨ���Ӳ��ͷ�������ڴ��������
//���ַ�ʽ���������ڴ��ͽ������list ͨ����list�Ĳ������Լ������ڴ档
//�ô����Ա�����󡣶�ȱ���������һ���������˺ܴ���ڴ棬��ô����ڴ潫
//�ڳ������֮ǰ���ٻᱻ�ͷš�
//��������ڴ����ʽ�ʺ������ڴ������С���������Ǻܴ�������
//��Ȼ���ַ�ʽ��Ӧ�ò����Ǻܺ�
//��������hash��������ÿ���û�������ڴ滹�Ƿǳ�������ġ�


const Except_T  Mem_Failed={"Allocation failed"};
Except_T Assert_Failed={"Assert failed"};
#define hash(p,t) (((unsigned long)(p)>>3)&(sizeof(t)/sizeof((t)[0])-1))
#define NDESCRIPTORS 512
#define NALLOC ((4096+sizeof(union align)-1)/(sizeof(union align)))*(sizeof(union align))

union align
{
	int i;
	long l;
	long *lp;
	void *p;
	void (*fp)(void);
	float f;
	double d;
	long double ld;
};


static struct descriptor{
	struct descriptor *free;
	struct descriptor *link;
	const void *ptr;
	long size;
	const char *file;
	int line;
	
	
}* htab[2048];
//����һ��descriptor �ṹ�� �����ĵ�ַ��ֵ�����ĵ�һ������ free 
//�˴�freelist��һ��ѭ���������ʱ���Լ�ָ���Լ�û���κ����������ڴ��
static struct descriptor freelist={&freelist};  


static struct descriptor *find(const void *ptr){
	struct descriptor *bp=htab[hash(ptr,htab)];

	while(bp&&bp->ptr!=ptr)
    bp=bp->link;
	return bp;
}

void Mem_free(void* ptr,const char *file,int line)
{
	if(ptr)
	{
		struct descriptor *bp;
		if(((unsigned long)ptr)%(sizeof(union align))!=0||(bp=find(ptr))==NULL||bp->free)
			Except_raise(&Assert_Failed,file,line);

		bp->free=freelist.free;
		freelist.free=bp;
	}

}



static struct descriptor *dalloc(void *ptr,long size,const char* file,int line)
{
    static struct descriptor *avail;
	static int nleft;

	if(nleft<=0)
	{
		avail=(struct descriptor *)malloc(NDESCRIPTORS*sizeof(*avail));
		if(avail==NULL)
			return NULL;
		nleft=NDESCRIPTORS;

	}

	avail->ptr=ptr;
	avail->size=size;
	avail->file=file;
	avail->free=avail->link=NULL;
	nleft--;
	return avail++;

}

void *Mem_alloc(long nbytes,const char *file,int line)
{
	struct descriptor *bp;
	void *ptr;

	assert(nbytes>0);
	//��nbytes���ֽڶ������䵽�����ֽڣ�����ռ��˷�
	nbytes=((nbytes+sizeof(union align)-1)/(sizeof(union align)))*(sizeof(union align));
	//�ӿ��п���׵�ַ����һ�鿪ʼѰ�Һ��ʵĿռ䣬freelist��һ��ѭ������������ν�Ŀ��п�
	//�������������ǿ��еģ���ʵ�����е�ǰ�Ѿ�������Ŀ飬ÿһ�鶼�����٣�NALLOC���󡣾�����ηֱ��
	//�����е��ǿ��еģ����еĿ����Ѿ���������
	for(bp=freelist.free;bp;bp=bp->free)
	{
		if(bp->size>nbytes) //����ҵ����ʵĿ��п�
		{
			bp->size-=nbytes;  
			ptr=(char *)bp->ptr+bp->size;  //�õ�����ռ���׵�ַ
			if((bp=dalloc(ptr,nbytes,file,line))!=NULL)  //����һ���洢��ptr�Ľṹ��bp
			{
				unsigned h=hash(ptr,htab);               //Ȼ������ṹ����뵽hash����
				bp->link=htab[h];                        //��������ڴ��Ѿ���ռ���ˡ�
				htab[h]=bp;
				return ptr;
			}
			else
			{
				if(file==NULL)
					RAISE(Mem_Failed);
				else
					Except_raise(&Mem_Failed,file,line);
			}
		}
		if(bp==&freelist)  //û�к��ʵĿ��п飬��ô����һ���¿�
		{
			struct descriptor *newptr;
			if((ptr=malloc(nbytes+NALLOC))==NULL     //�¿��С�ɹ̶����nbytes��ͬ��������ζ�����еĿ鶼���д�С�ϵ�һЩ����
				||(newptr=dalloc(ptr,nbytes+NALLOC,__FILE__,__LINE__))==NULL)
			{

	            if(file==NULL)
					RAISE(Mem_Failed);
				else
					Except_raise(&Mem_Failed,file,line);
			}

			newptr->free=freelist.free;
			freelist.free=newptr;
		}

	}
	assert(0);
	return NULL;
}

void *Mem_resize(void *ptr,long nbytes,const char *file,int line)
{
	struct descriptor *bp;
	void *newptr;
	assert(ptr);
	assert(nbytes>0);
	if(((unsigned long)ptr)%(sizeof(union align))!=0||(bp=find(ptr))==NULL||bp->free)
		Except_raise(&Assert_Failed,file,line);

	newptr=Mem_alloc(nbytes,file,line);
	memcpy(newptr,ptr,nbytes<bp->size? nbytes:bp->size);
	Mem_free(ptr,file,line);
	return newptr;
}


void *Mem_calloc(long count,long nbytes,const char*file,int line)
{
	void *ptr;
	assert(count>0);
	assert(nbytes>0);
	ptr=Mem_alloc(count*nbytes,file,line);
	memset(ptr,'\0',count*nbytes);
	return ptr;

}