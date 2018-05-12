#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
//堆存储在数组中
#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<assert.h>
#if 0
//创建一个小堆
template<class T>
class Heap
{
public:
	Heap()
	{}

	Heap(const T*array, size_t size)
	{
		//开辟空间
		_array.resize(size);
		//拷贝元素
		for (int i = 0; i < size; ++i)
		{
			_array[i] = array[i];
		}
		//调整元素
		int root = (size - 1 - 1) >> 1;
		for (; root >= 0; --root)
		{
			AdjustDown(root);
		}
	}
	

	void Push(const T&data)
	{
		_array.push_back(data);//将元素放在vector中，即数组的最后
		//元素放入之后，个数大于1，则需要对齐进行调整
		if (_array.size() > 1)
		{
			//向上调整
			AdjustUp(_array.size() - 1);//此处传的是下标
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
		//多个元素
		else
		{
			swap(_array[0], _array[_array.size() - 1]);
			_array.pop_back();//删除数组中最后一个元素
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
	//获取堆顶元素
	T Top()const
	{
		assert(_array.size());
		return _array[0];
	}
private:
	//创建小堆-----向下调整
	void AdjustDown(size_t parent)
	{
		//标记左孩子,且默认左孩子为最小的孩子
		size_t child = parent * 2 + 1;
		size_t size = _array.size();
		//找最小的孩子
		while (child < size)
		{
			if (child + 1 <size && _array[child] > _array[child + 1])
			{
				child = child + 1;//右孩子为最小
			}
			//比较最小的孩子与双亲的大小----值域
			if (_array[child] < _array[parent])
			{
				swap(_array[parent], _array[child]);
				//交换之后，可能导致孩子结点不为堆
				parent = child;
				child = parent * 2 + 1;
			}
			else
				break;
		}
	}
	//小堆
	void AdjustUp(size_t child)//此处的child为下标
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
//模板参数列表,创建一个任意堆
#if 1
template<class T>
class Less//小堆
{
public:
	bool operator()(const T&left, const T&right)
	{
		return left < right;
	}
};

template<class T>
class Great//大堆
{
public:
	bool operator()(const T&left, const T&right)
	{
		return left > right;
	}
};

template<class T,class Compare=Less<T>>//缺省时为小堆
class Heap
{
public:
	Heap()
	{}

	Heap(const T*array, size_t size)
	{
		//开辟空间
		_array.resize(size);
		//拷贝元素
		for (int i = 0; i < size; ++i)
		{
			_array[i] = array[i];
		}
		//调整元素
		int root = (size - 1 - 1) >> 1;
		for (; root >= 0; --root)
		{
			AdjustDown(root);
		}
	}


	void Push(const T&data)
	{
		_array.push_back(data);//将元素放在vector中，即数组的最后
		//元素放入之后，个数大于1，则需要对齐进行调整
		if (_array.size() > 1)
		{
			//向上调整
			AdjustUp(_array.size() - 1);//此处传的是下标
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
		//多个元素
		else
		{
			swap(_array[0], _array[_array.size() - 1]);
			_array.pop_back();//删除数组中最后一个元素
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

	//获取堆顶元素
	T Top()const
	{
		assert(_array.size());
		return _array[0];
	}
private:
	//创建小堆-----向下调整
	void AdjustDown(size_t parent)
	{
		//标记左孩子,且默认左孩子为最小的孩子
		size_t child = parent * 2 + 1;
		size_t size = _array.size();
		//找最小的孩子
		while (child < size)
		{
			//Compare com;
			if (child + 1 <size && Compare()(_array[child + 1], _array[child]))//在此处，因为默认左孩子最小，因此要返回true，只能是这样
			{
				child = child + 1;//右孩子为最小
			}
			//比较最小的孩子与双亲的大小----值域
			if (Compare()(_array[child], _array[parent]))
			{
				swap(_array[parent], _array[child]);
				//交换之后，可能导致孩子结点不为堆
				parent = child;
				child = parent * 2 + 1;
			}
			else
				break;
		}
	}
	void AdjustUp(size_t child)//此处的child为下标
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
//模板的模板参数列表
template<class T>
class Less//小堆
{
public:
	bool operator()(const T&left, const T&right)
	{
		return left < right;
	}
};

template<class T>
class Great//大堆
{
public:
	bool operator()(const T&left, const T&right)
	{
		return left > right;
	}
};

template<class T, template<class> class Compare = Less >//缺省时为小堆
class Heap
{
public:
	Heap()
	{}

	Heap(const T*array, size_t size)
	{
		//开辟空间
		_array.resize(size);
		//拷贝元素
		for (int i = 0; i < size; ++i)
		{
			_array[i] = array[i];
		}
		//调整元素
		int root = (size - 1 - 1) >> 1;
		for (; root >= 0; --root)
		{
			AdjustDown(root);
		}
	}


	void Push(const T&data)
	{
		_array.push_back(data);//将元素放在vector中，即数组的最后
		//元素放入之后，个数大于1，则需要对齐进行调整
		if (_array.size() > 1)
		{
			//向上调整
			AdjustUp(_array.size() - 1);//此处传的是下标
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
		//多个元素
		else
		{
			swap(_array[0], _array[_array.size() - 1]);
			_array.pop_back();//删除数组中最后一个元素
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
	//获取堆顶元素
	T Top()const
	{
		assert(_array.size());
		return _array[0];
	}
private:
	//创建小堆-----向下调整
	void AdjustDown(size_t parent)
	{
		//标记左孩子,且默认左孩子为最小的孩子
		size_t child = parent * 2 + 1;
		size_t size = _array.size();
		//找最小的孩子
		while (child < size)
		{
			//Compare com;
			if (child + 1 <size && Compare<T>()(_array[child + 1], _array[child]))//在此处，因为默认左孩子最小，因此要返回true，只能是这样
			{
				child = child + 1;//右孩子为最小
			}
			//比较最小的孩子与双亲的大小----值域
			if (Compare<T>()(_array[child], _array[parent]))
			{
				swap(_array[parent], _array[child]);
				//交换之后，可能导致孩子结点不为堆
				parent = child;
				child = parent * 2 + 1;
			}
			else
				break;
		}
	}
	void AdjustUp(size_t child)//此处的child为下标
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
	Heap<int> hp(array,sizeof(array)/sizeof(*array));//如果是模板参数，则需要实例化
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