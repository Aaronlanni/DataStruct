void CountSort(int *array, int size)
{
    assert(array || size < 0);
    int minData = array[0];
    int maxData = array[0];

    //确定数据元素的范围
    for (int i = 1; i < size; ++i)
    {
        if (array[i] < minData)
            minData = array[i];
        else if (array[i] > maxData)
            maxData = array[i];
    }
    //开辟辅助空间
    int range = maxData - minData + 1;
    int *pCount = new int[range];
    memset(pCount, 0, range*sizeof(int));

    //统计每个字符出现的次数
    for (int i = 0; i < size; ++i)
    {
        pCount[array[i] - minData]++;//在此处开辟的区间，是一段连续的数组，下标从0开始
    }

    //回收已经统计好的字符
    int index = 0;
    for (int i = 0; i < range; ++i)
    {

        while (pCount[i]--)
            array[index++] = i + minData;
    }
    delete[] pCount;
}