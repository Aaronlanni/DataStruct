template < class T, class Container = vector<T>,
           class Compare = less<typename Container::value_type> > class priority_queue;
#include<iostream>
using namespace std;
#include<queue>
#include<vector>

template<class W>
struct HuffmanTreeNode
{
    HuffmanTreeNode(const W&weight)
    :_pLeft(NULL)
    , _pRight(NULL)
    , _weight(weight)
    {}

    HuffmanTreeNode<W> *_pLeft;
    HuffmanTreeNode<W> *_pRight;
    W _weight;
};

//利用优先级队列
template<class W>
class HuffmanTree
{
    typedef HuffmanTreeNode<W> Node;
    typedef Node*pNode;
public:
    HuffmanTree()
        :_pRoot(NULL)
    {}

    HuffmanTree(W *array, size_t size,const W&invalid)
    {
        _CreatHuffmanTree(array, size, invalid);
    }

    ~HuffmanTree()
    {
        Destory(_pRoot);
    }
private:
    void _CreatHuffmanTree(W*array, size_t size, const W& invalid)
    {
        //定义比较器，此处使用的原因是：在此要比较的是权值的大小
        struct Less
        {
            bool operator()(pNode left, pNode right)
            {
                return left->_weight < right->_weight;
            }
        };

        priority_queue<pNode, vector<pNode>, Less> hp;
        //将所有元素先放入到堆中
        for (size_t i = 0; i < size; ++i)
        {
            if (array[i] != invalid)                
                hp.push(new HuffmanTreeNode<W>(array[i]));          
        }
        //堆中没有元素（空堆）
        if (hp.empty())
            _pRoot = NULL;

        //利用堆创建Huffman树
        while ((int)hp.size()>1)
        {
            pNode pLeft = hp.top();
            hp.pop();

            pNode pRight = hp.top();
            hp.pop();

            pNode parent = new HuffmanTreeNode<W>(pLeft->_weight + pRight->_weight);

            parent->_pLeft = pLeft;
            parent->_pRight = pRight;
            hp.push(parent);
        }
        _pRoot = hp.top();
    }

    void Destory(pNode pRoot)
    {
        //后序遍历
        pNode pCur = pRoot;
        if (pCur)
        {
            Destory(pCur->_pLeft);
            Destory(pCur->_pRight);
            delete pCur;
            pCur = NULL;
        }
    }
private:
    pNode _pRoot;
};