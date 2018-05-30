void _MegreSort(int *array, int left, int right, int* tmp);
void MegreSort(int *array, int size)
{
    assert(array || size < 0);
    //������ʱ�ռ�
    int *tmp = new int[size];
    _MegreSort(array, 0, size, tmp);
    delete[] tmp;
}
void _Megre(int *array, int left,int mid, int right, int* tmp)
{
    //�����������������±�
    int index1 = left;
    int index2 = mid;

    int index = left;
    //����������ϲ�
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
    //����֮������ĸ����鲻Ϊ�գ�������Ԫ��ֱ�Ӱ�������
    while (index1 < mid)
    {
        tmp[index++] = array[index1++];
    }
    while (index2 < right)
    {
        tmp[index++] = array[index2++];
    }
    //�ӿռ��е�Ԫ��ֱ�ӿ�������
    memcpy(array+left, tmp+left, (right - left)*sizeof(int));
}
void _MegreSort(int *array, int left,int right,int* tmp)
{

    //���ֿ��������ֻ��һ��Ԫ��֮ʱ
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