void TestTree()
{
    //��������
    char array[] = "abd###ce##f";
    BindaryTree<char> bt(array, strlen(array), '#');
    cout << "�ǿ���1�������㣩---->" ;
    if (bt.IsBalanceTree())
        cout << "ƽ��" << endl;
    else
        cout << "��ƽ��" << endl;

    cout << "�ǿ���2�������㣩---->" ;
    char array1[] = "abd##c";
    BindaryTree<char> bt1(array1, strlen(array1), '#');
    if (bt1.IsBalanceTree())
        cout << "ƽ��" << endl;
    else
        cout << "��ƽ��" << endl;

    char array2[] = "a";
    BindaryTree<char> bt2(array2, strlen(array2), '#');
    cout << "�ǿ���3��ֻ��һ����㣩---->" ;
    if (bt2.IsBalanceTree())
        cout << "ƽ��" << endl;
    else
        cout << "��ƽ��" << endl;

    //����
    cout << "����---->";
    BindaryTree<char> bt3;
    if (bt3.IsBalanceTree())
        cout << "ƽ��" << endl;
    else
        cout << "��ƽ��" << endl;
}