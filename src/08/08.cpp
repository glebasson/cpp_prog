#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

template <class InputIterator1, class InputIterator2, class OutputIterator>
  OutputIterator mymerge (InputIterator1 first1, InputIterator1 last1,
                        InputIterator2 first2, InputIterator2 last2,
                        OutputIterator result) {
  while (true) {
    if (first1 == last1) return std::copy(first2, last2, result);
    if (first2 == last2) return std::copy(first1, last1, result);
    // magic of post increment
    *result++ = (*first2 < *first1) ? *first2++ : *first1++;
  }
}


template <class InputIterator>
  void myinplace_merge (InputIterator first, InputIterator last, InputIterator middle) {
    if (first == middle || middle == last) 
      return;
    typedef typename std::iterator_traits<InputIterator>::value_type
    _ValueType;
    std::vector<_ValueType> ar(std::distance(first,last));
    mymerge(first, middle, middle, last, ar.begin());
    std::copy(ar.begin(), ar.end(), first);
    return;
}


template <class InputIterator>
  void merge_sort(InputIterator first, InputIterator last) {
    if (std::distance(first, last) > 1) {
      InputIterator middle = first + std::distance(first, last)/2;

      merge_sort(first, middle);
      merge_sort(middle, last);
      myinplace_merge(first, last, middle);
    }
}

template <class InputIterator>
void fastmergesort(InputIterator first, InputIterator last) {
    int n = std::thread::hardware_concurrency();
    // int n = 2;
    int delta = distance(first, last)/n;
    typedef pair<InputIterator,InputIterator> itpair;
    vector<itpair> itv(n);
    for(int i=0; i < n-1; ++i) {
        itv[i] = itpair(first + delta * i, first + delta * (i+1));
    }
    itv[n-1] = itpair(itv[n-2].second, last);
    vector<thread> vth;
    for(int i=0; i < n; ++i) {
        vth.push_back(thread(merge_sort<InputIterator>, itv[i].first, itv[i].second));
    }
    for(int i=0; i < n; ++i) {
        vth[i].join();
    }
    for(int i=1; i < n; ++i) {
        myinplace_merge(first, itv[i].second, itv[i].first);
    }

}

int main(int argc, char** argv) {
    int N = atoi(argv[1]);
    vector<int> v(N);
    for(int i=0; i<N; ++i) {
        v[i] = i;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);

    std::chrono::time_point<std::chrono::system_clock> now;
    now = std::chrono::system_clock::now();
    fastmergesort(v.begin(), v.end());
    cout <<  (std::chrono::system_clock::now() - now).count() << "\n";

    now = std::chrono::system_clock::now();
    std::shuffle(v.begin(), v.end(), g);
    merge_sort(v.begin(), v.end());
    cout << (std::chrono::system_clock::now() - now).count() << "\n";
}