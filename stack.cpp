#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<assert.h>
using namespace std;
//¾²Ì¬
//#define STACK_SIZE 100
//template<class T>
//class Stack
//{
//public:
//	Stack()
//	:_size(0)
//	{}
//
//	void Push(const T&data)
//	{
//		if (STACK_SIZE == _size)
//			return;
//		_array[_size++] = data;
//	}
//
//	void Pop()
//	{
//		if (_size <= 0)
//			return;
//		--_size;
//	}
//	size_t Size()const
//	{
//		return _size;
//	}
//	bool Empty()const
//	{
//		return (_size == 0);
//	}
//	T&Top()
//	{
//		return _array[_size - 1];
//	}
//
//	T&Top()const
//	{
//		return _array[_size - 1];
//	}
//
//private:
//	T _array[STACK_SIZE];
//	int _size;
//};
//
//int main()
//{
//	Stack<int>  s;
//	s.Push(1);
//	s.Push(2); 
//	s.Push(3); 
//	s.Push(4);
//	s.Push(5);
//	cout << s.Size() << endl;
//	cout << s.Top() << endl;
//
//	s.Pop();
//	cout <<s.Size() << endl;
//	cout << s.Top() << endl;
//	s.Pop();
//	cout << s.Size() << endl;
//	cout << s.Top() << endl;
//	s.Pop();
//	s.Pop();
//	cout << s.Size() << endl;
//	cout << s.Top() << endl;
//	s.Pop();
//	cout << s.Size() << endl;
//	
//	s.Pop();
//	cout << s.Size() << endl;
//	system("pause");
//	return 0;
//}


template<class T>
class Stack
{
public:
	Stack()
		:_array(new T[3])
		, _size(0)
		, _capacity(3)
	{}

	void Push(const T& data)
	{
		CheckCapacity();
		_array[_size++] = data;
	}

	void Pop()
	{
		if (_size <= 0)
			return;
		_size--;
	}

	T& Top()
	{
		return _array[_size - 1];
	}

	T& Top()const
	{
		return _array[_size - 1];
	}
	size_t Size()const
	{
		return _size;
	}
	size_t Capacity()const
	{
		return _capacity;
	}
	bool Empty()const
	{
		return (Size() == 0);
	}
	

	//¼ì²â¿Õ¼ä
	void CheckCapacity()
	{
		if (_size >= _capacity)
		{
			T*pNewNode = new T[_size * 2 + 3];
			for (int i = 0; i < _size; ++i)
			{
				pNewNode[i] = _array[i];
			}
			_capacity = _size * 2 + 3;
			delete _array;
			_array = pNewNode;
		}
	}
	~Stack()
	{
		//¿Õ¶ÓÁÐ
		if (_array)
			delete _array;
		_array = NULL;
		_size = 0;
		_capacity = 0;
	}

private:
	T* _array;
	size_t _capacity;
	size_t _size;
};
int main()
{
	Stack<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(6);
	
	cout << s.Size() << endl;
	cout << s.Top() << endl;
	cout << s.Capacity() << endl;
	s.Pop();
	s.Pop();
	cout << s.Size() << endl;
	cout << s.Top() << endl;
	cout << s.Capacity() << endl;

	

	system("pause");
	return 0;
}
