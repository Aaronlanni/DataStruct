//×óÓÒ×ÓÊ÷·Ö¿ª
    bool _IsCompeteTree2(pNode pRoot)
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
            if (pCur->_pLeft)
            {
                if (flag)
                    return false;
                q.push(pCur->_pLeft);
            }
            else
                flag = true;

            if (pCur->_pRight)
            {
                if (flag)
                    return false;
                q.push(pCur->_pRight);
            }
            else
                flag = true;
        }
        return true;
    }