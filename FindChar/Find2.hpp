char FirstComeSecondChar(char*array, size_t size)
{
    if (array == '\0')
        return '\0';
    //���ÿ���ַ�
    int str[256] = { 0 };
    memset(str, '0', 256);
    char*str2 = array;
    //ͳ��ÿ���ַ����ֵĴ���
    for (int i = 0; i < size; ++i)
    {
        str[*str2]++;//�ڶ�Ӧ�ַ���ͳ������ֵĴ���
        str2++;
    }
    str2 = array;//��һ�θ���ָ���λ�ã���������ָ��ʼ
    for (int j = 0; j < size; ++j)
    {
        if (str[*str2] == 2)
        {
            return *str2;//�ҵ��Ļ����򷵻ض�Ӧ��Ԫ��
        }
        str2++;
    }
    //�߳�������û���ҵ�����֤��û������ַ�
    return '\0';
}