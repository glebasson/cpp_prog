#include <iostream>
#include <string>
#include <bits/stdc++.h> 


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
