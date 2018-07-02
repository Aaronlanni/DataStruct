#define _CRT_SECURE_NO_WARNINGS 1
//#pragma once
#include"heap.hpp"

//���ȼ�����
template<class T,class Compare>
class PriorityQueue
{
public:
    PriorityQueue()
    {}

    void Push(const T&data)
    {
        _hp.Push(data);
    }
    void Pop()
    {
        _hp.Pop();
    }
    bool Empty()const
    {
        return _hp.Empty();
    }
    size_t Size()const
    {
        return _hp.Size();
    }
    T Top()const
    {
        return _hp.Top();
    }

private:
    Heap<T, Compare> _hp;
};

void Test1()
{
    PriorityQueue<int,Less<int> > q;
    q.Push(2);//�����з���Ԫ��
    q.Push(10);
    q.Push(1);
    cout << q.Size() << endl;
    cout << q.Top() << endl;

    q.Pop();//ɾ������Ԫ��
    cout << q.Size() << endl;
    cout << q.Top() << endl;
    if (!q.Empty())//�п�
        cout << "�ǿ�" << endl;
    else
        cout << "��" << endl;

    q.Pop();
    cout << q.Size() << endl;
    cout << q.Top() << endl;

    q.Pop();//����ֻ��һ��Ԫ��
    cout << q.Size() << endl;
    cout << q.Top() << endl;
    if (!q.Empty())
        cout << "�ǿ�" << endl;
    else
        cout << "��" << endl;
    q.Pop();//�ն�
    cout << q.Size() << endl;
    cout << q.Top() << endl;
    if (!q.Empty())
        cout << "�ǿ�" << endl;
    else
        cout << "��" << endl;
}