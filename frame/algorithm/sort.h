#ifndef SORT_H
#define SORT_H


namespace algo{
void Swap(int& a, int& b);
/* ��������,
��һ������������в���һ������ʹ�ò������ݺ�������
O(n2)
�ƶ���i ��������ǰ��i-1 �����Ƚϡ�
*/
void InsertSort(int array[], int n);
void PrintArray(int array[], int n);

/* ð������

*/
void BubbleSort(int array[],int n);


}
#endif