int Partition2(int*array, int left, int right)
{
    int key = array[right];//将基准值保存
    int begin = left;
    int end = right;
    while (begin < end)
    {
        while (begin < end && array[begin] <= key)
            ++begin;
        //填坑
        if (begin < end)
        {
            array[end] = array[begin];
        }

        while (begin < end && array[end] >= key)
            --end;

        if (begin < end)
        {
            array[begin] = array[end];
        }

    }
    //begin与end相遇，则用基准值去填充这个坑
    if (begin == end)
    {
        array[begin] = key;
    }
    return begin;
}
//递归调用
void QuickSort(int *array, int left, int right)
{
    assert(array || left < 0 || right < 0);
    /*if (left >= right)
    {
        return;
    }*/
    if (left < right)
    {
        int div = Partition2(array, left, right);
        QuickSort(array, left, div - 1);//对划分出来的左半部分进行排序
        QuickSort(array, div + 1, right);//对划分出来的右半部分进行排序
    }
}