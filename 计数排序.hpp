void CountSort(int *array, int size)
{
    assert(array || size < 0);
    int minData = array[0];
    int maxData = array[0];

    //ȷ������Ԫ�صķ�Χ
    for (int i = 1; i < size; ++i)
    {
        if (array[i] < minData)
            minData = array[i];
        else if (array[i] > maxData)
            maxData = array[i];
    }
    //���ٸ����ռ�
    int range = maxData - minData + 1;
    int *pCount = new int[range];
    memset(pCount, 0, range*sizeof(int));

    //ͳ��ÿ���ַ����ֵĴ���
    for (int i = 0; i < size; ++i)
    {
        pCount[array[i] - minData]++;//�ڴ˴����ٵ����䣬��һ�����������飬�±��0��ʼ
    }

    //�����Ѿ�ͳ�ƺõ��ַ�
    int index = 0;
    for (int i = 0; i < range; ++i)
    {

        while (pCount[i]--)
            array[index++] = i + minData;
    }
    delete[] pCount;
}