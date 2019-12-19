#ifndef MYmyvector
#define MYmyvector

#include <bits/stdc++.h>

/**
 * \brief
 * Реализация вектора
 * \date 2019-12-19
 *
 * Развернутое описание
 *
 */
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


	T* begin();
	T* end();

	// move  
	void push_back(T&& value);

	// copy
	void push_back(const T &value);

	void pop_back();
	int size();

	void swap(myvector &x) {
		std::swap(data, x.data);
		std::swap(len, x.len);
	}

	void erase(int pos) {
		for(int i=0; i<len; i++) delete data[i];
		len = pos + 1;
	}

	T* data;
	int len = 0;
};

template <typename T>
void swap(T &a, T &b);
#endif