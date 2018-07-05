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
            //��������ջ
            while (pCur)
            {
                s.push(pCur);
                pCur = pCur->_pLeft;
            }
            //��������ջ֮��ȡջ��Ԫ��
            pTop = s.top();

            //�ж�ջ��Ԫ���Ƿ���������
            //�����������ڣ���������û�б�����
            if (NULL == pTop->_pRight || Prev == pTop->_pRight)
            {
                //���ʲ�����
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
            //��������ջ
            //���pCur != Prev�ı���pCur��ָ�������Ϊ�˷�ֹѭ����ջ
            while (pCur&&pCur != Prev)
            {
                s.push(pCur);
                pCur = pCur->_pLeft;
            }
            //������ֹ�γ���ѭ��
            if (s.empty())
                return;
            //��������ջ֮��ȡջ��Ԫ��
            pCur = s.top();

            //�ж�ջ��Ԫ���Ƿ���������
            //�����������ڣ���������û�б�����
            if (NULL == pCur->_pRight || Prev == pCur->_pRight)
            {
                //���ʲ�����
                cout << pCur->_data << " ";
                Prev = pCur;
                s.pop();
            }
            else
                pCur = pCur->_pRight;
        }
    }