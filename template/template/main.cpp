#include <cstdio>
#include "HashandSales.h"
#include <iostream>
using namespace std;
int main()
{
	Sales_data a("C++", 10, 99.8);
	Sales_data b("Java", 5, 233);
	cout << hash<Sales_data>()(a) << endl;
	cout << hash<Sales_data>()(b) << endl;
	system("pause");
}