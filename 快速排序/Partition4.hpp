�Ż�
//�ڻ�û�׼ֵ��ʱ�����ڻ�����������С��ֵ����� �ڻ�׼ֵ��ѡ���ϣ���ʮ����Ҫ
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
//�ڴ˴��������ǿ�����
//����
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
        while (begin < end && array[begin] <= key)//�˴��ӵ��ڵ�ԭ���ǣ����������ȵ�Ԫ�أ��������ĵ���߻����ұ���û��Ӱ���
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
    //����ָ��������ʱ�򣬽��������ĵط������һ��Ԫ�أ�����׼ֵ
    if (begin != right)
    {
        swap(array[begin], array[right-1]);
    }
    return begin;
}

//��ʽ�����ڿӷ�
//����
int Partition2(int*array, int left, int right)
{
    //int key = array[right];//����׼ֵ����
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
        //���
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
    //begin��end���������û�׼ֵȥ��������

    array[begin] = key;

    return begin;
}

//��ʽ����ǰ��ָ��
//����
int Partition3(int*array, int left, int right)
{
    assert(array);
    int cur = left;
    int pre = cur - 1;
    int index = GetMidKey(array, left, right);//�Ż�
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
        ++cur;//��cur�ߵ���һ��λ�ã��Ӷ���ʼ�µ�һ�ֵıȽ�
    }
    if (++pre != right)
        swap(array[pre], array[right-2]);
    return pre;
}

//������
//�Ż�---->1��������Ԫ�ؽ���֮ʱ���������е�Ԫ�ؽ�Ϊ����֮ʱ������ò������򣬴Ӷ���߳����Ч��2���ڻ�ȡ��׼ֵ֮ʱ����������׼ֵ��������������ֵ������Сֵ
void QuickSort(int *array, int left, int right)
{
    assert(array || left < 0 || right < 0);
    //�������е�Ԫ�ظ������٣�����ò������򣬸����ܽ�ʡʱ��
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