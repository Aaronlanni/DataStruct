int Partition1(int*array, int left, int right)
{
    int key = right;
    int begin = left;
    int end = right;
    while (begin < end)
    {
        while (begin < end && array[begin] <= array[key])//此处加等于的原因是：如果碰到相等的元素，不论是拍到左边还是右边是没有影响的
        {
            ++begin;
        }
        while (begin < end && array[end] >= array[key])
        {
            --end;
        }
        if (begin != end)
            swap(array[begin], array[end]);
    }
    //两个指针相遇的时候，交换相遇的地方与最后一个元素，即基准值
    if (begin != key)
    {
        swap(array[begin], array[key]);
    }
    return begin;
}
//注意递归调用时的区间问题
void QuickSort(int *array, int left, int right)
{
    assert(array || left < 0 || right < 0);
    /*if (left >= right)
    {
        return;
    }*/
    if (left < right)
    {
        int div = Partition1(array, left, right);
        QuickSort(array, left, div - 1);//对划分出来的左半部分进行排序
        QuickSort(array, div + 1, right);//对划分出来的右半部分进行排序
    }
}