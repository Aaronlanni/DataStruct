//快排的非递归算法
void QuickSortNor(int *array, int left,int right)
{
    stack<int> s;
    s.push(right);
    s.push(left);

    while (!s.empty())
    {
        left = s.top();
        s.pop();
        right = s.top();
        s.pop();

        //如果区间中的元素个数大于1，则继续分块
        if (left < right)
        {
            int div = Partition1(array, left, right);
            s.push(right);
            s.push(div + 1);
            s.push(div);
            s.push(left);
        }               
    }
}