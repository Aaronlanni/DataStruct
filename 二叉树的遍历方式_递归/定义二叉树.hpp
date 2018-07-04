//���������Ķ���  
template<class T>  
struct BinTreeNode  
{  
    //���캯��  
    BinTreeNode(const T&data)  
    :_data(data)  
    , _pLeft(NULL)  
    , _pRight(NULL)  
    {}  

    BinTreeNode *_pLeft;  
    BinTreeNode *_pRight;  
    T _data;  
};
//�������Ķ���
template<class T>
class BinTree
{
    typedef BinTreeNode<T> Node;
    typedef BinTreeNode<T>* pNode ;
public:
    //���캯��
    BinTree()
        :_pRoot(NULL)
    {}
    BinTree(const T* array, size_t size, const T& invalid)
    {
        size_t index = 0;//��ֹ������
        _CreateBinTree(_pRoot, array, size, index, invalid);//������
    }
    //�������캯��
    BinTree(const BinTree& bt)
    {
        _pRoot = _CopyBinTree(bt._pRoot);
    }
    //��ֵ���������
    BinTree& operator=(const BinTree& bt)
    {
        if (this != &bt)
        {
            //������ԭ������
            _DestroyBinTree(_pRoot);
            //�������ڵ���
            _pRoot = _CopyBinTree(bt._pRoot);
        }
        return *this;
    }
private:
    //���ú������
    void _DestroyBinTree(PNode pRoot)
    {
        if (pRoot)
        {
            //����������
            _DestroyBinTree(pRoot->_pLeft);
            //����������
            _DestroyBinTree(pRoot->_pRight);
            //���ٸ��ڵ�
            delete pRoot;
            pRoot = NULL;
        }
    }
    PNode _CopyBinTree(PNode pRoot)
    {
        PNode pNewNode = NULL;
        if (pRoot)
        {
            //�������ڵ�
            pNewNode = new Node(pRoot->_data);
            //�������ڵ������
            if (pRoot->_pLeft)
                pNewNode->_pLeft = _CopyBinTree(pRoot->_pLeft);
            //�������ڵ���Һ���
            if (pRoot->_pRight)
                pNewNode->_pRight = _CopyBinTree(pRoot->_pRight);
        }
        return pNewNode;
    }

    void _CreateBinTree(PNode& pRoot, const T* array, size_t size, size_t& index, const T& invalid)
    {
        if (index < size&&invalid != array[index])//��ֹ��Чֵ�Ĳ���
        {
            //�������ڵ�
            pRoot = new Node(array[index]);
            //����������-
            _CreateBinTree(pRoot->_pLeft, array, size, ++index, invalid);
            //����������
            _CreateBinTree(pRoot->_pRight, array, size, ++index, invalid);
        }
    }

private:
    PNode _pRoot;
};