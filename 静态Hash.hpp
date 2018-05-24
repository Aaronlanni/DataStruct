#define MAX_SIZE 10

typedef enum State{ EMPTY, DETELE, EXIST };

template<class K>
struct Elem
{
    K _key;
    State _state;
};

template<class K,bool IsLine=true>
class HashTable
{
public:
    HashTable()
    {
        //清空每个位置
        for (int i = 0; i < MAX_SIZE; ++i)
        {
            _hashtable[i]._state = EMPTY;
        }
        _size = 0;
    }
    //插入元素
    bool Insert(const K&key)
    {
        //负载因子
        if (_size * 10 / MAX_SIZE>7)
            return false;
        size_t HashAdder = Func(key);
        size_t stateAdder = HashAdder;
        size_t i = 0;
        //找空位置
        while (_hashtable[HashAdder]._state != EMPTY)
        {
            if (_hashtable[HashAdder]._state == EXIST&&_hashtable[HashAdder]._key == key)
                return false;

            if (IsLine)
                LineCheck(HashAdder);
            else
                SecondCheck(HashAdder, i++);
            if (HashAdder == stateAdder)
                return false;
        }
        //插入元素
        _hashtable[HashAdder]._key = key;
        _hashtable[HashAdder]._state = EXIST;
        ++_size;
        return true;
    }
    //查找元素
    int Find(const K&key)
    {
        //在哈希表中找对应的位置
        size_t HashAdder = Func(key);
        size_t i = 0;
        //找空位置
        while (_hashtable[HashAdder]._state != EMPTY)
        {
            if (_hashtable[HashAdder]._key == key)
                return _hashtable[HashAdder]._key;

            if (IsLine)
                LineCheck(HashAdder);
            else
                SecondCheck(HashAdder, i++);
        }
        return -1;
    }
    //删除元素
    bool DElete(const K&key)
    {
        size_t HashAdder = Func(key);
        int ret = Find(key);
        if (-1 != ret)
        {
            _hashtable[HashAdder]._state = DETELE;
            --_size;
            return true;
        }
        return false;
    }
    size_t Size()
    {
        return _size;
    }
    bool Empty()
    {
        return _size == 0;
    }
private:
    //线性探测
    void LineCheck(size_t& HashAdder)
    {
        ++HashAdder;
        if (HashAdder >= MAX_SIZE)
            HashAdder = 0;
    }
    //二次探测
    void SecondCheck(size_t HashAdder,size_t i)
    {
        HashAdder = HashAdder + ((i << 1) + 1);
        if (HashAdder >= MAX_SIZE)
            HashAdder %= MAX_SIZE;
    }
private:
    //哈希函数
    size_t Func(const K&key)
    {
        return key%MAX_SIZE;
    }
private:
    Elem<K> _hashtable[MAX_SIZE];
    size_t _size;
};