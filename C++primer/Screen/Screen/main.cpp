#include "Screen.h"
#include <iostream>

int main()
{
	Screen scn(2, 2, 'a');
	char (Screen::*ptr)(Screen::pos, Screen::pos)const;
	ptr = &Screen::get;       //成员函数和指针间没有自动转换

	char t = (scn.*ptr)(0,0);
	std::cout << t << std::endl;
	system("pause");
}