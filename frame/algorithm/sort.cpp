#include "sort.h"
#include<stdio.h>

/* 
Î±´úÂë
for i = 1, n
j = i
while(j > 0 and E[j] < E[j-1])
swap(E[j], E[j-1])
j--
*/
void algo::Swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void algo::InsertSort(int array[], int n)
{
	for(int i = 1; i < n; i++)
	{
		for(int j = i; j > 0; j--)
		{
			if(array[j] > array[j-1])
				Swap(array[j],array[j-1]);
		}
	}
}

void algo::PrintArray(int array[], int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("%d ",array[i]);
	}
	printf("\n");
}

void algo::BubbleSort(int array[],int n)
{
	for(int i = 0; i < n; i++)
	{
	//	for(int j = 0; j < n - i = 1)
	}
}