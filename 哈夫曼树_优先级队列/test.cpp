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

//�������ȼ�����
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
        //����Ƚ������˴�ʹ�õ�ԭ���ǣ��ڴ�Ҫ�Ƚϵ���Ȩֵ�Ĵ�С
        struct Less
        {
            bool operator()(pNode left, pNode right)
            {
                return left->_weight < right->_weight;
            }
        };

        priority_queue<pNode, vector<pNode>, Less> hp;
        //������Ԫ���ȷ��뵽����
        for (size_t i = 0; i < size; ++i)
        {
            if (array[i] != invalid)                
                hp.push(new HuffmanTreeNode<W>(array[i]));          
        }
        //����û��Ԫ�أ��նѣ�
        if (hp.empty())
            _pRoot = NULL;

        //���öѴ���Huffman��
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
        //�������
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