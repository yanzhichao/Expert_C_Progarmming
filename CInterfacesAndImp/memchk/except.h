#ifndef EXCEPT_INCLUDED
#define EXCEPT_INCLUDED
/***************************************************************************
                        如何使用异常
 ***************************************************************************
 首先要定义一个异常结构体来指示是发生了什么异常。结构体用问题提示符初始化

     Except_T WrongInput={"Wrong Input"};
 然后再编写函数时候就可以用RAISE（e）宏或者Except_raise(T* e,const char *file,int line)函数来
 触发一个异常 如下函数
 //ftest函数不允许输入0值，
 //输入0值将触发异常WrongInput

 void ftest(int a)
 {
 if(a==0)
 RAISE(WrongInput);
 else
 printf("Correct Input=%d",a);
 }

 //如果要想LINE号定位在调用函数接口处，那么可以作为参数传入
 void ftest(int a,const char* file,int line)   
 {
 if(a==0)
 Except_raise(&WrongInput,file,line);
 else
 printf("Correct Input=%d",a);

 }

 然后这些函数中异常就可以被捕获了，用如下TRY S EXCEPT S1 END_TRY; 的方式捕获
 TRY
    ftest(0,__FILE__,__LINE__);
 EXCEPT(WrongInput)
     printf("FILE: %s,LINE: %d, %s\n",Except_frame.file, Except_frame.line,Except_frame.exception->reason);
 END_TRY; 

 /*************************************************************************************/
#include "setjmp.h"

#define T Except_T
typedef struct T 
{
	const char *reason;
}T;


typedef struct Except_Frame Except_Frame;

struct Except_Frame{
	Except_Frame *prev;
	jmp_buf env;
	const char *file;
	int line;
	const T *exception;
};


enum { Except_entered=0, //没有异常
	   Except_raised, //出现异常
	   Except_handled, //已处理异常
	   Except_finalized
     };

extern Except_Frame *Except_stack;   //异常栈的栈顶

//参数 e 为异常的名字 可以随意取名 但是必须声明在
//Except_T 结构体，如分配一个内存分配失败异常
//Except_T Mem_Failed={"Allocation failed"};
//则 e=Mem_Failed 
#define RAISE(e) Except_raise(&(e),__FILE__,__LINE__)


#define RERAISE Except_raise(Except_frame.exception,Except_frame.file,Except_frame.line)
#define TRY do{\
                 volatile int Except_flag;\
				 Except_Frame Except_frame;\
				 Except_frame.prev=Except_stack;\
				 Except_stack=&Except_frame;\
				 Except_flag=setjmp(Except_frame.env);\
				 if(Except_flag==Except_entered){


#define EXCEPT(e) if(Except_flag==Except_entered) \
					 Except_stack=Except_stack->prev;\
				   }\
				  else if (Except_frame.exception==&(e))\
				  {\
					  Except_flag=Except_handled;

#define ELSE  if(Except_flag==Except_entered)\
					  Except_stack=Except_stack->prev;\
				 } else {\
				      Except_flag=Except_handled;

#define FINALLY if(Except_flag==Except_entered)\
					  Except_stack=Except_stack->prev;\
				 }\
				 {\
					 if(Except_flag==Except_entered)\
						 Except_flag=Except_finalized;

 //如果异常没有处理就END_TRY  会再次触发异常
#define END_TRY if(Except_flag==Except_entered) \
					 Except_stack=Except_stack->prev;\
				 }\
				 if(Except_flag==Except_raised) RERAISE;\
                 }while (0)
           
           
#define RETURN switch(,0) default;return

void Except_raise(const T *e,const char *file,int line);


#undef T

#endif