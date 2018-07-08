void _CreatHuffmanTree(W*array, size_t size, const W& invalid)
    {
        //定义比较器，此处使用的原因是：在此要比较的是权值的大小
        struct Less
        {
            bool operator()(pNode left, pNode right)
            {
                return left->_weight < right->_weight;
            }
        };

        priority_queue<pNode, vector<pNode>, Less> hp;
        //将所有元素先放入到堆中
        for (size_t i = 0; i < size; ++i)
        {
            if (array[i] != invalid)                
                hp.push(new HuffmanTreeNode<W>(array[i]));          
        }
        //堆中没有元素（空堆）
        if (hp.empty())
            _pRoot = NULL;

        //利用堆创建Huffman树
        while ((int)hp.size()>1)
        {
            pNode pLeft = hp.top();
            hp.pop();

            pNode pRight = hp.top();
            hp.pop();

            pNode parent = new HuffmanTreeNode<W>(pLeft->_weight + pRight->_weight);

            parent->_pLeft = pLeft;
            parent->_pRight = pRight;
            hp.push(parent);
        }
        _pRoot = hp.top();
    }