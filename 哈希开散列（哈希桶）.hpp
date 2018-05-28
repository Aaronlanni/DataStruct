#pragma once
#include"Common.hpp"
#include<vector>
//�����ϣͰ�еĽ��
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
//�Թ�ϣ��������
template<class K, class V, class KeyToInt>
class HashBucket;

//�ӵ�����,��ָ����з�װ
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
    //���������û��--����
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
        //�����ǰͰ�е�Ԫ�ز������һ��
        if (_pCur->_pNext)
            _pCur = _pCur->_pNext;

        //��ǰͰ�е�Ԫ�������һ����������һ��Ͱ������һ���ǿ�Ͱ
        else
        {
            size_t BucketNo = _ht->Func(_pCur->_key) + 1;//������һ��Ͱ
            for (; BucketNo < (_ht->_hashtable.capacity()); ++BucketNo)
            {
                //��ǰͰ�������
                if (_ht->_hashtable[BucketNo])
                {
                    _pCur = _ht->_hashtable[BucketNo];
                    return;
                }       
            }
            _pCur = NULL;//�ߵ����һ���ǿ�Ͱ
        }
        return;
    }
public:
    pNode _pCur;
    HashBucket<K, V, KeyToInt>*  _ht;//����ϣͰ�е�Ԫ�����뵽�������У��Ӷ�ʹ�õ��������ϣͰ����
};
//��ϣͰ
template<class K, class V, class KeyToInt = KeyToIntDef<int> >
class HashBucket
{
    typedef HashBucketNode<K, V> Node;
    typedef Node* pNode;

public:
    friend class HashBucketIterator<K, V, KeyToInt>;
    typedef HashBucketIterator<K, V, KeyToInt> Iterator;
public:
    //�ӵ�����
    Iterator Begin()//����ϣͰ������������
    {
        //�ӵ�һ��Ͱ��ʼ����������Ͱ
        for (size_t BucketNo = 0; BucketNo < _hashtable.capacity(); ++BucketNo)
        {
            if (_hashtable[BucketNo])
                return Iterator(_hashtable[BucketNo], this);
        }
        return Iterator(NULL, this);//����߳���������ͰΪ�գ��򷵻ؿռ��ɡ�
    }

    Iterator End()
    {
        return Iterator(NULL, this);
    }

public:
    HashBucket(size_t capacity = 10)
    {
        capacity = GetNextPrime(capacity);
        _hashtable.resize(capacity);//���ٿռ�
        _size = 0;
    }
    //######################����ɾ��######################
    //ΨһԪ�صĲ���
    pair<Iterator, bool> UniqueInsert(const K&key, const V&value)
    {
        CapacityCheck();
        size_t BuckNo = Func(key);//�ҵ���Ӧ��Ͱ
        pNode pCur = _hashtable[BuckNo];
        //�����µĽ��
        pNode pNewNode = new Node(key, value);
        while (pCur)
        {
            //������ӦͰ������Ԫ��
            if (pCur->_key == key)
                return make_pair(Iterator(pCur, this), false);

            pCur = pCur->_pNext;
        }
        //�߳���֮��û����֮��ͬ��Ԫ�أ�����в���
        pNewNode->_pNext = _hashtable[BuckNo];
        _hashtable[BuckNo] = pNewNode;
        _size++;
        return make_pair(Iterator(pCur, this), true);
    }

    //�ظ���Ԫ�صĲ���
    pair<Iterator,bool> EqualInsert(const K&key, const V&value)
    {
        CapacityCheck();
        size_t BuckNo = Func(key);//�ҵ���Ӧ��Ͱ
        //�����µĽ��
        pNode pNewNode = new Node(key, value);
        //����
        pNewNode->_pNext = _hashtable[BuckNo];
        _hashtable[BuckNo] = pNewNode;
        _size++;
        return pair<Iterator, bool>(Iterator(pNewNode, this), true);//make_pair�Ĺ��캯��,�˴���ȥ�����������Ȼ����ܽ�����������
    }

    //Ψһ��Ԫ�ص�ɾ��
    Iterator UniqueDelete(const K&key)
    {
        size_t BuckNo = Func(key);//�ҵ���Ӧ��Ͱ
        pNode pCur = _hashtable[BuckNo];
        pNode Pre = NULL;
        while (pCur)
        {
            //���ҵ����Ψһ�Ե�Ԫ��֮ʱ����ɾ��
            if (pCur->_key == key)
            {
                //����ɾ�����Ϊͷ���
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

    //�ظ���Ԫ�ص�ɾ��(����ɾ��Ԫ�صĸ�����
    size_t EqualDelete(const K&key)
    {
        size_t BuckNo = Func(key);//�ҵ���Ӧ��Ͱ
        pNode pCur = _hashtable[BuckNo];
        pNode Pre = NULL;
        int OldSize = _size;
        while (pCur)
        {
            //���ҵ����Ԫ��֮ʱ����ɾ��
            if (pCur->_key == key)
            {
                //����ɾ�����Ϊͷ���
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

    //######################����######################
    //����ĳ��Ԫ�����ڵ�Ͱ��
    Iterator Find(const K&key)
    {
        size_t BuckNo = Func(key);//�ҵ���Ӧ��Ͱ
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
        size_t BuckNo = Func(key);//�ҵ���Ӧ��Ͱ
        pNode pCur = _hashtable[BuckNo];
        while (pCur)
        {
            if (pCur->_key == key)
                return Iterator(pCur, this);
            pCur = pCur->_pNext;
        }
        return Iterator(NULL, this);
    }

    //######################����######################
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
                //ͷɾ
                _hashtable[BuckNo] = pCur->_pNext;
                delete pCur;
                pCur = NULL;
                _size--;
                pCur = _hashtable[BuckNo];
            }
        }
    }


    //���ع�ϣ����ָ��key��Ԫ�ص��ܸ���
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
    //���ع�ϣ����Ͱ�ĸ���
    size_t BucketCount()const
    {
        return _hashtable.capacity();
    }
    //Ͱ��Ԫ�ص��ܸ���
    size_t Size()const
    {
        return _size;
    }
    //��ǰͰ�н��ĸ���
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
    //�ҵ������أ�û���ҵ�������ȱʡֵ----�Ӷ���װ[]
    V& FindOfInsert(const K&key)
    {
        size_t BuckNo = Func(key);//�ҵ���Ӧ��Ͱ
        pNode pCur = _hashtable[BuckNo];
        while (pCur)
        {
            if (pCur->_key == key)
                return pCur->_value;
            pCur = pCur->_pNext;
        }
        pair<Iterator, bool> tmp = UniqueInsert(key, V());
        return (*(tmp.first)).second;//�ó���ֵ�ԣ��Ӷ�������е�value�ó���

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
            //�����µĹ�ϣͰ
            HashBucket<K, V,KeyToInt> newHt(GetNextPrime(capacity));
            //���ɿռ��е�Ԫ�ز��뵽�¿ռ���
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
    ht.EqualInsert("��� ", "���");
    ht.EqualInsert("abcd", "abcd");
    //cout << ht.Find(("���")) << endl;//������
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