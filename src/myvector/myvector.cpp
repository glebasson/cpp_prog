#include "myvector.h"
#include <cstring> // memcpy
#include <utility>
#include <fstream>
#include <random>
#include <algorithm>
#include <iostream>

// move init
template <typename T>
myvector<T>::myvector(myvector &&x) : 
  data(x.data), len(x.len) {
  x.data = nullptr;
}

// copy init
template <typename T>
myvector<T>::myvector(const myvector &x) {
  data = new T[x.len];
  for(int i=0; i<x.len; i++) data[i] = x.data[i];
  len = x.len;
}

template <typename T>
myvector<T>::~myvector() {
  delete[] data;
}

// init empty 
template <typename T>
myvector<T>::myvector() {
  data = nullptr;
}

template <typename T>
T* myvector<T>::begin() {
  return(data);
}

template <typename T>
T* myvector<T>::end() {
  return(data + len);
}

// move operator
template <typename T>
myvector<T>& myvector<T>::operator=(myvector &&x) {
  if (&x == this)
    return this;
  return(myvector(std::move(x)));
}

// copy operator
template <typename T>
myvector<T>& myvector<T>::operator=(const myvector &x) {
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
  T* td = new T[len + 1];
  for(int i=0; i<len; i++) td[i] = std::move(data[i]);
  delete[] data;
  data = td;
  *(data + len) = std::move(value);
  len++;
}

// copy push
template <typename T>
void myvector<T>::push_back(const T &value) {
  T* td = new T[len + 1];
  for(int i=0; i<len; i++) td[i] = data[i];
  delete[] data;
  data = td;
  *(data + len) = value;
  len++;
}

template <typename T>
void myvector<T>::pop_back() {
  len--;
  delete (data + len);
}

template <typename T>
int myvector<T>::size() {
  return(len);
}




int main() {
  // myvector<int> v;
  // v.push_back(10);
  // v.push_back(20);
  // myvector<int> d = v;
  // d.push_back(50);
  // d.push_back(70);
  // d.push_back(80);

  // d.swap(v);

  // myvector<int> d(v);
  // myvector<int> c = std::move(d);
  // std::cout << d.data[2] << std::endl;
  myvector<std::ofstream> v;
  v.push_back(std::ofstream("a"));
  v.push_back(std::ofstream("b"));
  v.push_back(std::ofstream("c"));
  v.push_back(std::ofstream("d"));

  myvector<std::ofstream> d;
  d.push_back(std::ofstream("q"));
  d.push_back(std::ofstream("w"));
  d.push_back(std::ofstream("r"));
  d.push_back(std::ofstream("t"));

  std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(d.begin(), d.end(), g);

  for(int i=0; i<v.size(); i++) d.data[i] << i;

  return(0);
}