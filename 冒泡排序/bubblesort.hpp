void BubbleSort(int *array, int size)
{
    assert(array || size < 0);
    int i = 0;
    int j = 0;
    for (; i < size - 1; ++i)
    {
        for (j = 0; j < size - i - 1; ++j)
        {
            if (array[j] > array[j + 1])
            {
                swap(array[j], array[j + 1]);
            }
        }
    }
}