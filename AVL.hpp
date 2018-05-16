#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

template<class K,class V>
struct AVLNode
{
	AVLNode(const K&key, const V&value)
	:_pLeft(NULL)
	, _pRight(NULL)
	, _parent(NULL)
	, _key(key)
	, _value(value)
	, _bf(0)
	{}

	AVLNode<K,V> *_pLeft;
	AVLNode<K, V> *_pRight;
	AVLNode<K, V> *_parent;
	K _key;
	V _value;
	int _bf;//ƽ������
};
template<class K,class V>
class AVLTree
{
	typedef AVLNode<K, V> Node;
	typedef AVLNode<K, V>* pNode;
public:
	AVLTree()
		:_pRoot(NULL)
	{}

	bool Insert(const K&key, const V&value)
	{
		//����
		if (NULL == _pRoot)
		{
			_pRoot = new Node(key, value);
			return true;
		}
			
		//�ǿ���
		pNode pCur = _pRoot;
		pNode pParent = NULL;
		//�Ҳ���λ��
		while (pCur)
		{
			if (key > pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
			else if (key < pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else
				return false;
		}
		pCur = new Node(key, value);
		//������
		if (key > pParent->_key)
		{
			pParent->_pRight = pCur;
			pCur->_parent = pParent;
		}
		else
		{
			pParent->_pLeft = pCur;
			pCur->_parent = pParent;
		}

		//����֮������ʧ�⣬����Ҫ����
		while (pParent)
		{
			//����ڵ�֮��ĵ���
			if (pParent->_pLeft == pCur)
				pParent->_bf--;
			else
				pParent->_bf++;
			//����֮��ƽ�����ӵ��ж�
			if (pParent->_bf == 0)
				break;
			else if (pParent->_bf == 1 || pParent->_bf == -1)
			{
				pCur = pParent;
				pParent = pCur->_parent;
			}
			else
			{
				//�������ϸ�
				if (pParent->_bf == 2)
				{
					//�ϸ����������Ҳ�
					if (pCur->_bf == 1)
					{
						RoateL(pParent);
					}
					//�ϸ������������
					else
					{
						RoateRL(pParent);
					}
				}
				//�������ϸ�
				else
				{
					//�ϸ������������
					if (pCur->_bf == -1)
					{
						RoateR(pParent);
					}
					//�ϸ����������Ҳ�
					else
					{
						RoateLR(pParent);
					}
				}
				//��ת���֮�󣬲���Ҫ�����ϵ���
				break;
			}
		}
		return true;
	}
	
private:
	//����
	void RoateL(pNode parent)
	{
		pNode pSubR = parent->_pRight;
		pNode pSubRL = pSubR->_pLeft;
		pNode pParent = parent->_parent;

		pSubR->_pLeft = parent;
		parent->_parent = pSubR;

		parent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_parent = parent;

		if (parent == _pRoot)
		{
			_pRoot = pSubR;
		}
		else
		{
			if (pParent->_pLeft == parent)
				pParent->_pLeft = pSubR;

			else
				pParent->_pRight = pSubR;
		}		
		//����ƽ������
		parent->_bf = pSubR->_bf = 0;
	}

	//�ҵ���
	void RoateR(pNode parent)
	{
		pNode pSubL = parent->_pLeft;
		pNode pSubLR = pSubL->_pRight;
		pNode pParent = parent->_parent;

		pSubL->_pRight = parent;
		parent->_parent = pSubL;

		parent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_parent = parent;
		if (parent == _pRoot)
		{
			_pRoot = pSubL;
		}
		else
		{
			if (pParent->_pLeft == parent)
				pParent->_pLeft = pSubL;

			else
				pParent->_pRight = pSubL;
		}		
		parent->_bf = pSubL->_bf = 0;
	}
	//����˫��
	void RoateRL(pNode parent)
	{
		pNode pSubR = parent->_pRight;
		pNode pSubRL = pSubR->_pLeft;
		int bf = pSubRL->_bf;
		RoateR(pSubR);
		RoateL(parent);
		if (bf == -1)
			pSubR->_bf = 1;
		if (bf == 1)
			parent->_bf = -1;
	}

	//����˫��
	void RoateLR(pNode parent)
	{
		pNode pSubL = parent->_pLeft;
		pNode pSubLR = pSubL->_pRight;
		int bf = pSubLR->_bf;
		RoateL(pSubL);
		RoateR(parent);
		if (bf == -1)
			parent->_bf = 1;
		if (bf == 1)
			pSubL->_bf = -1;
	}
private:
	pNode _pRoot;
};

