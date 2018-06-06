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

//基数排序-----非比较排序2----低关键码排序
void RadixSort_LSD(int*array, int size)
{
    assert(array || size < 0);
    //获取最大数的比特位
    int bitCount = GetBitCount(array, size);
    int radix = 1;

    int*bucket = new int[size];//辅助空间，
    for (int idx = 0; idx < bitCount; ++idx)
    {
        int bucketCount[10] = { 0 };//存放计数的数组
        //统计每个桶中元素的个数
        for (int i = 0; i < size; ++i)
        {
            int index = array[i] / radix % 10;
            //如果是负数,将其放在0号桶的位置
            if (index < 0)
            {
                bucketCount[0]++;
            }
            else
            {
                bucketCount[index]++;//以每一位的形式将元素统计
            }

        }
        //计算每个桶的起始地址
        int startAddr[10] = { 0 };
        for (int i = 1; i < 10; ++i)//表示10个桶
        {
            startAddr[i] = startAddr[i - 1] + bucketCount[i - 1];
        }

        //将对应元素放置到对应的桶中
        for (int i = 0; i < size; ++i)
        {
            //计算桶号
            int bucketNo = array[i] / radix % 10;
            if (bucketNo < 0)
            {
                if (array[i] > array[i + 1])
                    swap(array[i],array[i + 1]);
                bucket[startAddr[0]++] = array[i];
            }
            else
            {
                //将对应元素放置到对应的桶中
                bucket[startAddr[bucketNo]++] = array[i];
            }   
        }
        //回收元素
        memcpy(array, bucket, size*sizeof(array[0]));

        //下面再来排百位等....
        radix *= 10;
    }
}