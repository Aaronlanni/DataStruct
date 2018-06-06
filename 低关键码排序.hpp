int GetBitCount(int *array, int size)
{
    int radix = 10;
    int count = 1;
    for (int i = 0; i < size; ++i)
    {
        if (radix < array[i])
        {
            count++;
            radix *= 10;
        }   
    }
    return count;
}

//��������-----�ǱȽ�����2----�͹ؼ�������
void RadixSort_LSD(int*array, int size)
{
    assert(array || size < 0);
    //��ȡ������ı���λ
    int bitCount = GetBitCount(array, size);
    int radix = 1;

    int*bucket = new int[size];//�����ռ䣬
    for (int idx = 0; idx < bitCount; ++idx)
    {
        int bucketCount[10] = { 0 };//��ż���������
        //ͳ��ÿ��Ͱ��Ԫ�صĸ���
        for (int i = 0; i < size; ++i)
        {
            int index = array[i] / radix % 10;
            //����Ǹ���,�������0��Ͱ��λ��
            if (index < 0)
            {
                bucketCount[0]++;
            }
            else
            {
                bucketCount[index]++;//��ÿһλ����ʽ��Ԫ��ͳ��
            }

        }
        //����ÿ��Ͱ����ʼ��ַ
        int startAddr[10] = { 0 };
        for (int i = 1; i < 10; ++i)//��ʾ10��Ͱ
        {
            startAddr[i] = startAddr[i - 1] + bucketCount[i - 1];
        }

        //����ӦԪ�ط��õ���Ӧ��Ͱ��
        for (int i = 0; i < size; ++i)
        {
            //����Ͱ��
            int bucketNo = array[i] / radix % 10;
            if (bucketNo < 0)
            {
                if (array[i] > array[i + 1])
                    swap(array[i],array[i + 1]);
                bucket[startAddr[0]++] = array[i];
            }
            else
            {
                //����ӦԪ�ط��õ���Ӧ��Ͱ��
                bucket[startAddr[bucketNo]++] = array[i];
            }   
        }
        //����Ԫ��
        memcpy(array, bucket, size*sizeof(array[0]));

        //���������Ű�λ��....
        radix *= 10;
    }
}