#include<iostream>
using namespace std;
#include<vector>

class BitSet
{
public:
	BitSet(size_t  size = 10)
		:_size(size)
	{
		_bt.resize(((size >> 5) + 1));//��ʾ��ǰ��Ҫ������ٸ�int
	}
	void Set(int whichBit)
	{
		//���㵱ǰֵ���������һ��int��
		int index = (whichBit >> 5);
		//�����ڵ�ǰint�µ���һ��bitλ��
		if (whichBit < _size)
			_bt[index] |= (1 << (whichBit % 32));//whichBit % 32���㵱ǰ�������ĸ�bitλ�ϣ��Ӷ������Ӧ�ı���λ��Ϊ1
	}
	void ReSet(int whichBit)
	{
		//���㵱ǰֵ���������һ��int��
		int index = (whichBit >> 5);
		//�����ڵ�ǰint�µ���һ��bitλ��
		if (whichBit < _size)
			_bt[index] &= ~(1 << (whichBit % 32));
	}
	//��⵱ǰλ�Ƿ�Ϊ1
	bool Test(int whichBit)
	{
		//���㵱ǰֵ���������һ��int��
		int index = (whichBit >> 5);
		//�����ڵ�ǰint�µ���һ��bitλ��
	
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

		//�����������ַ�������һ��ͳ���ĸ�����λ��������ܳ���1�Ĵ�����һ����ʮ����������ڴ˴����������ַ����������������
		char* pCount = "\0\1\1\2\1\2\2\3\1\2\2\3\2\3\3\4";//�ĸ�����λ��������ʮ����״̬
		int count = 0;
		for (size_t i = 0; i < _bt.size(); ++i)//_bt.size()��ʾ�ж��ٸ�int
		{
			int value = _bt[i];//_btΪint�ͣ��˴�ȡ�����һ��int
			//�ڴ˴�һ��ͳ���ĸ�����λ
			int j = 0;
			while (j < sizeof(int))
			{
				count += pCount[value & 0x0F];//����ͳ�Ƶ�һ���ı���λ
				value = value >> 4;//���ղ��Ѿ�ͳ�Ƶ���λ���ߣ�Ȼ��ͳ��ʣ�µ���λ
				count += pCount[value & 0x0F];
				value = value >> 4;//��ʱ�ѽ���һ���ֽ�ͳ����ɡ�
				++j;
			}
		}
		return count;
	}
	//���ر���λ�ĸ���
	size_t Size()const
	{
		return _size;
	}
private:
	vector<int> _bt;//��ʾ��ǰһ����������ٸ�����λ����ʱĬ������32λ
	int _size;//��ʾ�Ѿ�ʹ���˶��ٱ���λ
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
		cout << "��1" << endl;
	else
		cout << "����1" << endl;

	bt.ReSet(36);
	bt.ReSet(45);
	cout << bt.Count() << endl;
	cout << bt.Size() << endl;
	if (bt.Test(36))
		cout << "��1" << endl;
	else
		cout << "����1" << endl;
}