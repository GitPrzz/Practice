#include <cstdio>
#include "Compare.h"
#include <iostream>
using namespace std;
int main()
{
	int a = 10, b = 100;
	cout << (Compare(a, b) ? 'a' : 'b') << endl;
	system("pause");
}