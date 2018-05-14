#pragma once
#include<iostream>
using namespace std;
#include<assert.h>
#if 1
template<class K,class V>
struct BSTreeNode
{
	BSTreeNode(const K& key, const V& value)
	:_pLeft(NULL)
	, _pRight(NULL)
	, _key(key)
	, _value(value)
	{}

	BSTreeNode<K, V>* _pLeft;
	BSTreeNode<K, V>* _pRight;
	K _key;
	V _value;
};

template<class K,class V>
class BSTree
{
	typedef BSTreeNode<K, V> Node;
	typedef BSTreeNode<K, V>* pNode;

public:
	BSTree()
		:_pRoot(NULL)
	{}

	bool Insert(const K& key, const V& value)
	{
		pNode pCur = _pRoot;
		pNode pParent = NULL;
		pNode pNewNode = new Node(key, value);
		//空树--直接插入
		if (pCur == NULL)
		{
			_pRoot = pNewNode;
			return true;
		}

		//找插入的位置
		while (pCur)
		{
			if (key == pCur->_key)
				return false;
			else if (key < pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else
			{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
		}
		//插入元素
		if (key < pParent->_key)
			pParent->_pLeft = pNewNode;
		else
			pParent->_pRight = pNewNode;

		return true;
	}
	//递归
	void Insert1(const K& key, const V& value)
	{
		_Insert1(_pRoot, key, value);
	}
	//查找某一个元素
	bool Find(const K&key)
	{
		//空树
		if (_pRoot == NULL)
			return false;
		//非空树
		pNode pCur = _pRoot;
		while (pCur)
		{
			if (key == pCur->_key)
				return true;
			else if (key > pCur->_key)
				pCur = pCur->_pRight;
			else
				pCur = pCur->_pLeft;
		}
		return false;
	}
	//递归
	bool Find1(const K&key)
	{
		//空树
		if (_pRoot == NULL)
			return true;
		//非空树
		_Find1(_pRoot, key);

	}
	//获取最小的元素,一直往其左边走
	K LastMost()const
	{
		assert(_pRoot);//判断是否为空树

		pNode pCur = _pRoot;
		while (pCur->_pLeft)
		{
			pCur = pCur->_pLeft;
		}
		return pCur->_key;
	}

	//获取最大的元素
	K RightMost()const
	{
		assert(_pRoot);//判断是否为空树

		pNode pCur = _pRoot;
		while (pCur->_pRight)
		{
			pCur = pCur->_pRight;
		}
		return pCur->_key;
	}

	void Pop(const K&key)
	{
		//空树
		if (_pRoot == NULL)
			return;
		//非空树
		pNode pDel = _pRoot;
		pNode pDParent = NULL;
		//找待删除的结点
		while (pDel)
		{
			if (key == pDel->_key)
				break;
			else if (key > pDel->_key)
			{
				pDParent = pDel;
				pDel = pDel->_pRight;
			}
			else
			{
				pDParent = pDel;
				pDel = pDel->_pLeft;
			}
		}
		//删除的结点不在树中
		if (pDel == NULL)
		{
			return;
		}

		//删除结点
		//只有左孩子，此种情况包含两个孩子都没有
		if (NULL == pDel->_pRight)
		{
			//判断待删结点是否为根节点
			if (pDel == _pRoot)//左单支
			{
				_pRoot = pDel->_pLeft;
				
			}
			else
			{
				//待删结点在双亲结点的左孩子上
				if (pDParent->_pLeft == pDel)
				{
					pDParent->_pLeft = pDel->_pLeft;
					
				}
				//待删结点在双亲结点的右孩子上
				else
				{
					pDParent->_pRight = pDel->_pLeft;
					
				}
			}
		}

		//只有右孩子，此种情况包含两个孩子都没有
		else if (NULL == pDel->_pLeft)
		{
			if (pDel == _pRoot)//右单支
			{
				_pRoot = pDel->_pRight;
				
			}
			else
			{
				if (pDParent->_pLeft == pDel)
				{
					pDParent->_pLeft = pDel->_pRight;
					
				}
				else
				{
					pDParent->_pRight = pDel->_pRight;
					
				}
			}
		}
		//两个孩子都有
		else
		{
			//找替代结点，在右子树中，找待删除结点的中序遍历下的第一个结点,右子树中序遍历下的第一个结点
			pNode pReplaceNode = pDel->_pRight;
			pDParent = pDel;
			//找出替代结点
			while (pReplaceNode->_pLeft)
			{
				pDParent = pReplaceNode;
				pReplaceNode = pReplaceNode->_pLeft;
			}
			//交换待删结点与替代结点,一般的替代结点为只有右子树或者叶子结点
			pDel->_key = pReplaceNode->_key;
			pDel->_value = pReplaceNode->_value;
			pDel = pReplaceNode;
			//删除结点

			if (pDParent->_pLeft == pDel)
			{
				pDParent->_pLeft = pDel->_pRight;
			}
			else
			{
				pDParent->_pRight = pDel->_pRight;
			}
		}
		delete pDel;
	}


	void InOrder()
	{
		cout << "InOrder:" << endl;
		_InOrder(_pRoot);
	}

	//将二叉搜索树转换为一条双向链表，并且有序（类似一个链表面试题）
	pNode BST2List()
	{
		pNode pHead = pRoot;
		//空树
		if (_pRoot == NULL)
			return NULL;

		//先找到头结点
		while (pHead->_pLeft)
		{
			pHead = pHead->_pLeft;//找到头结点
		}
		pNode prev = NULL;
		_BST2List(_pRoot, prev);
		return pHead;
	}
	//递归
private:
	bool _Find1(pNode pRoot, const K&key)
	{
		if (pRoot == NULL)
			return false;		
		if (key == pRoot->_key)
			return true;
		//左子树
		else if (key < pRoot->_pLeft->_key)
			_Find1(pRoot->_pLeft, key);
		//右子树
		else
			_Find1(pRoot->_pRight,key);
	}
	bool _Insert1(pNode& pRoot, const K&key, const V&value)
	{
		pNode pNewNode = new Node(key, value);
		if (pRoot == NULL)
		{
			pRoot = pNewNode;
			return true;
		}

		if (pRoot == NULL)
			return false;
		if (pNewNode->_key == pRoot->_key)
			return false;

		if (pRoot->_key > pNewNode->_key)
			_Insert1(pRoot->_pLeft, key, value);

		else
			_Insert1(pRoot->_pRight, key, value);
	}
private:
	void _InOrder(pNode pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << "<" << pRoot->_key << "," << pRoot->_value << ">" << endl;;
			_InOrder(pRoot->_pRight);
		}
		
	}

	pNode _BST2List(pNode& pRoot, pNode& prev)
	{
		_BST2List(pRoot->_pLeft, prev);//左子树
		pRoot->_pLeft = prev;//根节点，左指针域
		if (prev)//处理右指针域
		{
			prev->_pRight = pRoot;
		}
		prev = pRoot;
		_BST2List(pRoot->_pRight, prev);
	}
private:
	pNode _pRoot;
};

#endif







