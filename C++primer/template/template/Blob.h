#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <functional>
#include <cstdio>
#pragma once
using namespace std;
template <typename T> class Blob;
template <typename T> class BlobPtr;


template <typename T>
class Blob
{
	friend class BlobPtr<T>;
public:
	typedef T value_type;
	typedef typename std::vector<T>::size_type size_type;
	 Blob();
	Blob(initializer_list<T> l);
	size_type size() const { return data->size(); }
	bool empty() const { return date->empty(); }
	void push_back(const T& t) { data->push_back(t); }
	void pop_back();
	void show();
	T& back();
	T& front();
	T& operator[](size_type i);
private:
	std::shared_ptr<std::vector<T>> data;
	void check(size_type i, const string &msg) const;
};

template <typename T> 
Blob<T>::Blob():data(make_shared<vector<T>>()) {}

template <typename T>
Blob<T>::Blob(initializer_list<T> l) : data(make_shared<vector<T>>(l)) {}

template <typename T>
inline T& Blob<T>::front()
{
	check(0, "front on empty");
	return data->front();
}

template<typename T>
inline void Blob<T>::check(size_type i, const string & msg) const
{
	if (i > data->size()) {
		cout << msg << endl;
		return ;
	}
}
template <typename T>
T& Blob<T>::back()
{
	check(0, "back on empty");
	return data->back();
}

template <typename T>
void Blob<T>::pop_back()
{
	check(0, "back on empty");
	data->pop_back();
}

template<typename T>
inline void Blob<T>::show()
{
	for (int i = 0; i < size(); i++)
	{
		cout << (*data)[i] << " ";
	}
	cout << endl;
}

template <typename T>
T& Blob<T>::operator[](size_type i)
{
	return (*data)[i];
}