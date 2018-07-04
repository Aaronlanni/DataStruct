//二叉树结点的定义  
template<class T>  
struct BinTreeNode  
{  
    //构造函数  
    BinTreeNode(const T&data)  
    :_data(data)  
    , _pLeft(NULL)  
    , _pRight(NULL)  
    {}  

    BinTreeNode *_pLeft;  
    BinTreeNode *_pRight;  
    T _data;  
};
//二叉树的定义
template<class T>
class BinTree
{
    typedef BinTreeNode<T> Node;
    typedef BinTreeNode<T>* pNode ;
public:
    //构造函数
    BinTree()
        :_pRoot(NULL)
    {}
    BinTree(const T* array, size_t size, const T& invalid)
    {
        size_t index = 0;//防止常引用
        _CreateBinTree(_pRoot, array, size, index, invalid);//构造树
    }
    //拷贝构造函数
    BinTree(const BinTree& bt)
    {
        _pRoot = _CopyBinTree(bt._pRoot);
    }
    //赋值运算符重载
    BinTree& operator=(const BinTree& bt)
    {
        if (this != &bt)
        {
            //先销毁原来的树
            _DestroyBinTree(_pRoot);
            //拷贝现在的树
            _pRoot = _CopyBinTree(bt._pRoot);
        }
        return *this;
    }
private:
    //利用后序遍历
    void _DestroyBinTree(PNode pRoot)
    {
        if (pRoot)
        {
            //销毁左子树
            _DestroyBinTree(pRoot->_pLeft);
            //销毁右子树
            _DestroyBinTree(pRoot->_pRight);
            //销毁根节点
            delete pRoot;
            pRoot = NULL;
        }
    }
    PNode _CopyBinTree(PNode pRoot)
    {
        PNode pNewNode = NULL;
        if (pRoot)
        {
            //拷贝根节点
            pNewNode = new Node(pRoot->_data);
            //拷贝根节点的左孩子
            if (pRoot->_pLeft)
                pNewNode->_pLeft = _CopyBinTree(pRoot->_pLeft);
            //拷贝根节点的右孩子
            if (pRoot->_pRight)
                pNewNode->_pRight = _CopyBinTree(pRoot->_pRight);
        }
        return pNewNode;
    }

    void _CreateBinTree(PNode& pRoot, const T* array, size_t size, size_t& index, const T& invalid)
    {
        if (index < size&&invalid != array[index])//防止无效值的插入
        {
            //创建根节点
            pRoot = new Node(array[index]);
            //创建左子树-
            _CreateBinTree(pRoot->_pLeft, array, size, ++index, invalid);
            //创建右子树
            _CreateBinTree(pRoot->_pRight, array, size, ++index, invalid);
        }
    }

private:
    PNode _pRoot;
};