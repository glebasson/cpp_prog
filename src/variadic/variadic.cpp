#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <cstring> //memcpy


void message(std::ostream& stream, std::string&& pattern){
	stream << pattern;
}

template<typename head>
void message(std::ostream& stream, std::string&& pattern, 
	head&& value){

	std::string::iterator it = std::find(pattern.begin(), pattern.end(), '%');
	stream << std::forward<std::string>(std::string(pattern.begin(), it));
	stream << std::forward<head>(value);
	message(stream, std::forward<std::string>(std::string( it + 1, pattern.end() )));
}

template<typename head, typename... tail>
void message(std::ostream& stream, std::string&& pattern, 
	head&& value, tail&&... args){

	std::string::iterator it = std::find(pattern.begin(), pattern.end(), '%');
	stream << std::forward<std::string>(std::string(pattern.begin(), it));
	stream << std::forward<head>(value);
	message(stream, std::forward<std::string>(std::string( it + 1, pattern.end() )), std::forward<tail>(args)...);
}


// cpy
template<int N, int S, typename AT, typename head>
void cpy(AT &arr, head first){
	for(int i=0; i<S; i++) arr[N*S + i] = first[i];
}

template<int N, int S, typename AT, typename head, typename... Args>
void cpy(AT &arr, head first, Args... tail){
	for(int i=0; i<S; i++) arr[N*S + i] = first[i];
	cpy<N+1, S, AT, Args...>(arr, tail...);
}


// concat
template<typename head, typename... Args>
struct concantinator {
	typedef typename head::value_type arraytype;
	static const size_t S = std::tuple_size<head>::value;
	typedef std::array<arraytype, S * (sizeof...(Args) + 1)> bigarray;


	static void cat(bigarray& arr, head a, Args... tail){
		cpy<0, S, bigarray, Args...>(arr, a, tail...);
	}
};

template<typename... Args>
typename concantinator<Args...>::bigarray
cat(Args... tail){
	typedef typename concantinator<Args...>::bigarray bigarr;
	bigarr out;
	concantinator<Args...>::cat(out, tail...);
	return(out);
}

// int main() {
// 	std::array<int, 3> a = { 1, 2, 3};
// 	std::array<int, 3> b = { 1, 2, 3};
// 	std::array<int, 3> c = { 5, 6, 8};
// 	std::array<int, 9> d = cat(a, b, c);
// 	for(int i = 0; i<9; i++)std::cout << d[i] << std::endl;
// }