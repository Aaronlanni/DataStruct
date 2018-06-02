//#define _CRT_SECURE_NO_WARNINGS 1
//
#include<iostream>
#include<assert.h>
#include<stack>
using namespace std;

//enum OPERATOR
//{
//	ADD,SUM,MUL,DIV,DATA
//};
//
//struct Cell
//{
//	OPERATOR _op;
//	int _data;
//};
//int CalcRPN(Cell*RPN, int size)
//{
//	stack<int> s;
//	for (int i = 0; i < size; ++i)
//	{
//		if  (DATA==RPN[i]._op)
//		{
//			s.push(RPN[i]._data);
//		}
//		else
//		{
//			int right = s.top();
//			s.pop();
//			int left = s.top();
//			s.pop();
//			switch (RPN[i]._op)
//			{
//				
//			case ADD:
//				s.push(left + right);
//				break;
//			case SUM:
//				s.push(left - right);
//				break;
//			case MUL:
//				s.push(left * right);
//				break;
//			case DIV:
//				if (right == 0)
//				{
//					cout << "³ýÊý·Ç·¨" << endl;
//					return 0;
//				}
//				s.push(left / right);
//			}
//		}
//	}
//	return s.top();
//}
//int main()
//{
//	//12*(3+4)-6+8/2 ==> 12 3 4 + * 6 - 8 2 / +
//	Cell RPN[] = { { DATA, 12 }, { DATA, 3 }, { DATA, 4 }, { ADD, 0 }, { MUL, 0 },
//	{ DATA, 6 }, { SUM, 0 }, { DATA, 8 }, { DATA, 2 }, { DIV, 0 }, { ADD, 0 } };
//	cout << CalcRPN(RPN, sizeof(RPN) / sizeof(RPN[0]))<<endl;
//	system("pause");
//	return 0;
//}


