#include "stdio.h"
#include "except.h"
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
//ftest函数不允许输入0值，
//输入0值将触发异常WrongInput
Except_T WrongInput={"Wrong Input"};
void ftest(int a)
{
	if(a==0)
		RAISE(WrongInput);
	else
		printf("Correct Input=%d",a);
}

void ftest(int a,const char* file,int line)   //如果要想LINE号定位在调用函数接口处，那么可以作为参数传入
{
	if(a==0)
		Except_raise(&WrongInput,file,line);
	else
		printf("Correct Input=%d",a);

}


//int main()
//{
//	int a=0;
//TRY
//    ftest(0,__FILE__,__LINE__);
//EXCEPT(WrongInput)
//printf("FILE: %s,LINE: %d, %s\n",Except_frame.file, Except_frame.line,Except_frame.exception->reason);
//END_TRY; 
//    getchar();
//}

#include "mem.h"
int main()
{
	int a=0;
	int* ptr;
	TRY
		 ptr=(int *)ALLOC(10000000000*sizeof(int));
	EXCEPT(Mem_Failed)
		printf("FILE: %s,LINE: %d, %s\n",Except_frame.file, Except_frame.line,Except_frame.exception->reason);
	END_TRY; 

	for(int i=0;i<100;i++)
		ptr[i]=i;
	for(int i=0;i<100;i++)
		printf("%d ",*(ptr+i));
	   
	getchar();
}

