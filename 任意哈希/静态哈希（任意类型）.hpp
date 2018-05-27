//可以存取字符串
#include"Common.hpp"

//如果需要存取字符串，则需要在求取哈希地址的时候，需要转换，利用仿函数

template<class K>
struct Elem
{
    K _key;
    State _state;
};

template<class K, class KeyToInt = KeyToIntDef<int>, bool IsLine = true>
class HashTable
{
public:
    HashTable(size_t capacity = 10)
    {
        capacity = GetNextPrime(capacity);//获得的哈希表的长度
        _hashtable = new Elem<K>[capacity];
        _capacity = capacity;
        for (size_t i = 0; i < _capacity; ++i)
            _hashtable[i]._state = EMPTY;
        _size = 0;
    }
    //插入元素
    bool Insert(const K&key)
    {
        CheckCapacity();
        size_t HashAdder = Func(key);
        size_t stateAdder = HashAdder;
        size_t i = 1;
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
        size_t i = 1;
        //找位置
        while (_hashtable[HashAdder]._state != EMPTY)
        {
            if (_hashtable[HashAdder]._state == EXIST)
            {
                if (_hashtable[HashAdder]._key == key)
                    return HashAdder;
            }

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

    ~HashTable()
    {
        if (_hashtable)
        {
            _capacity = 0;
            _size = 0;
            delete[] _hashtable;
        }
    }
private:
    //交换函数
    void Swap(HashTable<K,KeyToInt,IsLine>& ht)
    {
        swap(_hashtable, ht._hashtable);
        swap(_size, ht._size);
        swap(_capacity, ht._capacity);
    }
    //增容函数
    void CheckCapacity()
    {
        if (_size * 10 / _capacity >= 5)
        {
            size_t newCapacity = GetNextPrime(_capacity);
            HashTable<K,KeyToInt,IsLine> newHt(newCapacity);//创建新的哈希表
            //搬移元素
            for (size_t i = 0; i < _capacity; ++i)
            {
                if (_hashtable[i]._state == EXIST)
                    newHt.Insert(_hashtable[i]._key);
            }
            Swap(newHt);
        }
    }
    //线性探测
    void LineCheck(size_t& HashAdder)
    {
        ++HashAdder;
        if (HashAdder >= _capacity)
            HashAdder = 0;
    }
    //二次探测
    void SecondCheck(size_t HashAdder, size_t i)
    {
        HashAdder = HashAdder + ((i << 1) + 1);
        if (HashAdder >= _capacity)
            HashAdder %= _capacity;
    }
private:
    size_t Func(const K&key)
    {
        return KeyToInt()(key)%_capacity;
    }
private:
    Elem<K> * _hashtable;
    size_t _size;
    size_t _capacity;
};