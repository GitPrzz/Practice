#include "Token.h"
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	string a = "abc";
	string b = "def";
	Token t;
	t = a;
	cout << t << endl;
	t = b;
	cout << t << endl;
	system("pause");
	return 0;
}
