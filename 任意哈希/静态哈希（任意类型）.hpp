//���Դ�ȡ�ַ���
#include"Common.hpp"

//�����Ҫ��ȡ�ַ���������Ҫ����ȡ��ϣ��ַ��ʱ����Ҫת�������÷º���

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
        capacity = GetNextPrime(capacity);//��õĹ�ϣ��ĳ���
        _hashtable = new Elem<K>[capacity];
        _capacity = capacity;
        for (size_t i = 0; i < _capacity; ++i)
            _hashtable[i]._state = EMPTY;
        _size = 0;
    }
    //����Ԫ��
    bool Insert(const K&key)
    {
        CheckCapacity();
        size_t HashAdder = Func(key);
        size_t stateAdder = HashAdder;
        size_t i = 1;
        //�ҿ�λ��
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
        //����Ԫ��
        _hashtable[HashAdder]._key = key;
        _hashtable[HashAdder]._state = EXIST;
        ++_size;
        return true;
    }
    //����Ԫ��
    int Find(const K&key)
    {
        //�ڹ�ϣ�����Ҷ�Ӧ��λ��
        size_t HashAdder = Func(key);
        size_t i = 1;
        //��λ��
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

    //ɾ��Ԫ��
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
    //��������
    void Swap(HashTable<K,KeyToInt,IsLine>& ht)
    {
        swap(_hashtable, ht._hashtable);
        swap(_size, ht._size);
        swap(_capacity, ht._capacity);
    }
    //���ݺ���
    void CheckCapacity()
    {
        if (_size * 10 / _capacity >= 5)
        {
            size_t newCapacity = GetNextPrime(_capacity);
            HashTable<K,KeyToInt,IsLine> newHt(newCapacity);//�����µĹ�ϣ��
            //����Ԫ��
            for (size_t i = 0; i < _capacity; ++i)
            {
                if (_hashtable[i]._state == EXIST)
                    newHt.Insert(_hashtable[i]._key);
            }
            Swap(newHt);
        }
    }
    //����̽��
    void LineCheck(size_t& HashAdder)
    {
        ++HashAdder;
        if (HashAdder >= _capacity)
            HashAdder = 0;
    }
    //����̽��
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