#pragma once
template<unsigned N, unsigned M>
int Compare(const char(&p1)[N], const char(&p2)[M])
{
	return strcmp(p1, p2);
}

template<typename T>
int Compare(const T& a, const T& b)
{
	return a < b;
}
