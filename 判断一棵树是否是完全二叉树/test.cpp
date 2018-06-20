void TestTree()
{
    char array[] = "abd###ce##f";
    BindaryTree<char> bt(array, strlen(array), '#');
    //树存在
    cout << "非空树1:"<<endl;
    if (bt.IsCompeteTree())
        cout << "是" << endl;
    else
        cout << "不是" << endl;

    if (bt.IsCompeteTree1())
        cout << "是" << endl;
    else
        cout << "不是" << endl;

    if (bt.IsCompeteTree2())
        cout << "是" << endl;
    else
        cout << "不是" << endl;

    char array1[] = "abd##c##f";
    BindaryTree<char> bt2(array1, strlen(array1), '#');
    //树存在
    cout << "非空树2:" << endl;
    if (bt2.IsCompeteTree())
        cout << "是" << endl;
    else
        cout << "不是" << endl;

    if (bt2.IsCompeteTree1())
        cout << "是" << endl;
    else
        cout << "不是" << endl;

    if (bt2.IsCompeteTree2())
        cout << "是" << endl;
    else
        cout << "不是" << endl;

    //空树
    BindaryTree<char> bt1;
    cout << "空树:"<<endl;
    if (bt1.IsCompeteTree())
        cout << "是" << endl;
    else
        cout << "不是" << endl;

    if (bt1.IsCompeteTree1())
        cout << "是" << endl;
    else
        cout << "不是" << endl;

    if (bt1.IsCompeteTree2())
        cout << "是" << endl;
    else
        cout << "不是" << endl;
}