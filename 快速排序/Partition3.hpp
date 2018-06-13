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
        if (cur < right&&++pre != cur)//���cur�е�ֵС��key���Ѿ���pre����һ��
        {
            swap(array[pre], array[cur]);
        }
        ++cur;//��cur�ߵ���һ��λ�ã��Ӷ���ʼ�µ�һ�ֵıȽ�
    }
    ++pre;
    swap(array[pre], key);
    return pre;
}
//[  ]������
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
        QuickSort(array, left, div - 1);//�Ի��ֳ�������벿�ֽ�������
        QuickSort(array, div + 1, right);//�Ի��ֳ������Ұ벿�ֽ�������
    }
}