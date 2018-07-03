template<class T>
class Less//Ð¡¶Ñ
{
public:
    bool operator()(const T&left, const T&right)
    {
        return left < right;
    }
};

template<class T>
class Great//´ó¶Ñ
{
public:
    bool operator()(const T&left, const T&right)
    {
        return left > right;
    }
};