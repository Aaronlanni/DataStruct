方式一：
void SelectSort(int *array, int size)
{
    assert(array || size < 0);
    int i = 0;
    int j = 0;
    int maxPos = 0;
    for (; i < size - 1; ++i)
    {
        maxPos = size - i - 1;//记录最大的元素,默认最后一个元素最大
        for (j = 0; j < size - i; ++j)
        {
            //找到最大的元素
            if (array[j]>array[maxPos])
            {
                maxPos = j;
            }
        }
        //将最大的元素与最后一个元素进行交换
        swap(array[maxPos], array[size - i - 1]);
    }
}

方式二
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
            //找最大与最小元素
            if (array[i]>array[maxPos])
            {
                maxPos = i;
            }

            if (array[i] < array[minPos])
            {
                minPos = i;
            }
        }
        //交换元素
        if (minPos != begin)
        {
            swap(array[minPos], array[begin]);
        }
        //防止在开始与结束分别出现最大与最小元素
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