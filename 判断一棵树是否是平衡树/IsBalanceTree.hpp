//ÅÐ¶ÏÒ»¿ÃÊ÷ÊÇ·ñÊÇÆ½ºâ¶þ²æÊ÷
    bool IsBalanceTree()
    {
        if (_IsBalanceTree(_pRoot))
            return true;
        else
            return false;
    }
    bool _IsBalanceTree(pNode pRoot)
   {
        if (pRoot == NULL)
            return true;
        if (pRoot->_pLeft == NULL&&pRoot->_pRight == NULL)
            return true;
        int Left = _Height(pRoot->_pLeft);
        int Right = _Height(pRoot->_pRight);
        return abs(Left - Right) < 1;
    }
    size_t _Height(pNode pRoot)
    {
        if (NULL == pRoot)
            return 0;

        if (NULL == pRoot->_pLeft&&NULL == pRoot->_pRight)
            return 1;

        size_t left = _Height(pRoot->_pLeft);
        size_t right = _Height(pRoot->_pRight);
        return left >= right ? left + 1 : right + 1;
    }