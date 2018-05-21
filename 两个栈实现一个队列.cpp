//用两个栈实现一个队列
template<class T>
class Queue
{
public:
    Queue()
    {}

    void Push(const T&data)
    {
        s1.push(data);
    }

    void Pop()
    {
        if (!s2.empty())
        {
            s2.pop();
            return;
        }

        while (!s1.empty())
        {
            while (s1.size() != 0)
            {
                s2.push(s1.top());
                s1.pop();
            }
            s2.pop();
        }
    }

    T Front()
    {
        if (!s2.empty())
        {
            return s2.top();
        }
        while (!s1.empty())
        {
            s2.push(s1.top());
            s1.pop();
        }
        return s2.top();
    }
    T Back()
    {
        if (!s1.empty())
        {
            return s1.top();
        }
        while (!s2.empty())
        {
            s1.push(s2.top());
            s2.pop();
        }
        return s1.top();
    }

    size_t Size()
    {
        return s1.size() + s2.size();
    }

    bool Empty()
    {
        if (s1.empty() && s2.empty())
            return true;
        else
            return false;
    }
private:
    stack<T> s1;
    stack<T> s2;
};