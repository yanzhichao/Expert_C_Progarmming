#include "stdio.h"
#include "stdlib.h"
#include "time.h"
/*
 * 快速排序
 *
 * 参数说明：
 *     a -- 待排序的数组
 *     l -- 数组的左边界(例如，从起始位置开始排序，则l=0)
 *     r -- 数组的右边界(例如，排序截至到数组末尾，则r=a.length-1)
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
				j--; // 从右向左找第一个小于x的数
            if(i < j)
				a[i++] = a[j];
            while(i < j && a[i] < x)
				i++; // 从左向右找第一个大于x的数
            if(i < j)
				a[j--] = a[i];
        }
        a[i] = x;
        quick_sort(a, l, i-1); /* 递归调用 */
        quick_sort(a, i+1, r); /* 递归调用 */
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

	quick_sort(InputArray,0,n-1);  //快速排序

	//去重
	   for(int i=0;i<n-1;i++)
			if(InputArray[i]==InputArray[i+1])
				InputArray[i]=-1;   //将重复的数据复制为-1

		int index=0;
		for(int i=0;i<n;i++)
			if(InputArray[i]!=-1)
				InputArray[index++]=InputArray[i];  //重新生成数组

		for(int i=0;i<index;i++)
			printf("%d ",InputArray[i]);
		printf("\n");
		clock_t tend=clock();
		printf("time=%lf",((double)(tend-begin)/CLOCKS_PER_SEC));
		
		
}