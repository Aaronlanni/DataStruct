#pragma once
#include"Common.hpp"
#include<vector>
//构造哈希桶中的结点
template<class K,class V>
struct HashBucketNode
{
    K _key;
    V _value;
    HashBucketNode<K, V>* _pNext;

    HashBucketNode(const K&key, const V&value)
        :_key(key)
        , _value(value)
        , _pNext(NULL)
    {}
};
//对哈希进行声明
template<class K, class V, class KeyToInt>
class HashBucket;

//加迭代器,对指针进行封装
template<class K, class V, class KeyToInt = KeyToIntDef<int> >
class HashBucketIterator
{
    typedef HashBucketNode<K, V> Node;
    typedef HashBucketNode<K, V>* pNode;
    typedef HashBucketIterator<K,V,KeyToInt> Self;


public:
    HashBucketIterator()
        :_pCur(NULL)
        , _ht(NULL)
    {}

    HashBucketIterator(const pNode pCur,HashBucket<K,V,KeyToInt>* ht)
        :_pCur(pCur)
        , _ht(ht)
    {}

    HashBucketIterator(Self & s)
        :_pCur(s._pCur)
        , _ht(s._ht)
    {}

    pair<K,V> operator*()
    {
        return make_pair(_pCur->_key, _pCur->_value);
    }
    pair<K, V>* operator->()
    {
        return &(operator*());
    }
    //单链表，因此没有--操作
    Self& operator++()
    {
        Next();
        return *this;
    }
    Self operator++(int)
    {
        Self tmp(*this);
        Next();
        return tmp;
    }

    bool operator!=(const Self&s)
    {
        return !(*this == s);
    }
    bool operator==(const Self&s)
    {
        return ((_pCur == s._pCur) && (_ht == s._ht));
    }
private:
    void Next()
    {
        //如果当前桶中的元素不是最后一个
        if (_pCur->_pNext)
            _pCur = _pCur->_pNext;

        //当前桶中的元素是最后一个，计算下一个桶，找下一个非空桶
        else
        {
            size_t BucketNo = _ht->Func(_pCur->_key) + 1;//计算下一个桶
            for (; BucketNo < (_ht->_hashtable.capacity()); ++BucketNo)
            {
                //当前桶如果存在
                if (_ht->_hashtable[BucketNo])
                {
                    _pCur = _ht->_hashtable[BucketNo];
                    return;
                }       
            }
            _pCur = NULL;//走到最后一个非空桶
        }
        return;
    }
public:
    pNode _pCur;
    HashBucket<K, V, KeyToInt>*  _ht;//将哈希桶中的元素引入到迭代器中，从而使得迭代器与哈希桶关联
};
//哈希桶
template<class K, class V, class KeyToInt = KeyToIntDef<int> >
class HashBucket
{
    typedef HashBucketNode<K, V> Node;
    typedef Node* pNode;

public:
    friend class HashBucketIterator<K, V, KeyToInt>;
    typedef HashBucketIterator<K, V, KeyToInt> Iterator;
public:
    //加迭代器
    Iterator Begin()//将哈希桶与迭代器相关联
    {
        //从第一个桶开始，遍历整个桶
        for (size_t BucketNo = 0; BucketNo < _hashtable.capacity(); ++BucketNo)
        {
            if (_hashtable[BucketNo])
                return Iterator(_hashtable[BucketNo], this);
        }
        return Iterator(NULL, this);//如果走出来，整个桶为空，则返回空即可。
    }

    Iterator End()
    {
        return Iterator(NULL, this);
    }

public:
    HashBucket(size_t capacity = 10)
    {
        capacity = GetNextPrime(capacity);
        _hashtable.resize(capacity);//开辟空间
        _size = 0;
    }
    //######################插入删除######################
    //唯一元素的插入
    pair<Iterator, bool> UniqueInsert(const K&key, const V&value)
    {
        CapacityCheck();
        size_t BuckNo = Func(key);//找到对应的桶
        pNode pCur = _hashtable[BuckNo];
        //创建新的结点
        pNode pNewNode = new Node(key, value);
        while (pCur)
        {
            //遍历对应桶的所有元素
            if (pCur->_key == key)
                return make_pair(Iterator(pCur, this), false);

            pCur = pCur->_pNext;
        }
        //走出来之后，没有与之相同的元素，则进行插入
        pNewNode->_pNext = _hashtable[BuckNo];
        _hashtable[BuckNo] = pNewNode;
        _size++;
        return make_pair(Iterator(pCur, this), true);
    }

    //重复性元素的插入
    pair<Iterator,bool> EqualInsert(const K&key, const V&value)
    {
        CapacityCheck();
        size_t BuckNo = Func(key);//找到对应的桶
        //创建新的结点
        pNode pNewNode = new Node(key, value);
        //插入
        pNewNode->_pNext = _hashtable[BuckNo];
        _hashtable[BuckNo] = pNewNode;
        _size++;
        return pair<Iterator, bool>(Iterator(pNewNode, this), true);//make_pair的构造函数,此处先去构造迭代器，然后才能将迭代器返回
    }

    //唯一性元素的删除
    Iterator UniqueDelete(const K&key)
    {
        size_t BuckNo = Func(key);//找到对应的桶
        pNode pCur = _hashtable[BuckNo];
        pNode Pre = NULL;
        while (pCur)
        {
            //当找到这个唯一性的元素之时，则删除
            if (pCur->_key == key)
            {
                //当待删除结点为头结点
                if (pCur == _hashtable[BuckNo])
                {
                    _hashtable[BuckNo] = pCur->_pNext;
                    delete pCur;
                    pCur = NULL;
                    _size--;
                    return Iterator(Pre, this);
                }
                else
                {
                    Pre->_pNext = pCur->_pNext;
                    delete pCur;
                    pCur = NULL;
                    _size--;
                    return Iterator(Pre, this);
                }
            }
            else
            {
                Pre = pCur;
                pCur = pCur->_pNext;
            }
        }
        return Iterator(NULL, this);
    }

    //重复性元素的删除(返回删除元素的个数）
    size_t EqualDelete(const K&key)
    {
        size_t BuckNo = Func(key);//找到对应的桶
        pNode pCur = _hashtable[BuckNo];
        pNode Pre = NULL;
        int OldSize = _size;
        while (pCur)
        {
            //当找到这个元素之时，则删除
            if (pCur->_key == key)
            {
                //当待删除结点为头结点
                if (pCur == _hashtable[BuckNo])
                {
                    _hashtable[BuckNo] = pCur->_pNext;
                    delete pCur;
                    pCur = NULL;
                    _size--;
                    pCur = _hashtable[BuckNo];
                }
                else
                {
                    Pre->_pNext = pCur->_pNext;
                    delete pCur;
                    pCur = NULL;
                    _size--;
                    pCur = Pre->_pNext;

                }
            }
            else
            {
                Pre = pCur;
                pCur = pCur->_pNext;
            }

        }
        if (OldSize == _size)
            return 0;
        else
            return OldSize - _size;
    }

    //######################查找######################
    //返回某个元素所在的桶号
    Iterator Find(const K&key)
    {
        size_t BuckNo = Func(key);//找到对应的桶
        pNode pCur = _hashtable[BuckNo];
        while (pCur)
        {
            if (pCur->_key == key)
                return Iterator(pCur, this);
            pCur = pCur->_pNext;
        }
        return Iterator(NULL, this);
    }
    const Iterator Find(const K&key)const
    {
        size_t BuckNo = Func(key);//找到对应的桶
        pNode pCur = _hashtable[BuckNo];
        while (pCur)
        {
            if (pCur->_key == key)
                return Iterator(pCur, this);
            pCur = pCur->_pNext;
        }
        return Iterator(NULL, this);
    }

    //######################其他######################
    bool Empty()const
    {
        return _size == 0;
    }


    void Clear()
    {
        size_t capacity = _hashtable.capacity();
        for (size_t BuckNo = 0; BuckNo < capacity; ++BuckNo)
        {
            pNode pCur = _hashtable[BuckNo];
            while (pCur)
            {
                //头删
                _hashtable[BuckNo] = pCur->_pNext;
                delete pCur;
                pCur = NULL;
                _size--;
                pCur = _hashtable[BuckNo];
            }
        }
    }


    //返回哈希表中指定key的元素的总个数
    size_t KeySize(const K&key)const
    {
        int count = 0;

        size_t BucketNo = Func(key);
        pNode pCur = _hashtable[BucketNo];

        while (pCur)
        {
            if (pCur->_key == key)
            {
                ++count;
            }

            pCur = pCur->_pNext;
        }
        return count;
    }
    //返回哈希表中桶的个数
    size_t BucketCount()const
    {
        return _hashtable.capacity();
    }
    //桶中元素的总个数
    size_t Size()const
    {
        return _size;
    }
    //当前桶中结点的个数
    size_t BucketSize(size_t BucketNo)
    {
        pNode pCur = _hashtable[BucketNo];
        size_t count = 0;
        while (pCur)
        {
            ++count;
            pCur = pCur->_pNext;
        }
        return count;
    }
    //找到，返回，没有找到，返回缺省值----从而封装[]
    V& FindOfInsert(const K&key)
    {
        size_t BuckNo = Func(key);//找到对应的桶
        pNode pCur = _hashtable[BuckNo];
        while (pCur)
        {
            if (pCur->_key == key)
                return pCur->_value;
            pCur = pCur->_pNext;
        }
        pair<Iterator, bool> tmp = UniqueInsert(key, V());
        return (*(tmp.first)).second;//拿出键值对，从而将其的中的value拿出来

    }
    V operator[](const K&key)
    {
        return FindOfInsert(key);
    }

    ~HashBucket()
    {
        Clear();
    }

private:
    void Swap(HashBucket<K, V,KeyToInt> ht)
    {
        swap(_hashtable, ht._hashtable);
        swap(_size, ht._size);
    }

    void CapacityCheck()
    {
        size_t capacity = _hashtable.capacity();
        if (_size == capacity)
        {
            //创建新的哈希桶
            HashBucket<K, V,KeyToInt> newHt(GetNextPrime(capacity));
            //将旧空间中的元素插入到新空间中
            for (size_t BuckNo = 0; BuckNo < capacity; ++BuckNo)
            {
                pNode pCur = _hashtable[BuckNo];
                while (pCur)
                {
                    newHt.UniqueInsert(pCur->_key, pCur->_key);
                    pCur = pCur->_pNext;
                }
            }
            Swap(newHt);
        }
    }
private:
    size_t Func(const K&key)
    {
        return KeyToInt()(key) % _hashtable.capacity();
    }
private:
    vector<pNode> _hashtable;
    size_t _size;

};

void TestBucket()
{
    HashBucket<int, int> ht;
    ht.EqualInsert(1, 1);
    ht.EqualInsert(2, 2);
    ht.EqualInsert(3, 3);
    ht.EqualInsert(4, 4);
    HashBucket<int, int >::Iterator it = ht.Begin();
    cout << ht.Size() << endl;
    HashBucket<int, int >::Iterator ret = ht.Find(3);
    cout << (*ret).first << endl;
    if (ht.Empty())
        cout << "kong" << endl;
    else
    {
        while (it != ht.End())
        {
            cout << (*it).first << " " <<it->second<<"  ";
            it++;
        }
    }

    ht.EqualDelete(1);
    cout << ht.Size() << endl;

    if (ht.Empty())
        cout << "kong" << endl;
    else
        cout << "feikong" << endl;

    ht.UniqueInsert(1, 1);
    ht.UniqueInsert(2, 2);
    ht.UniqueInsert(5, 5);
    cout << ht.Size() << endl;

    if (ht.Empty())
        cout << "kong" << endl;
    else
        cout << "feikong" << endl;
    ht.UniqueDelete(2);
    cout << ht.Size() << endl;

    if (ht.Empty())
        cout << "kong" << endl;
    else
        cout << "feikong" << endl;

    ht.Clear();
    cout << ht.Size() << endl;


    if (ht.Empty())
        cout << "kong" << endl;
    else
        cout << "feikong" << endl;
}

void Test2Bucket()
{
    HashBucket<string, string,StringToInt > ht;
    ht.EqualInsert("1111", "1111");
    ht.EqualInsert("2222", "2222");
    ht.EqualInsert("3333", "3333");
    ht.EqualInsert("你好 ", "你好");
    ht.EqualInsert("abcd", "abcd");
    //cout << ht.Find(("你好")) << endl;//有问题
    cout << ht.Size() << endl;
    if (ht.Empty())
        cout << "kong" << endl;
    else
        cout << "feikong" << endl;
    HashBucket<string, string, StringToInt>::Iterator it = ht.Begin();
    if (ht.Empty())
        cout << "kong" << endl;
    else
    {
        while (it != ht.End())
        {
            cout << (*it).first.c_str() << " " << (*it).second.c_str() << "  ";
            it++;
        }
    }
}