void AdjustDown(size_t parent)
    {
        //标记左孩子,且默认左孩子为最小的孩子
        size_t child = parent * 2 + 1;
        size_t size = _array.size();
        //找最小的孩子
        while (child < size)
        {
            //Compare com;
            if (child + 1 <size && Compare()(_array[child + 1], _array[child]))//在此处，因为默认左孩子最小，因此要返回true，只能是这样
            {
                child = child + 1;//右孩子为最小
            }
            //比较最小的孩子与双亲的大小----值域
            if (Compare()(_array[child], _array[parent]))
            {
                swap(_array[parent], _array[child]);
                //交换之后，可能导致孩子结点不为堆
                parent = child;
                child = parent * 2 + 1;
            }
            else
                break;
        }
    }