#include "stdio.h"
#include "stdlib.h"
#include "time.h"
/*
 * ��������
 *
 * ����˵����
 *     a -- �����������
 *     l -- �������߽�(���磬����ʼλ�ÿ�ʼ������l=0)
 *     r -- ������ұ߽�(���磬�������������ĩβ����r=a.length-1)
 */
void quick_sort(int a[], int l, int r)
{
    if (l < r)
    {
		int i,j,x;

        i = l;
        j = r;
        x = a[i];
        while (i < j)
        {
            while(i < j && a[j] > x)
				j--; // ���������ҵ�һ��С��x����
            if(i < j)
				a[i++] = a[j];
            while(i < j && a[i] < x)
				i++; // ���������ҵ�һ������x����
            if(i < j)
				a[j--] = a[i];
        }
        a[i] = x;
        quick_sort(a, l, i-1); /* �ݹ���� */
        quick_sort(a, i+1, r); /* �ݹ���� */
    }
}

int main()
{

    srand(time(NULL));
	int n=0;
	scanf("%d",&n);
	int *InputArray=(int *)malloc(sizeof(int)*n);

	/*for(int i=0;i<n;i++)
	scanf("%d",&InputArray[i]);*/
	clock_t begin=clock();
	for(int i=0;i<n;i++)
		InputArray[i]=rand()%1000;

	quick_sort(InputArray,0,n-1);  //��������

	//ȥ��
	   for(int i=0;i<n-1;i++)
			if(InputArray[i]==InputArray[i+1])
				InputArray[i]=-1;   //���ظ������ݸ���Ϊ-1

		int index=0;
		for(int i=0;i<n;i++)
			if(InputArray[i]!=-1)
				InputArray[index++]=InputArray[i];  //������������

		for(int i=0;i<index;i++)
			printf("%d ",InputArray[i]);
		printf("\n");
		clock_t tend=clock();
		printf("time=%lf",((double)(tend-begin)/CLOCKS_PER_SEC));
		
		
}