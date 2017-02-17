#ifndef SORT_H
#define SORT_H


namespace algo{
void Swap(int& a, int& b);
/* 插入排序,
在一个有序的序列中插入一个数，使得插入数据后仍有序
O(n2)
移动第i 个将其与前面i-1 个数比较。
*/
void InsertSort(int array[], int n);
void PrintArray(int array[], int n);

/* 冒泡排序

*/
void BubbleSort(int array[],int n);


}
#endif