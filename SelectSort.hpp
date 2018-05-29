��ʽһ��
void SelectSort(int *array, int size)
{
    assert(array || size < 0);
    int i = 0;
    int j = 0;
    int maxPos = 0;
    for (; i < size - 1; ++i)
    {
        maxPos = size - i - 1;//��¼����Ԫ��,Ĭ�����һ��Ԫ�����
        for (j = 0; j < size - i; ++j)
        {
            //�ҵ�����Ԫ��
            if (array[j]>array[maxPos])
            {
                maxPos = j;
            }
        }
        //������Ԫ�������һ��Ԫ�ؽ��н���
        swap(array[maxPos], array[size - i - 1]);
    }
}

��ʽ��
void SelectSort_OP(int *array, int size)
{
    assert(array || size < 0);
    int i = 0;
    int begin = 0;
    int end = size - 1;
    while (begin < end)
    {
        int minPos = begin;
        int maxPos = end;
        for (i = begin; i <= end; ++i)
        {
            //���������СԪ��
            if (array[i]>array[maxPos])
            {
                maxPos = i;
            }

            if (array[i] < array[minPos])
            {
                minPos = i;
            }
        }
        //����Ԫ��
        if (minPos != begin)
        {
            swap(array[minPos], array[begin]);
        }
        //��ֹ�ڿ�ʼ������ֱ�����������СԪ��
        if (maxPos == begin)
        {
            maxPos = minPos;
        }


        if (maxPos != end)
        {
            swap(array[maxPos], array[end]);
        }
        begin++;
        end--;
    }
}