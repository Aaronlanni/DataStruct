void InsertSort(int *array, size_t size)
{
	assert(array || size < 0);
	for (size_t i = 1; i < size; ++i)
	{
		int key = array[i];
		int end = i - 1;
		//�Ƚϲ��Ұ���
		while (end >= 0 && key < array[end])
		{
			array[end + 1] = array[end];
			end--;
		}
		//����Ԫ��
		array[end + 1] = key;
	}
}

//*********��������********����������ַ�************
void InsertSort_OP(int *array, int size)
{
	assert(array || size < 0);
	for (int i = 1; i < size; ++i)
	{
		int left = 0;
		int right = i - 1;
		int key = array[i];
		int mid = 0;
		//�����������У����Ҳ���Ԫ�ص�λ��
		while (left <= right)
		{
			//mid = (right + left) >> 1;
			mid = right + ((left - right) >> 1);
			if (key < array[mid])
				right = mid - 1;
			else
				left = mid + 1;
		}
		//����Ԫ��
		int end = i - 1;
		while (end >= left)
		{
			array[end + 1] = array[end];
			end--;
		}
		array[left] = key;
	}
}


//*********��������********ϣ������************�ֿ�����
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
			//�Ƚϲ��Ұ���
			while (end >= 0 && key < array[end])
			{
				array[end + gap] = array[end];
				end -= gap;
			}
			//����Ԫ��
			array[end + gap] = key;
		}
		--gap;
	}

}

//*********��������********ϣ������************�ֿ�����********����
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
			//�Ƚϲ��Ұ���
			while (end >= 0 && key < array[end])
			{
				array[end + gap] = array[end];
				end -= gap;
			}
			//����Ԫ��
			array[end + gap] = key;
		}
	}

}