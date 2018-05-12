#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
//�Ѵ洢��������
#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<assert.h>
#if 0
//����һ��С��
template<class T>
class Heap
{
public:
	Heap()
	{}

	Heap(const T*array, size_t size)
	{
		//���ٿռ�
		_array.resize(size);
		//����Ԫ��
		for (int i = 0; i < size; ++i)
		{
			_array[i] = array[i];
		}
		//����Ԫ��
		int root = (size - 1 - 1) >> 1;
		for (; root >= 0; --root)
		{
			AdjustDown(root);
		}
	}
	

	void Push(const T&data)
	{
		_array.push_back(data);//��Ԫ�ط���vector�У�����������
		//Ԫ�ط���֮�󣬸�������1������Ҫ������е���
		if (_array.size() > 1)
		{
			//���ϵ���
			AdjustUp(_array.size() - 1);//�˴��������±�
		}
	}

	void Pop()
	{
		if (_array.size() == 0)
			return;
		else if (_array.size() == 1)
		{
			_array.pop_back();
			return;
		}
		//���Ԫ��
		else
		{
			swap(_array[0], _array[_array.size() - 1]);
			_array.pop_back();//ɾ�����������һ��Ԫ��
			AdjustDown(0);
		}
	}
	bool Empty()const
	{
		return _array.empty();
	}
	size_t Size()const
	{
		return _array.size();
	}
	//��ȡ�Ѷ�Ԫ��
	T Top()const
	{
		assert(_array.size());
		return _array[0];
	}
private:
	//����С��-----���µ���
	void AdjustDown(size_t parent)
	{
		//�������,��Ĭ������Ϊ��С�ĺ���
		size_t child = parent * 2 + 1;
		size_t size = _array.size();
		//����С�ĺ���
		while (child < size)
		{
			if (child + 1 <size && _array[child] > _array[child + 1])
			{
				child = child + 1;//�Һ���Ϊ��С
			}
			//�Ƚ���С�ĺ�����˫�׵Ĵ�С----ֵ��
			if (_array[child] < _array[parent])
			{
				swap(_array[parent], _array[child]);
				//����֮�󣬿��ܵ��º��ӽ�㲻Ϊ��
				parent = child;
				child = parent * 2 + 1;
			}
			else
				break;
		}
	}
	//С��
	void AdjustUp(size_t child)//�˴���childΪ�±�
	{
		size_t parent = (child - 1) >> 1;
		while (child > 0)
		{
			if (_array[parent] > _array[child])
			{
				swap(_array[parent], _array[child]);
				child = parent;
				parent = (child - 1) >> 1;
			}
			else
				return;
		}
	}

private:
	vector<T> _array;
};
#endif
//ģ������б�,����һ�������
#if 1
template<class T>
class Less//С��
{
public:
	bool operator()(const T&left, const T&right)
	{
		return left < right;
	}
};

template<class T>
class Great//���
{
public:
	bool operator()(const T&left, const T&right)
	{
		return left > right;
	}
};

template<class T,class Compare=Less<T>>//ȱʡʱΪС��
class Heap
{
public:
	Heap()
	{}

	Heap(const T*array, size_t size)
	{
		//���ٿռ�
		_array.resize(size);
		//����Ԫ��
		for (int i = 0; i < size; ++i)
		{
			_array[i] = array[i];
		}
		//����Ԫ��
		int root = (size - 1 - 1) >> 1;
		for (; root >= 0; --root)
		{
			AdjustDown(root);
		}
	}


	void Push(const T&data)
	{
		_array.push_back(data);//��Ԫ�ط���vector�У�����������
		//Ԫ�ط���֮�󣬸�������1������Ҫ������е���
		if (_array.size() > 1)
		{
			//���ϵ���
			AdjustUp(_array.size() - 1);//�˴��������±�
		}
	}

	void Pop()
	{
		if (_array.size() == 0)
			return;
		else if (_array.size() == 1)
		{
			_array.pop_back();
			return;
		}
		//���Ԫ��
		else
		{
			swap(_array[0], _array[_array.size() - 1]);
			_array.pop_back();//ɾ�����������һ��Ԫ��
			AdjustDown(0);
		}
	}
	bool Empty()const
	{
		return _array.empty();
	}

	size_t Size()const
	{
		return _array.size();
	}

	//��ȡ�Ѷ�Ԫ��
	T Top()const
	{
		assert(_array.size());
		return _array[0];
	}
private:
	//����С��-----���µ���
	void AdjustDown(size_t parent)
	{
		//�������,��Ĭ������Ϊ��С�ĺ���
		size_t child = parent * 2 + 1;
		size_t size = _array.size();
		//����С�ĺ���
		while (child < size)
		{
			//Compare com;
			if (child + 1 <size && Compare()(_array[child + 1], _array[child]))//�ڴ˴�����ΪĬ��������С�����Ҫ����true��ֻ��������
			{
				child = child + 1;//�Һ���Ϊ��С
			}
			//�Ƚ���С�ĺ�����˫�׵Ĵ�С----ֵ��
			if (Compare()(_array[child], _array[parent]))
			{
				swap(_array[parent], _array[child]);
				//����֮�󣬿��ܵ��º��ӽ�㲻Ϊ��
				parent = child;
				child = parent * 2 + 1;
			}
			else
				break;
		}
	}
	void AdjustUp(size_t child)//�˴���childΪ�±�
	{
		size_t parent = (child - 1) >> 1;
		while (child > 0)
		{
			if (Compare()(_array[child] , _array[parent]))
			{
				swap(_array[parent], _array[child]);
				child = parent;
				parent = (child - 1) >> 1;
			}
			else
				return;
		}
	}

private:
	vector<T> _array;
};
#endif

#if 0
//ģ���ģ������б�
template<class T>
class Less//С��
{
public:
	bool operator()(const T&left, const T&right)
	{
		return left < right;
	}
};

template<class T>
class Great//���
{
public:
	bool operator()(const T&left, const T&right)
	{
		return left > right;
	}
};

template<class T, template<class> class Compare = Less >//ȱʡʱΪС��
class Heap
{
public:
	Heap()
	{}

	Heap(const T*array, size_t size)
	{
		//���ٿռ�
		_array.resize(size);
		//����Ԫ��
		for (int i = 0; i < size; ++i)
		{
			_array[i] = array[i];
		}
		//����Ԫ��
		int root = (size - 1 - 1) >> 1;
		for (; root >= 0; --root)
		{
			AdjustDown(root);
		}
	}


	void Push(const T&data)
	{
		_array.push_back(data);//��Ԫ�ط���vector�У�����������
		//Ԫ�ط���֮�󣬸�������1������Ҫ������е���
		if (_array.size() > 1)
		{
			//���ϵ���
			AdjustUp(_array.size() - 1);//�˴��������±�
		}
	}

	void Pop()
	{
		if (_array.size() == 0)
			return;
		else if (_array.size() == 1)
		{
			_array.pop_back();
			return;
		}
		//���Ԫ��
		else
		{
			swap(_array[0], _array[_array.size() - 1]);
			_array.pop_back();//ɾ�����������һ��Ԫ��
			AdjustDown(0);
		}
	}
	bool Empty()const
	{
		return _array.empty();
	}
	size_t Size()const
	{
		return _array.size();
	}
	//��ȡ�Ѷ�Ԫ��
	T Top()const
	{
		assert(_array.size());
		return _array[0];
	}
private:
	//����С��-----���µ���
	void AdjustDown(size_t parent)
	{
		//�������,��Ĭ������Ϊ��С�ĺ���
		size_t child = parent * 2 + 1;
		size_t size = _array.size();
		//����С�ĺ���
		while (child < size)
		{
			//Compare com;
			if (child + 1 <size && Compare<T>()(_array[child + 1], _array[child]))//�ڴ˴�����ΪĬ��������С�����Ҫ����true��ֻ��������
			{
				child = child + 1;//�Һ���Ϊ��С
			}
			//�Ƚ���С�ĺ�����˫�׵Ĵ�С----ֵ��
			if (Compare<T>()(_array[child], _array[parent]))
			{
				swap(_array[parent], _array[child]);
				//����֮�󣬿��ܵ��º��ӽ�㲻Ϊ��
				parent = child;
				child = parent * 2 + 1;
			}
			else
				break;
		}
	}
	void AdjustUp(size_t child)//�˴���childΪ�±�
	{
		size_t parent = (child - 1) >> 1;
		while (child > 0)
		{
			if (Compare<T>()(_array[child], _array[parent]))
			{
				swap(_array[parent], _array[child]);
				child = parent;
				parent = (child - 1) >> 1;
			}
			else
				return;
		}
	}

private:
	vector<T> _array;
};
#endif
#if 0
void Test()
{
	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23 };
	Heap<int> hp(array,sizeof(array)/sizeof(*array));//�����ģ�����������Ҫʵ����
	cout << hp.Top() << endl;
	hp.Push(98);
	cout << hp.Top() << endl;
	cout << hp.Size() << endl;
	/*hp.Pop();
	cout << hp.Top() << endl;
	hp.Pop();
	cout << hp.Top() << endl;
	hp.Pop();
	cout << hp.Top() << endl;
	hp.Pop();
	cout << hp.Top() << endl;
	hp.Pop();
	cout << hp.Top() << endl;
	hp.Pop();
	cout << hp.Top() << endl;*/
}
#endif