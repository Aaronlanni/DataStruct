void MegreSortNor(int *array, int size)
{
    int *tmp = new int[size];
    int gap = 1;
    while (gap < size)
    {
        for (int i = 0; i < size; i += 2*gap)
        {
            int left = i;
            int mid = i + gap;
            int right = mid + gap;//给出下一个区间中的元素

            //防止mid与right越界
            if (mid > size)
                mid = size;
            if (right > size)
                right = size;
            _Megre(array, left, mid, right, tmp);
        }
        gap *= 2;
    }
    delete[] tmp;
}