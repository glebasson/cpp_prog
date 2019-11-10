#include "myvector.h"
#include <cstring> // memcpy
#include <utility>
#include <fstream>
#include <random>
#include <algorithm>

// move init
template <typename T>
myvector<T>::myvector(myvector &&x) : 
  data(x.data), len(x.len), capacity(x.capacity) {
  x.data = nullptr;
}

// copy init
template <typename T>
myvector<T>::myvector(const myvector &x) {
  data = new T[x.capacity];
  memcpy(data, x.data, sizeof(T) * x.len);
  len = x.len;
  capacity = x.capacity;
}

template <typename T>
myvector<T>::~myvector() {
  delete[] data;
}

// init empty with fixed size
template <typename T>
myvector<T>::myvector(int maxsize) {
  data = new T[maxsize];
  capacity = maxsize;
}

template <typename T>
T* myvector<T>::begin() {
  return(data);
}

template <typename T>
T* myvector<T>::end() {
  return(data + len - 1);
}

// move operator
template <typename T>
myvector<T>& myvector<T>::operator=(myvector &&x) {
  if (&x == this)
    return this;
  return(myvector(x));
}

// copy operator
template <typename T>
myvector<T>& myvector<T>::operator=(const myvector& x) {
  if (&x == this)
    return this;
  return(myvector(x));
}

template <typename T>
void myvector<T>::swap(T &a, T &b) {
  T tmp(std::move(a));
  a = std::move(b);
  b = std::move(tmp);
}

// move push
template <typename T>
void myvector<T>::push_back(T&& value) {
  *(data + len) = std::move(value);
  len++;
}

// copy push
template <typename T>
void myvector<T>::push_back(const T &value) {
  *(data + len) = value;
  len++;
}

template <typename T>
T& myvector<T>::pop_back() {
  len--;
  return *(data + len);
}

template <typename T>
int myvector<T>::size() {
  return(len);
}




int main() {
  myvector<std::ofstream> v(4);
  v.push_back(std::ofstream("a"));
  v.push_back(std::ofstream("b"));
  v.push_back(std::ofstream("c"));
  v.push_back(std::ofstream("d"));

  std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);

    while(v.size())
      v.pop_back() << v.size(); 

  return(0);
}