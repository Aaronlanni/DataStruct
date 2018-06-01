#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<stack>
#include<assert.h>
using namespace std;
bool IsMatchBrackets(char c)//ÅÐ¶ÏÊÇ·ñÎªÀ¨ºÅ
{
	if (c == '(' || c == ')' || c == '{' || c == '}'
		|| c == '<' || c == '>' || c == '[' || c == ']')
		return true;
	return false;
}
bool MatchBrackets(char*pStr)
{
	assert(pStr);//ÅÐ¶Ï´«¹ýÀ´µÄ×Ö·û´®ÊÇ·ñÎª¿Õ
	stack<char> s;
	size_t len = strlen(pStr);
	for (int i = 0; i < len; ++i)
	{
		if (false ==IsMatchBrackets(pStr[i]))//²»ÊÇÀ¨ºÅµÄÇé¿ö
		{
			continue;
		}
			

		else//ÅÐ¶ÏÊÇÀ¨ºÅµÄÎÊÌâ
		{
			//×óÀ¨ºÅ
			if (pStr[i] == '(' || pStr[i] == '{' || pStr[i] == '['
				|| pStr[i] == '<')
				s.push(pStr[i]);
			else//ÓÒÀ¨ºÅ
			{
				if (s.empty())//ÅÐ¶ÏÕ»ÖÐÎª¿Õ
				{
					cout << "ÓÒÀ¨ºÅ¶àÓà×óÀ¨ºÅ" << endl;
					return 0;
				}

				else//·Ç¿Õ
				{
					if ((pStr[i] == ')'&&s.top() == '(')
						|| (pStr[i] =='}'&&s.top() == '{')
						||(pStr[i] == ']'&&s.top() == '[')
						||(pStr[i] == '>'&&s.top() == '<'))//À¨ºÅÆ¥Åä
					{
						cout << "ÍêÈ«Æ¥Åä" << endl;
						s.pop();
						//return true;
					}
					else//À¨ºÅ²»Æ¥Åä
					{
						cout << "À¨ºÅ´ÎÐòÓÐÎÊÌâ" << endl;
						return false;
					}
				}
			}
		}

	}
	if (true ==s.empty())
	{
		cout << "ÍêÈ«Æ¥Åä" << endl;
		return true;
	}
	else
	{
		cout << "×óÀ¨ºÅ¶àÓÚÓÒÀ¨ºÅ" << endl;
		return false;
	}
}
int main()
{
	char a[] = "(())abc{[(])}"; // ×óÓÒÀ¨ºÅ´ÎÐòÆ¥Åä²»ÕýÈ·
	char b[] = "(()))abc{[]}"; // ÓÒÀ¨ºÅ¶àÓÚ×óÀ¨ºÅ
	char c[] = "(()()abc{[]}"; // ×óÀ¨ºÅ¶àÓÚÓÒÀ¨ºÅ
	char d[] = "(())abc{[]()}"; // ×óÓÒÀ¨ºÅÆ¥ÅäÕýÈ·
	MatchBrackets(a);
	MatchBrackets(b);
	MatchBrackets(c);
	MatchBrackets(d);
	system("pause");
	return 0;
}
