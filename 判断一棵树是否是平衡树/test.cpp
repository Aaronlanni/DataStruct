void TestTree()
{
    //利用数组
    char array[] = "abd###ce##f";
    BindaryTree<char> bt(array, strlen(array), '#');
    cout << "非空树1（多个结点）---->" ;
    if (bt.IsBalanceTree())
        cout << "平衡" << endl;
    else
        cout << "不平衡" << endl;

    cout << "非空树2（多个结点）---->" ;
    char array1[] = "abd##c";
    BindaryTree<char> bt1(array1, strlen(array1), '#');
    if (bt1.IsBalanceTree())
        cout << "平衡" << endl;
    else
        cout << "不平衡" << endl;

    char array2[] = "a";
    BindaryTree<char> bt2(array2, strlen(array2), '#');
    cout << "非空树3（只有一个结点）---->" ;
    if (bt2.IsBalanceTree())
        cout << "平衡" << endl;
    else
        cout << "不平衡" << endl;

    //空树
    cout << "空树---->";
    BindaryTree<char> bt3;
    if (bt3.IsBalanceTree())
        cout << "平衡" << endl;
    else
        cout << "不平衡" << endl;
}