void InsertSort(int *array, size_t size)
{
	assert(array || size < 0);
	for (size_t i = 1; i < size; ++i)
	{
		int key = array[i];
		int end = i - 1;
		//比较并且搬移
		while (end >= 0 && key < array[end])
		{
			array[end + 1] = array[end];
			end--;
		}
		//插入元素
		array[end + 1] = key;
	}
}

//*********插入排序********利用区间二分法************
void InsertSort_OP(int *array, int size)
{
	assert(array || size < 0);
	for (int i = 1; i < size; ++i)
	{
		int left = 0;
		int right = i - 1;
		int key = array[i];
		int mid = 0;
		//在已序序列中，查找插入元素的位置
		while (left <= right)
		{
			//mid = (right + left) >> 1;
			mid = right + ((left - right) >> 1);
			if (key < array[mid])
				right = mid - 1;
			else
				left = mid + 1;
		}
		//搬移元素
		int end = i - 1;
		while (end >= left)
		{
			array[end + 1] = array[end];
			end--;
		}
		array[left] = key;
	}
}


//*********插入排序********希尔排序************分块排序
void ShellSort(int *array, int size)
{
	assert(array || size < 0);
	int gap = 3;
	while (gap)
	{
		for (int i = gap; i < size; ++i)
		{
			int key = array[i];
			int end = i - gap;
			//比较并且搬移
			while (end >= 0 && key < array[end])
			{
				array[end + gap] = array[end];
				end -= gap;
			}
			//插入元素
			array[end + gap] = key;
		}
		--gap;
	}

}

//*********插入排序********希尔排序************分块排序********最优
void ShellSort_OP(int *array, int size)
{
	assert(array || size < 0);
	int gap = size;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (int i = gap; i < size; ++i)
		{
			int key = array[i];
			int end = i - gap;
			//比较并且搬移
			while (end >= 0 && key < array[end])
			{
				array[end + gap] = array[end];
				end -= gap;
			}
			//插入元素
			array[end + gap] = key;
		}
	}

}