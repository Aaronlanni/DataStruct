int Partition3(int*array, int left,int right)
{
    int key = array[right];
    int cur = 0;
    int pre = cur - 1;
    while (cur < right)
    {
        while (cur < right&&array[cur] >= key)
        {
            ++cur;
        }
        if (cur < right&&++pre != cur)//如果cur中的值小于key，已经让pre走了一步
        {
            swap(array[pre], array[cur]);
        }
        ++cur;//让cur走到下一个位置，从而开始新的一轮的比较
    }
    ++pre;
    swap(array[pre], key);
    return pre;
}
//[  ]闭区间
void QuickSort(int *array, int left, int right)
{
    assert(array || left < 0 || right < 0);
    /*if (left >= right)
    {
        return;
    }*/
    if (left < right)
    {
        int div = Partition3(array, left, right);
        QuickSort(array, left, div - 1);//对划分出来的左半部分进行排序
        QuickSort(array, div + 1, right);//对划分出来的右半部分进行排序
    }
}