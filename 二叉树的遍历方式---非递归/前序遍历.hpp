void _FrontOrder_Nor1(pNode pRoot)
    {
        if (NULL == pRoot)
            return;
        stack<pNode> s;
        s.push(pRoot);
        while (!s.empty())
        {
            pNode pCur = s.top();
            cout << pCur->_data << " ";
            s.pop();
            if (pCur->_pRight)
                s.push(pCur->_pRight);
            if (pCur->_pLeft)
                s.push(pCur->_pLeft);
        }
    }



void _FrontOrder_Nor2(pNode pRoot)
    {
        if (NULL == pRoot)
            return;
        stack<pNode> s;
        s.push(pRoot);
        while (!s.empty())
        {
            pNode pCur = s.top();
            s.pop();
            while (pCur)
            {
                cout << pCur->_data << " ";
                if (pCur->_pRight)
                    s.push(pCur->_pRight);
                pCur = pCur->_pLeft;
            }
        }
    }



