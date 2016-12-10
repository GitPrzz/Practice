#pragma once
#include <string>
#include <iostream>
template<unsigned N, unsigned M>
int Compare(const char(&p1)[N], const char(&p2)[M])
{
	return strcmp(p1, p2);
}

template<typename T>
int Compare(const T& a, const T& b)
{
	std::cout << "normal" << std::endl;
	return a < b;
}

template<>
int Compare(const char* const &a, const char* const &b)
{
	std::cout << "special" << std::endl;
	return strcmp(a, b);
}
