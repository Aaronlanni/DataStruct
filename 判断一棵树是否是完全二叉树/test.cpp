void TestTree()
{
    char array[] = "abd###ce##f";
    BindaryTree<char> bt(array, strlen(array), '#');
    //������
    cout << "�ǿ���1:"<<endl;
    if (bt.IsCompeteTree())
        cout << "��" << endl;
    else
        cout << "����" << endl;

    if (bt.IsCompeteTree1())
        cout << "��" << endl;
    else
        cout << "����" << endl;

    if (bt.IsCompeteTree2())
        cout << "��" << endl;
    else
        cout << "����" << endl;

    char array1[] = "abd##c##f";
    BindaryTree<char> bt2(array1, strlen(array1), '#');
    //������
    cout << "�ǿ���2:" << endl;
    if (bt2.IsCompeteTree())
        cout << "��" << endl;
    else
        cout << "����" << endl;

    if (bt2.IsCompeteTree1())
        cout << "��" << endl;
    else
        cout << "����" << endl;

    if (bt2.IsCompeteTree2())
        cout << "��" << endl;
    else
        cout << "����" << endl;

    //����
    BindaryTree<char> bt1;
    cout << "����:"<<endl;
    if (bt1.IsCompeteTree())
        cout << "��" << endl;
    else
        cout << "����" << endl;

    if (bt1.IsCompeteTree1())
        cout << "��" << endl;
    else
        cout << "����" << endl;

    if (bt1.IsCompeteTree2())
        cout << "��" << endl;
    else
        cout << "����" << endl;
}