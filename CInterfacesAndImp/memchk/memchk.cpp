#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#include "except.h"

#include "mem.h"

//本程序实现的是一种最佳适配的内存管理方法
//为了使得malloc函数从来不返回同一地址两次，通过从不释放申请的内存块来做到
//这种方式在申请来内存后就进入管理list 通过对list的操作来自己管理内存。
//好处可以避免错误。而缺点在于如果一下子申请了很大的内存，那么这块内存将
//在程序结束之前不再会被释放。
//因此这种内存管理方式适合用于内存申请大小波动并不是很大的情况。
//虽然这种方式的应用并不是很好
//但是其用hash表来管理每次用户申请的内存还是非常的巧妙的。


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
//定义一个descriptor 结构体 把他的地址赋值给他的第一个变量 free 
//此处freelist是一个循环链表，起初时候自己指向自己没有任何其他空闲内存块
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
	//对nbytes做字节对齐扩充到合适字节，避免空间浪费
	nbytes=((nbytes+sizeof(union align)-1)/(sizeof(union align)))*(sizeof(union align));
	//从空闲块的首地址的下一块开始寻找合适的空间，freelist是一个循环链表，这里所谓的空闲块
	//并不是真正都是空闲的，其实是所有当前已经申请过的块，每一块都有至少（NALLOC）大。经过多次分别后
	//块中有的是空闲的，而有的可能已经被用满。
	for(bp=freelist.free;bp;bp=bp->free)
	{
		if(bp->size>nbytes) //如果找到合适的空闲块
		{
			bp->size-=nbytes;  
			ptr=(char *)bp->ptr+bp->size;  //得到分配空间的首地址
			if((bp=dalloc(ptr,nbytes,file,line))!=NULL)  //申请一个存储新ptr的结构体bp
			{
				unsigned h=hash(ptr,htab);               //然后将这个结构体加入到hash表中
				bp->link=htab[h];                        //表明这块内存已经被占用了。
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
		if(bp==&freelist)  //没有合适的空闲块，那么分配一个新块
		{
			struct descriptor *newptr;
			if((ptr=malloc(nbytes+NALLOC))==NULL     //新块大小由固定宏和nbytes共同决定，意味着所有的块都将有大小上的一些差异
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