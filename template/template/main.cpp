#include <cstdio>
#include "Compare.h"
#include "Blob.h"
#include <iostream>
using namespace std;
int main()
{
	//int a = 10, b = 100;
	//cout << (Compare(a, b) ? 'a' : 'b') << endl;

	Blob<int> ptr = { 1,2,4,5 };
	cout << ptr.back() << endl;
	cout << ptr.front() << endl;
	ptr.push_back(10);
	ptr.show();
	system("pause");
}