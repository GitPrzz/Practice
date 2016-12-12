#include <cstdio>
#include <cstring>
#include <iostream>
#include <functional>
#include <regex>

using namespace std;
/*
可以把正则表达式看成多个小的表达式
*/
bool valid(const smatch& s)
{
	if (s[1].matched)
	{
		return s[3].matched && (s[4].matched == 0 || s[4].str() == " ");
	}
	else
	{
		return !s[3].matched && s[4].str() == s[6].str();
	}
}

void get_Phone()
{
	string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
	regex r(phone);
	string s;
	while (getline(cin, s))
	{
		for (sregex_iterator it(s.begin(), s.end(), r), end_it; it != end_it; ++it)
		{
			if (valid(*it))
				cout << "valid " << it->str() << endl;
			else
				cout << "notvalid " << it->str() << endl;
		}
	}
}

void replace()
{
	string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
	regex r(phone);
	//$跟子表达式的索引号
	string ftm = "$2,$5,$7";
	string s = "(908) 555-1900";
	cout << regex_replace(s, r, ftm) << endl;
}

int main()
{
	replace();
	system("pause");
}