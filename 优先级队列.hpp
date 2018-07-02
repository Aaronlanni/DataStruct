#define _CRT_SECURE_NO_WARNINGS 1
//#pragma once
#include"heap.hpp"

//优先级队列
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
    q.Push(2);//往堆中放入元素
    q.Push(10);
    q.Push(1);
    cout << q.Size() << endl;
    cout << q.Top() << endl;

    q.Pop();//删除堆中元素
    cout << q.Size() << endl;
    cout << q.Top() << endl;
    if (!q.Empty())//判空
        cout << "非空" << endl;
    else
        cout << "空" << endl;

    q.Pop();
    cout << q.Size() << endl;
    cout << q.Top() << endl;

    q.Pop();//堆中只有一个元素
    cout << q.Size() << endl;
    cout << q.Top() << endl;
    if (!q.Empty())
        cout << "非空" << endl;
    else
        cout << "空" << endl;
    q.Pop();//空堆
    cout << q.Size() << endl;
    cout << q.Top() << endl;
    if (!q.Empty())
        cout << "非空" << endl;
    else
        cout << "空" << endl;
}