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