void _MegreSort(int *array, int left, int right, int* tmp);
void MegreSort(int *array, int size)
{
    assert(array || size < 0);
    //开辟临时空间
    int *tmp = new int[size];
    _MegreSort(array, 0, size, tmp);
    delete[] tmp;
}
void _Megre(int *array, int left,int mid, int right, int* tmp)
{
    //用来标记两个数组的下标
    int index1 = left;
    int index2 = mid;

    int index = left;
    //类似于链表合并
    while (index1 < mid&&index2 < right)
    {
        if (array[index1] < array[index2])
        {
            tmp[index++] = array[index1++];
        }
        else
        {
            tmp[index++] = array[index2++];
        }
    }
    //出来之后，如果哪个数组不为空，即将其元素直接搬移下来
    while (index1 < mid)
    {
        tmp[index++] = array[index1++];
    }
    while (index2 < right)
    {
        tmp[index++] = array[index2++];
    }
    //加空间中的元素直接拷贝下来
    memcpy(array+left, tmp+left, (right - left)*sizeof(int));
}
void _MegreSort(int *array, int left,int right,int* tmp)
{

    //当分块的区间中只有一个元素之时
    if (right - left <= 1)
        return;
    if (right > left)
    {
        int mid = left + ((right - left) >> 1);
        _MegreSort(array, left, mid, tmp);
        _MegreSort(array, mid, right, tmp);
        _Megre(array, left, mid, right, tmp);;
    }

}