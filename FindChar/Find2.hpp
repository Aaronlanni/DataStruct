char FirstComeSecondChar(char*array, size_t size)
{
    if (array == '\0')
        return '\0';
    //存放每个字符
    int str[256] = { 0 };
    memset(str, '0', 256);
    char*str2 = array;
    //统计每个字符出现的次数
    for (int i = 0; i < size; ++i)
    {
        str[*str2]++;//在对应字符上统计其出现的次数
        str2++;
    }
    str2 = array;//再一次更新指针的位置，让其重新指向开始
    for (int j = 0; j < size; ++j)
    {
        if (str[*str2] == 2)
        {
            return *str2;//找到的话，则返回对应的元素
        }
        str2++;
    }
    //走出来，还没有找到，则证明没有这个字符
    return '\0';
}