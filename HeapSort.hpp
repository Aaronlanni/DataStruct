#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<algorithm>
#include<iostream>
using namespace std;

//����----��ѣ�����----С��
void AdjustHeap(int *array, int size, size_t parent)
{
	//Ĭ���������
	size_t child = parent * 2 + 1;
	while (child < size)
	{
		//�����ĺ���
		if (child + 1 < size&&array[child] < array[child + 1])
			child = child + 1;
		//����
		if (array[parent] < array[child])
		{
			swap(array[parent], array[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			return;
	}
}

void HeapSort(int *array, int size)
{
	//������
	int root = (size - 1 - 1) >> 1;
	for (; root >= 0; --root)
	{
		AdjustHeap(array, size, root);//���µ���
	}
	//����
	int i = 0;
	for (; i < size - 1; ++i)
	{
		//�Ѷ�Ԫ�������һ��Ԫ�ؽ���
		swap(array[0], array[size - 1 - i]);
		AdjustHeap(array, size - i - 1,0);
	}
}



void Test2()
{
	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23 };

	HeapSort(array, sizeof(array) / sizeof(*array));
	int i = 0;
	for (; i < sizeof(array) / sizeof(*array); ++i)
	{
		cout << array[i] << " " << endl;
	}
}