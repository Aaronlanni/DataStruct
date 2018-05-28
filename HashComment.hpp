#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<string.h>
#include<iostream>
using namespace std;
// 使用素数表对齐做哈希表的容量，降低哈希冲突
const int _PrimeSize = 28;
static const unsigned long _PrimeList[_PrimeSize] =
{
    53ul, 97ul, 193ul, 389ul, 769ul,
    1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
    49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
    1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
    50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
    1610612741ul, 3221225473ul, 4294967291ul
};
//除留余数法
size_t GetNextPrime(size_t num)
{
    for (int i = 0; i < _PrimeSize; ++i)
    {
        if (_PrimeList[i] > num)
            return _PrimeList[i];
    }

    //走到最后，仍然没有找到
    return _PrimeList[_PrimeSize - 1];
}
static size_t BKDRHash(const char * str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313
    unsigned int hash = 0;
    while (*str)
    {
        hash = hash * seed + (*str++);
    }
    return (hash & 0x7FFFFFFF);
}
//转换函数（整数）
template<class K>
class KeyToIntDef
{
public:
    size_t operator()(const K&key)
    {
        return key;
    }
};
//字符串，需要特化

class StringToInt
{
public:
    size_t operator()(const string&  key)
    {
        return BKDRHash(key.c_str()); //key.c_str()将其
    }
};