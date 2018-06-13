优化
//在获得基准值的时候，由于会获得最大或者最小的值，因此 在基准值的选择上，将十分重要
int GetMidKey(int *array, int left,int right)
{
    assert(array || left-right<0);
    int mid = left + ((right - left) >> 1);
    if (array[left] < array[right - 1])
    {
        if (array[left] > array[mid])
            return left;
        else if (array[right - 1] < array[mid])
            return right - 1;
        else
            return mid;
    }
    else
    {
        if (array[left] < array[mid])
            return left;
        else if (array[mid] < array[right - 1])
            return right - 1;
        else
            return mid;
    }
}
//在此处给出的是开区间
//升序
int Partition1(int*array, int left, int right)
{
    //int key = right-1;
    int index = GetMidKey(array, left,right);
    if (index != (right-1))
        swap(array[index], array[right-1]);
    int key = array[right-1];
    int begin = left;
    int end = right-1;
    while (begin < end)
    {
        while (begin < end && array[begin] <= key)//此处加等于的原因是：如果碰到相等的元素，不论是拍到左边还是右边是没有影响的
        {
            ++begin;
        }
        while (begin < end && array[end] >= key)
        {
            --end;
        }
        if (begin < end)
            swap(array[begin], array[end]);
    }
    //两个指针相遇的时候，交换相遇的地方与最后一个元素，即基准值
    if (begin != right)
    {
        swap(array[begin], array[right-1]);
    }
    return begin;
}

//方式二，挖坑法
//升序
int Partition2(int*array, int left, int right)
{
    //int key = array[right];//将基准值保存
    int index = GetMidKey(array, left,right);
    if (index != (right-1))
        swap(array[index], array[right-1]);
    int key = array[right-1];
    int begin = left;
    int end = right-1;
    while (begin < end)
    {
        while (begin < end && array[begin] <= key)
            ++begin;
        //填坑
        if (begin < end)
        {
            array[end] = array[begin];
            end--;
        }

        while (begin < end && array[end] >= key)
            --end;

        if (begin < end)
        {
            array[begin] = array[end];
            begin++;
        }

    }
    //begin与end相遇，则用基准值去填充这个坑

    array[begin] = key;

    return begin;
}

//方式三，前后指针
//升序
int Partition3(int*array, int left, int right)
{
    assert(array);
    int cur = left;
    int pre = cur - 1;
    int index = GetMidKey(array, left, right);//优化
    if (index != (right-1))
    {
        swap(array[index], array[right-1]);
    }
    int key = array[right-1];
    while (cur < right)
    {
        while (array[cur] < key&&++pre != cur)
        {
            swap(array[pre], array[cur]);
        }
        ++cur;//让cur走到下一个位置，从而开始新的一轮的比较
    }
    if (++pre != right)
        swap(array[pre], array[right-2]);
    return pre;
}

//开区间
//优化---->1、在区间元素较少之时，且区间中的元素较为有序之时，则采用插入排序，从而提高程序的效率2、在获取基准值之时，尽量将基准值不给在区间的最大值或者最小值
void QuickSort(int *array, int left, int right)
{
    assert(array || left < 0 || right < 0);
    //当区间中的元素个数较少，则采用插入排序，更加能节省时间
    if (right - left < 10)
        InsertSort(array, right - left);
    else
    {
        if (left < right)
        {
            size_t div = Partition3(array, left, right);
            QuickSort(array, left, div);
            QuickSort(array, div + 1, right);
        }
    }
}