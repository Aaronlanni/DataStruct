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
		//����--ֱ�Ӳ���
		if (pCur == NULL)
		{
			_pRoot = pNewNode;
			return true;
		}

		//�Ҳ����λ��
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
		//����Ԫ��
		if (key < pParent->_key)
			pParent->_pLeft = pNewNode;
		else
			pParent->_pRight = pNewNode;

		return true;
	}
	//�ݹ�
	void Insert1(const K& key, const V& value)
	{
		_Insert1(_pRoot, key, value);
	}
	//����ĳһ��Ԫ��
	bool Find(const K&key)
	{
		//����
		if (_pRoot == NULL)
			return false;
		//�ǿ���
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
	//�ݹ�
	bool Find1(const K&key)
	{
		//����
		if (_pRoot == NULL)
			return true;
		//�ǿ���
		_Find1(_pRoot, key);

	}
	//��ȡ��С��Ԫ��,һֱ���������
	K LastMost()const
	{
		assert(_pRoot);//�ж��Ƿ�Ϊ����

		pNode pCur = _pRoot;
		while (pCur->_pLeft)
		{
			pCur = pCur->_pLeft;
		}
		return pCur->_key;
	}

	//��ȡ����Ԫ��
	K RightMost()const
	{
		assert(_pRoot);//�ж��Ƿ�Ϊ����

		pNode pCur = _pRoot;
		while (pCur->_pRight)
		{
			pCur = pCur->_pRight;
		}
		return pCur->_key;
	}

	void Pop(const K&key)
	{
		//����
		if (_pRoot == NULL)
			return;
		//�ǿ���
		pNode pDel = _pRoot;
		pNode pDParent = NULL;
		//�Ҵ�ɾ���Ľ��
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
		//ɾ���Ľ�㲻������
		if (pDel == NULL)
		{
			return;
		}

		//ɾ�����
		//ֻ�����ӣ�������������������Ӷ�û��
		if (NULL == pDel->_pRight)
		{
			//�жϴ�ɾ����Ƿ�Ϊ���ڵ�
			if (pDel == _pRoot)//��֧
			{
				_pRoot = pDel->_pLeft;
				
			}
			else
			{
				//��ɾ�����˫�׽���������
				if (pDParent->_pLeft == pDel)
				{
					pDParent->_pLeft = pDel->_pLeft;
					
				}
				//��ɾ�����˫�׽����Һ�����
				else
				{
					pDParent->_pRight = pDel->_pLeft;
					
				}
			}
		}

		//ֻ���Һ��ӣ�������������������Ӷ�û��
		else if (NULL == pDel->_pLeft)
		{
			if (pDel == _pRoot)//�ҵ�֧
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
		//�������Ӷ���
		else
		{
			//�������㣬���������У��Ҵ�ɾ��������������µĵ�һ�����,��������������µĵ�һ�����
			pNode pReplaceNode = pDel->_pRight;
			pDParent = pDel;
			//�ҳ�������
			while (pReplaceNode->_pLeft)
			{
				pDParent = pReplaceNode;
				pReplaceNode = pReplaceNode->_pLeft;
			}
			//������ɾ�����������,һ���������Ϊֻ������������Ҷ�ӽ��
			pDel->_key = pReplaceNode->_key;
			pDel->_value = pReplaceNode->_value;
			pDel = pReplaceNode;
			//ɾ�����

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

	//������������ת��Ϊһ��˫������������������һ�����������⣩
	pNode BST2List()
	{
		pNode pHead = pRoot;
		//����
		if (_pRoot == NULL)
			return NULL;

		//���ҵ�ͷ���
		while (pHead->_pLeft)
		{
			pHead = pHead->_pLeft;//�ҵ�ͷ���
		}
		pNode prev = NULL;
		_BST2List(_pRoot, prev);
		return pHead;
	}
	//�ݹ�
private:
	bool _Find1(pNode pRoot, const K&key)
	{
		if (pRoot == NULL)
			return false;		
		if (key == pRoot->_key)
			return true;
		//������
		else if (key < pRoot->_pLeft->_key)
			_Find1(pRoot->_pLeft, key);
		//������
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
		_BST2List(pRoot->_pLeft, prev);//������
		pRoot->_pLeft = prev;//���ڵ㣬��ָ����
		if (prev)//������ָ����
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







