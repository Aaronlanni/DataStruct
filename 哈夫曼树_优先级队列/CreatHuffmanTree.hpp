void _CreatHuffmanTree(W*array, size_t size, const W& invalid)
    {
        //����Ƚ������˴�ʹ�õ�ԭ���ǣ��ڴ�Ҫ�Ƚϵ���Ȩֵ�Ĵ�С
        struct Less
        {
            bool operator()(pNode left, pNode right)
            {
                return left->_weight < right->_weight;
            }
        };

        priority_queue<pNode, vector<pNode>, Less> hp;
        //������Ԫ���ȷ��뵽����
        for (size_t i = 0; i < size; ++i)
        {
            if (array[i] != invalid)                
                hp.push(new HuffmanTreeNode<W>(array[i]));          
        }
        //����û��Ԫ�أ��նѣ�
        if (hp.empty())
            _pRoot = NULL;

        //���öѴ���Huffman��
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