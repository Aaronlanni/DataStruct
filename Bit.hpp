#include<iostream>
using namespace std;
#include<vector>

class BitSet
{
public:
	BitSet(size_t  size = 10)
		:_size(size)
	{
		_bt.resize(((size >> 5) + 1));//表示当前需要申请多少个int
	}
	void Set(int whichBit)
	{
		//计算当前值在申请的哪一个int上
		int index = (whichBit >> 5);
		//就算在当前int下的哪一个bit位上
		if (whichBit < _size)
			_bt[index] |= (1 << (whichBit % 32));//whichBit % 32计算当前数字在哪个bit位上，从而将相对应的比特位置为1
	}
	void ReSet(int whichBit)
	{
		//计算当前值在申请的哪一个int上
		int index = (whichBit >> 5);
		//就算在当前int下的哪一个bit位上
		if (whichBit < _size)
			_bt[index] &= ~(1 << (whichBit % 32));
	}
	//检测当前位是否为1
	bool Test(int whichBit)
	{
		//计算当前值在申请的哪一个int上
		int index = (whichBit >> 5);
		//就算在当前int下的哪一个bit位上
	
		if (whichBit < _size)
			return (_bt[index] & (1 << (whichBit % 32)));

		else
		{
			printf("whichbit error\n");
			return false;
		}
	}

	size_t Count()
	{
		/*int count = 0;
		for (size_t i = 0; i < _bt.size(); ++i)
		{
			int value = _bt[i];
			while (value)
			{
				++count;
				value &= (value - 1);
			}
		}
		return count;*/

		//方法二，此种方法利用一次统计四个比特位，则其可能出现1的次数的一共有十六种情况，在此处可以利用字符串常量，将其给出
		char* pCount = "\0\1\1\2\1\2\2\3\1\2\2\3\2\3\3\4";//四个比特位，表明有十六种状态
		int count = 0;
		for (size_t i = 0; i < _bt.size(); ++i)//_bt.size()表示有多少个int
		{
			int value = _bt[i];//_bt为int型，此处取出其第一个int
			//在此处一次统计四个比特位
			int j = 0;
			while (j < sizeof(int))
			{
				count += pCount[value & 0x0F];//首先统计第一个四比特位
				value = value >> 4;//将刚才已经统计的四位移走，然后统计剩下的四位
				count += pCount[value & 0x0F];
				value = value >> 4;//此时已将第一个字节统计完成。
				++j;
			}
		}
		return count;
	}
	//返回比特位的个数
	size_t Size()const
	{
		return _size;
	}
private:
	vector<int> _bt;//表示当前一次性申请多少个比特位，此时默认申请32位
	int _size;//表示已经使用了多少比特位
};

void TestBit()
{
	BitSet bt(100);
	bt.Set(36);
	bt.Set(76);
	bt.Set(69);
	bt.Set(45);
	cout << bt.Count() << endl;
	cout << bt.Size() << endl;
	if (bt.Test(76))
		cout << "是1" << endl;
	else
		cout << "不是1" << endl;

	bt.ReSet(36);
	bt.ReSet(45);
	cout << bt.Count() << endl;
	cout << bt.Size() << endl;
	if (bt.Test(36))
		cout << "是1" << endl;
	else
		cout << "不是1" << endl;
}