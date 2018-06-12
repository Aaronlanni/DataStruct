void ShellSort_OP(int *array, int size)
{
    assert(array || size < 0);
    int gap = size;
    while (gap > 1)
    {
        gap = gap / 3 + 1;
        for (int i = gap; i < size; ++i)
        {
            int key = array[i];
            int end = i - gap;
            //�Ƚϲ��Ұ���
            while (end >= 0 && key < array[end])
            {
                array[end + gap] = array[end];
                end -= gap;
            }
            //����Ԫ��
            array[end + gap] = key;
        }
    }
}