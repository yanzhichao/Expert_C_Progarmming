#ifndef EXCEPT_INCLUDED
#define EXCEPT_INCLUDED
/***************************************************************************
                        ���ʹ���쳣
 ***************************************************************************
 ����Ҫ����һ���쳣�ṹ����ָʾ�Ƿ�����ʲô�쳣���ṹ����������ʾ����ʼ��

     Except_T WrongInput={"Wrong Input"};
 Ȼ���ٱ�д����ʱ��Ϳ�����RAISE��e�������Except_raise(T* e,const char *file,int line)������
 ����һ���쳣 ���º���
 //ftest��������������0ֵ��
 //����0ֵ�������쳣WrongInput

 void ftest(int a)
 {
 if(a==0)
 RAISE(WrongInput);
 else
 printf("Correct Input=%d",a);
 }

 //���Ҫ��LINE�Ŷ�λ�ڵ��ú����ӿڴ�����ô������Ϊ��������
 void ftest(int a,const char* file,int line)   
 {
 if(a==0)
 Except_raise(&WrongInput,file,line);
 else
 printf("Correct Input=%d",a);

 }

 Ȼ����Щ�������쳣�Ϳ��Ա������ˣ�������TRY S EXCEPT S1 END_TRY; �ķ�ʽ����
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


enum { Except_entered=0, //û���쳣
	   Except_raised, //�����쳣
	   Except_handled, //�Ѵ����쳣
	   Except_finalized
     };

extern Except_Frame *Except_stack;   //�쳣ջ��ջ��

//���� e Ϊ�쳣������ ��������ȡ�� ���Ǳ���������
//Except_T �ṹ�壬�����һ���ڴ����ʧ���쳣
//Except_T Mem_Failed={"Allocation failed"};
//�� e=Mem_Failed 
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

 //����쳣û�д����END_TRY  ���ٴδ����쳣
#define END_TRY if(Except_flag==Except_entered) \
					 Except_stack=Except_stack->prev;\
				 }\
				 if(Except_flag==Except_raised) RERAISE;\
                 }while (0)
           
           
#define RETURN switch(,0) default;return

void Except_raise(const T *e,const char *file,int line);


#undef T

#endif