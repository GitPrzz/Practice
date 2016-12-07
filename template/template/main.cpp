#include <cstdio>
#include "Compare.h"
#include "Blob.h"
#include "BlobPtr.h"
#include <iostream>
using namespace std;
int main()
{
	//int a = 10, b = 100;
	//cout << (Compare(a, b) ? 'a' : 'b') << endl;

	Blob<int> ptr = { 1,2,4,5 };
	BlobPtr<int> p(ptr, ptr.size());
	cout << *p << endl;
	cout << *(++p) << endl;
	system("pause");
}