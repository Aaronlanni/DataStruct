bool _IsCompeteTree1(pNode pRoot)
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

            //当前结点只有右----->不是
            if (pCur->_pLeft == NULL&&pCur->_pRight)
                return false;
            //当前结点只有左或者左右都不存在----->判断当前结点的下一个结点
            //判断当前结点的下一个结点
            if (flag&&(pCur->_pLeft != NULL || pCur->_pRight != NULL))
                return false;

            if (pCur->_pLeft == NULL || pCur->_pRight == NULL)
            {
                flag = true;
            }

            if (pCur->_pLeft)
                q.push(pCur->_pLeft);
            if (pCur->_pRight)
                q.push(pCur->_pRight);

            q.pop();
        }
        return true;
    }