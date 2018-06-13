int Partition2(int*array, int left, int right)
{
    int key = array[right];//����׼ֵ����
    int begin = left;
    int end = right;
    while (begin < end)
    {
        while (begin < end && array[begin] <= key)
            ++begin;
        //���
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
    //begin��end���������û�׼ֵȥ��������
    if (begin == end)
    {
        array[begin] = key;
    }
    return begin;
}
//�ݹ����
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
        QuickSort(array, left, div - 1);//�Ի��ֳ�������벿�ֽ�������
        QuickSort(array, div + 1, right);//�Ի��ֳ������Ұ벿�ֽ�������
    }
}