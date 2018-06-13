int Partition1(int*array, int left, int right)
{
    int key = right;
    int begin = left;
    int end = right;
    while (begin < end)
    {
        while (begin < end && array[begin] <= array[key])//�˴��ӵ��ڵ�ԭ���ǣ����������ȵ�Ԫ�أ��������ĵ���߻����ұ���û��Ӱ���
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
    //����ָ��������ʱ�򣬽��������ĵط������һ��Ԫ�أ�����׼ֵ
    if (begin != key)
    {
        swap(array[begin], array[key]);
    }
    return begin;
}
//ע��ݹ����ʱ����������
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
        QuickSort(array, left, div - 1);//�Ի��ֳ�������벿�ֽ�������
        QuickSort(array, div + 1, right);//�Ի��ֳ������Ұ벿�ֽ�������
    }
}