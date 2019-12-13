#include <iostream>
#include <ostream>
#include <vector>
#include <iterator>
#include <string>
#include <map>
#include <unordered_map>
#include <bits/stl_tempbuf.h>  // for _Temporary_buffer


template<class T, class charT=char, class traits=std::char_traits<charT> >
class myiter : public std::iterator<std::output_iterator_tag, void, void, void, void> {
	std::basic_ostream<charT,traits>* out_stream;
    const charT* delim;
    int n=1;
    int N;
    public:
  	typedef charT char_type;
  	typedef traits traits_type;
 	typedef std::basic_ostream<charT,traits> ostream_type;

 	myiter(ostream_type& s) : out_stream(&s), delim(0), N(1) {}
  	myiter(ostream_type& s, const charT* delimiter, int NN)
    	: out_stream(&s), delim(delimiter), N(NN) {}
  	myiter(const myiter<T,charT,traits>& x)
    	: out_stream(x.out_stream), delim(x.delim), N(x.N) {}
  	~myiter() {}

  	myiter<T,charT,traits>& operator= (const T& value) {
  		if (n%N == 0 ) {
			*out_stream << value;
			if (delim!=0) *out_stream << delim;
		}
		++n;
	    return *this;
  	}

  	myiter<T,charT,traits>& operator*() { return *this; }
  	myiter<T,charT,traits>& operator++() { return *this; }
  	myiter<T,charT,traits>& operator++(int) { return *this; }
};

class record {
	public:
		int id;
		std::string name;

		record(std::string n, int i) : id(i), name(n) {}

		bool operator<(const record &x) const {
			return bool(id < x.id);
		}

    bool operator==(const record &x) const {
      return(id == x.id);
    }

};

template<class T> class MyHash;

template<>
class MyHash<record> {
public:
    size_t operator()(const record &rec) const
    {
        size_t h1 = std::hash<int>()(rec.id);
        return h1;
    }
};

template <class InputIterator1, class InputIterator2, class OutputIterator>
  OutputIterator merge (InputIterator1 first1, InputIterator1 last1,
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
  void inplace_merge (InputIterator first, InputIterator last, InputIterator middle) {
    if (first == middle || middle == last) 
      return;
    typedef typename __gnu_cxx::iterator_traits<InputIterator>::value_type
    _ValueType;
    std::vector<_ValueType> ar(std::distance(first,last));
    merge(first, middle, middle, last, ar.begin());
    std::copy(ar.begin(), ar.end(), first);
    return;
}


template <class InputIterator>
  void merge_sort(InputIterator first, InputIterator last) {
    if (std::distance(first, last) > 1) {
      InputIterator middle = first + std::distance(first, last)/2;

      merge_sort(first, middle);
      merge_sort(middle, last);
      inplace_merge(first, last, middle);
    }
}





int main() {
	std::map<record, int> x { {record("me", 10), 10} };
  std::unordered_map<record, int, MyHash<record>> y { {record("me", 10), 10} };

  std::array<int, 4> a1 = {1, 2, 3, 4};
  std::array<int, 3> a2 = {3, 8, 10};
  std::array<int, 7> a3;  
  // merge(a1.begin(), a1.end(), a2.begin(), a2.end(), a3.begin());

  // for (auto &el : a3) {
  //   std::cout << el << "\n";
  // }

  a3 = {100, 2, 3, 4, 3, 8, 10};
  // std::array<int, 2> qq = {1,2};
  // std::cout << std::distance(qq.begin(), qq.end()) << "\n";

  // inplace_merge(a3.begin(), a3.end(), a3.begin() + a3.size()/2 + 1);
  // std::cout << a3.size()/2 << "\n";
  merge_sort(a3.begin(), a3.end());
  for (auto &el : a3) {
    std::cout << el << "\n";
  }

	return(0);
}