void _RadixSort_MSD(int*array, int left, int right, int bit, int* bucket)
{
    assert(array);
    if (bit <= 0)
        return;

    int radix = (int)pow((double)10, bit - 1);
    // ͳ��ÿ��Ͱ��Ԫ�صĸ���
    int bucketCount[10] = { 0 };
    for (int i = left; i < right; ++i)
        bucketCount[array[i] / radix % 10]++;

    // ͳ��ÿ��Ͱ����ʼ��ַ
    int startAddr[10] = { left };
    for (int i = 1; i < 10; ++i)
        startAddr[i] = startAddr[i - 1] + bucketCount[i - 1];

    // ����Ԫ�ط��õ���Ӧ��Ͱ��
    for (int i = left; i < right; ++i)
    {
        int bucketNo = array[i] / radix % 10;
        bucket[startAddr[bucketNo]++] = array[i];
    }

    // ����
    memcpy(array + left, bucket + left, (right - left)*sizeof(array[0]));

    for (int i = 0; i < 10; ++i)
    {
        int begin = startAddr[i] - bucketCount[i];
        int end = startAddr[i];
        if (begin + 1 < end)
            _RadixSort_MSD(array, begin, end, bit - 1, bucket);
    }
}
void RadixSort_MSD(int *array, int size)
{
    int* tmp = new int[size];
    int bit = GetBitCount(array, size);
    _RadixSort_MSD(array, 0, size, bit, tmp);
    delete[] tmp;
}