#include <utility>
#include <stdio.h>
#include <cassert>

template<typename T> using P = std::pair<T, T>;
template<typename T>
P<T> rotate(const P<T>& vec, int degree) {
    int sign = degree/std::abs(degree);
    assert(degree % 90 == 0);
    if (degree % 360 == 0) return P<T>(vec.first, vec.second);
    if (degree % 180 == 0) return P<T>(-1 * vec.first, -1 * vec.second);
    sign = degree % 90 ? sign * -1 : sign;
    std::cout << vec.first << " " << vec.second << "\n";
    // граничные случаи
    if (vec.first == 0 && ((vec.second > 0 && sign < 0) || (vec.second < 0 && sign > 0)) ) 
        return P<T>(vec.second * sign * -1, 0);
    if (vec.first == 0 && ((vec.second > 0 && sign > 0) || (vec.second < 0 && sign < 0)) ) 
        return P<T>(vec.second * sign * -1, 0);
    if (vec.second == 0 && ((vec.first > 0 && sign < 0) || (vec.first < 0 && sign > 0)) ) 
        return P<T>(0, vec.first * sign);
    if (vec.second == 0 && ((vec.first > 0 && sign > 0) || (vec.first < 0 && sign < 0)) ) 
        return P<T>(0, vec.first * sign);
    
    
    if (sign > 0 && vec.first * vec.second > 0) { // 1 3 qurter
        return P<T>(-1 * vec.second, vec.first);
    }
    if (sign > 0 && vec.first * vec.second < 0) { // 2 4 qurter
        return P<T>(vec.second * -1, vec.first);
    }
    if (sign < 0 && vec.first * vec.second > 0) { // 1 3 qurter
        return P<T>(vec.second, -1 * vec.first);
    }
    if (sign < 0 && vec.first * vec.second < 0) { // 2 4 qurter
        return P<T>(vec.second, -1 * vec.first);
    }
}

