#define _CRT_SECURE_NO_WARNING
#include<stdio.h>
typedef struct
{
	int compare;
	int move;
}count;
void insertSort(int a[], int n)
{
	count c;
	int i, j;
	c.compare = 0;
	c.move = 0;
	for (i = 2; i <=n; i++)
	{
		c.compare++;
		if (a[i] < a[i - 1])
		{
			c.move++;
			a[0] = a[i];
			a[i] = a[i - 1];
			for (j = i - 2; a[0] < a[j]; j--)
			{
				a[j + 1] = a[j];
				c.compare++;
				c.move++;
			}
			a[j + 1] = a[0];
		}
	}
	for (i = 1; i <=n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	printf("直接排序需要比较的次数为 %d\n", c.compare);
	printf("直接排序需要移动的次数为 %d\n", c.move);
}
void selectSort(int b[], int n)
{
	count c;
	int i, j,temp;
	c.compare = 0;
	c.move = 0;
	for (i = 1; i <=n; i++)
		for (j = i + 1; j <n; j++)
		{
			c.compare++;
			if (b[i] > b[j])
			{
				c.move++;
				temp = b[i];
				b[i] = b[j];
				b[j] = temp;
			}
		}
	for (i = 1; i <=n; i++)
		printf("%d ", b[i]);
	printf("\n");
	printf("选择排序需要比较的次数为 %d\n", c.compare);
	printf("选择排序需要移动的次数为 %d\n", c.move);
}
void bubbleSort(int c[], int n)
{
	count a;
	int i, j,temp;
	a.compare = 0;
	a.move = 0;
	for (i = 1; i <= n-1; i++)
		for (j = 1; j <= n - i; j++)
		{
			a.compare++;
			if (c[j] > c[j + 1])
			{
				a.move++;
				temp = c[j];
				c[j] = c[j + 1];
				c[j + 1] = temp;
			}
		}
	for (i = 1; i <=n; i++)
		printf("%d ", c[i]);
	printf("\n");
	printf("冒泡排序需要比较的次数为 %d\n", a.compare);
	printf("冒泡排序需要移动的次数为 %d\n", a.move);
}
int main()//输入数字的个数，以空格为分界输入需要排序的一串数字
{
	int a[50],b[50],c[50];
	int n;
	scanf_s("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf_s("%d", &a[i]);
		b[i] = a[i];
		c[i] = a[i];
	}
	insertSort(a, n);
	selectSort(b, n);
	bubbleSort(c, n);
}