char OneOccure(char *array, int size)
{
	if (size == 0||array==NULL)
		return -1;
	int i = 0;
	int count = 0;
	char ch = 0;
	int flag = 0;//��������ǣ��������ַ�ֻ����һ�Σ������ֱ�ӷ���
	while (array[i] != '\0')
	{
		ch = array[i];
		for (int j = 0; j < size; ++j)
		{
			if (ch == array[j])
			{
				count++;
			}
		}
		if (count == 1)
		{
			flag = 1;
			break;
		}
		count = 0;//��������һ��ѭ��
		++i;
	}
	if (flag == 1)
		return ch;
	else
		return -1;
}
