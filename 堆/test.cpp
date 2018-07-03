void Test()
{
    int array[] = { 53, 17, 78, 9, 45, 65, 87, 23 };
    Heap<int> hp(array,sizeof(array)/sizeof(*array));//此处默认为小堆
    cout << hp.Top() << endl;
    hp.Push(98);
    cout << hp.Top() << endl;
    cout << hp.Size() << endl;
    /*hp.Pop();
    cout << hp.Top() << endl;
    hp.Pop();
    cout << hp.Top() << endl;
    hp.Pop();
    cout << hp.Top() << endl;
    hp.Pop();
    cout << hp.Top() << endl;
    hp.Pop();
    cout << hp.Top() << endl;
    hp.Pop();
    cout << hp.Top() << endl;*/
}