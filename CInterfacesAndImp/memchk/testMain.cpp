#include "stdio.h"
#include "except.h"
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
//ftest��������������0ֵ��
//����0ֵ�������쳣WrongInput
Except_T WrongInput={"Wrong Input"};
void ftest(int a)
{
	if(a==0)
		RAISE(WrongInput);
	else
		printf("Correct Input=%d",a);
}

void ftest(int a,const char* file,int line)   //���Ҫ��LINE�Ŷ�λ�ڵ��ú����ӿڴ�����ô������Ϊ��������
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

