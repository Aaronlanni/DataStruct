bool _IsCompeteTree(pNode pRoot)
    {
        if (NULL == pRoot)
            return true;
        bool flag = false;
        pNode pCur = NULL;
        queue<pNode> q;
        q.push(pRoot);
        while (!q.empty())
        {
            pCur = q.front();
            q.pop();
            if (!flag)
            {
                if (pCur->_pLeft&&pCur->_pRight)
                {
                    q.push(pCur->_pLeft);
                    q.push(pCur->_pRight);
                }
                //当前结点存在左孩子，因此之后的结点不能存在右孩子（同一层上）
                if (pCur->_pLeft&&pCur->_pRight == NULL)
                {
                    q.push(pCur->_pLeft);
                    flag = true;
                }
                if (pCur->_pLeft == NULL&&pCur->_pRight)
                    return false;
            }
            else
            {
                if (pCur->_pLeft || pCur->_pRight)
                    return false;
            }
        }
        return true;
    }