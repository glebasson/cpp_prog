#ifndef MYmyvector
#define MYmyvector

#include <bits/stdc++.h>

template <typename T>
class myvector {
public:
	// empty init
	myvector();

	// move init
	myvector(myvector &&x);

	// copy init
	myvector(const myvector &x);

	~myvector();

	// move =
	myvector& operator=(myvector &&x);

	// copy =
	myvector& operator=(const myvector& x);

	// move swap
	void swap(T &a, T &b);

	T* begin();
	T* end();

	// move  
	void push_back(T&& value);

	// copy
	void push_back(const T &value);

	void pop_back();
	int size();

	void swap(myvector &x) {
		T* tmp = new T[len];
		for(int i=0; i<len; i++) data[i] = tmp[i];
		delete[] data;
		data = new T[x.len];
		for(int i=0; i<x.len; i++) data[i] = x.data[i];
		delete[] x.data;
		x.data = new T[len];
		for(int i=0; i<len; i++) x.data[i] = tmp[i];
		int tmpl = len;
		len = x.len;
		x.len = tmpl;
	}

	void erase(int pos) {
		for(int i=0; i<len; i++) delete data[i];
		len = pos + 1;
	}

	T* data;
	int len = 0;
};

#endif