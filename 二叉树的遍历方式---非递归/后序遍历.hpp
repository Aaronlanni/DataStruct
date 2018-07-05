void _PostOrder_No1(pNode pRoot)
    {
        if (NULL == pRoot)
            return;
        pNode pCur = pRoot;
        pNode pTop = NULL;
        pNode Prev = NULL;
        stack<PNode> s;
        while (pCur||!s.empty())
        {
            //左子树入栈
            while (pCur)
            {
                s.push(pCur);
                pCur = pCur->_pLeft;
            }
            //左子树入栈之后，取栈顶元素
            pTop = s.top();

            //判断栈顶元素是否有右子树
            //右子树不存在，且右子树没有被访问
            if (NULL == pTop->_pRight || Prev == pTop->_pRight)
            {
                //访问并弹出
                cout << pTop->_data << " ";
                Prev = pTop;
                s.pop();
            }
            else
                pCur = pTop->_pRight;
        }
    }



void _PostOrder_No2(pNode pRoot)
    {
        if (NULL == pRoot)
            return;
        pNode pCur = pRoot;
        pNode Prev = NULL;
        stack<PNode> s;
        while (pCur || !s.empty())
        {
            //左子树入栈
            //这块pCur != Prev改变了pCur的指向，因此是为了防止循环入栈
            while (pCur&&pCur != Prev)
            {
                s.push(pCur);
                pCur = pCur->_pLeft;
            }
            //这样防止形成死循环
            if (s.empty())
                return;
            //左子树入栈之后，取栈顶元素
            pCur = s.top();

            //判断栈顶元素是否有右子树
            //右子树不存在，且右子树没有被访问
            if (NULL == pCur->_pRight || Prev == pCur->_pRight)
            {
                //访问并弹出
                cout << pCur->_data << " ";
                Prev = pCur;
                s.pop();
            }
            else
                pCur = pCur->_pRight;
        }
    }