//���ŵķǵݹ��㷨
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

        //��������е�Ԫ�ظ�������1��������ֿ�
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