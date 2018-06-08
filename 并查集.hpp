#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include<iostream>
using namespace std;
#include<vector>

class UFS
{
public:
    UFS(size_t size)//�Բ��鼯�ļ��Ͻ��г�ʼ��
        :_vt(size,-1)//����vector������Ĺ��캯����������г�ʼ������ʽһ
    {
        //_vt.resize(size, -1);//����resiz��������ʽ2

        //��ʽ��
        /*int i = 0;
        for (; i < size; ++i)
        {
            _vt[i] = -1;
        }*/
    }
    int Find(int root)
    {
        while (_vt[root] >= 0)
        {
            root = _vt[root];
        }
        return root;
    }
    void UnionSet(int x1, int x2)
    {
        if (x1 > _vt.size() || x2 > _vt.size())
            return;
        int a = Find(x1);
        int b = Find(x2);
        _vt[a] += _vt[b];
        _vt[b] = a;
    }
    size_t Count()//�鿴�������м����Ӽ���
    {
        int count = 0;
        int i = 0;
        for (; i < _vt.size();++i)
        {
            if (_vt[i] < 0)
                count++;
        }
        return count;
    }
private:
    vector<int> _vt;
};

void Test()
{
    UFS u(10);
    u.UnionSet(0, 3);
    u.UnionSet(3, 4);
    u.UnionSet(4, 5);
    u.UnionSet(8, 9);
    u.UnionSet(1, 2);
    u.UnionSet(2, 6);
    u.UnionSet(6, 7);
    u.UnionSet(81, 9);//Խ��Ԫ��

    cout << u.Count() << endl;
}