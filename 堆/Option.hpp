template<class T>
class Less//С��
{
public:
    bool operator()(const T&left, const T&right)
    {
        return left < right;
    }
};

template<class T>
class Great//���
{
public:
    bool operator()(const T&left, const T&right)
    {
        return left > right;
    }
};