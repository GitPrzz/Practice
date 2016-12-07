#pragma once
#include "Blob.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include <memory>

template <typename T> class BlobPtr;

template <typename T>
bool operator==(const BlobPtr<T> &l , const BlobPtr<T> &r);

template <typename T>
bool operator<(const BlobPtr<T> &l, const BlobPtr<T> &r);

template <typename T>
class BlobPtr
{
	friend bool operator<(const BlobPtr<T> &l, const BlobPtr<T> &r);
	friend bool operator==(const BlobPtr<T> &l, const BlobPtr<T> &r);
	typedef T value_type;
	typedef typename std::vector<T>::size_type size_type;
public:
	BlobPtr():lit(0) {}
	BlobPtr(Blob<T>& a,size_t b = 0):Ptr(a.data), lit(b) , n(0){}
	T& operator*();
	BlobPtr& operator++();
	BlobPtr& operator--();

	BlobPtr operator ++(int);
	BlobPtr operator --(int);
private:
	shared_ptr<std::vector<T>> check(std::size_t, const std::string&);
	size_type n;
	size_type lit;
	std::weak_ptr<std::vector<T>> Ptr;
	//If use weak_ptr 
};

template<typename T>
T& BlobPtr<T>::operator*(){
	shared_ptr<std::vector<T>> p = check(n, "dereference past end");
	return (*p)[n];
}

template <typename T>
shared_ptr<std::vector<T>>
BlobPtr<T>::check(std::size_t i, const std::string& msg)
{
	if (i < 0 || i >= lit)
	{
		throw std::out_of_range(msg);
	}
	return Ptr.lock();
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++()
{
	check(n+1, "end of StrBlob");
	++n;
	return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--()
{
	check(n-1, "end of StrBlob");
	--n;
	return *this
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator--(int)
{
	check(n, "end of StrBlob");
	auto t = *this;
	n--;
	return t;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int )
{
	check(n, "end of StrBlob");
	auto t = *this;
	n++;
	return t;
}

template <typename T>
bool operator==(const BlobPtr<T> &l, const BlobPtr<T> &r)
{
	if (l.Ptr.lock != r.Ptr.lock)
	{
		throw runtime_error("ptrs to different Blobs!");
	}
	return *l == *r
}

template <typename T>
bool operator<(const BlobPtr<T> &l, const BlobPtr<T> &r)
{
	if (l.Ptr.lock != r.Ptr.lock)
	{
		throw runtime_error("ptrs to different Blobs!");
	}
	return *l < *r
}