#pragma once
#include <iostream>
#include <string>
using namespace std;
struct X {};

void f()
{

}

template <typename F, typename T1, typename T2>
void filp(F f, T1 t1, T2 t2)
{
	f(t1, t2);
}

template <typename F, typename T1, typename T2>
void filp1(F f, T1 &&t1, T2 &&t2) //const������ֵ���Եõ�����
{
	f(t1, t2);
}

template <typename T, typename... Args>
void foo(const T& t,const Args...args) 
{
	cout << sizeof...(Args) << endl;
	cout << sizeof...(args) << endl;
}

template <typename T>
ostream& print(ostream& os, const T &t) //��Argsû��ʱ����
{
	return os << t;
}

template <typename T, typename... Args>
ostream& print(ostream& os,const T &t,const Args&... args)
{
    os << t << " ";
	return print(os, args...);
}

