//用两个队列实现一个栈
template<class T>
class Stack
{
public:
    Stack()     
    {
        q1_used = true;//作为入队列
        q2_used = false;
    }
    void Push(const T&data)
    {
        if (q1_used == true)
        {
            q1.push(data);
            return;
        }
        if (q2_used == true)
        {
            q2.push(data);
            return;
        }

    }

    void Pop()
    {
        if (!q1.empty())
        {
            while (q1.front() != q1.back())
            {
                q2.push(q1.front());
                q1.pop();
            }
            q1.pop();
            q1_used = false;
            q2_used = true;
            return;
        }
        if (!q2.empty())
        {
            while (q2.front() != q2.back())
            {
                q1.push(q2.front());
                q2.pop();
            }
            q2.pop();
            q1_used = true;
            q2_used = false;
            return;
        }
        return;
    }

    T Top()
    {
        if (!q1.empty())
            return q1.back();
        if (!q2.empty())
            return q2.back();
        return NULL;
    }
    size_t Size()
    {
        if (!q1.empty())
        {
            return q1.size();
        }
        if (!q2.empty())
        {
            return q2.size();
        }
        return 0;
    }
    bool Empty()
    {
        if (q1.empty() && q2.empty())
            return true;
        else
            false;
    }
private:
    queue<T> q1;
    bool q1_used;
    queue<T> q2;
    bool q2_used;
};
