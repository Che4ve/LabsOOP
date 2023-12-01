// 5.    Очередь  std::vector
#include <iostream>
#include <cmath>
#include <map>
#include <cstddef>
#include <utility>
#include <regex.h>
#include "./include/myqueue.hpp"
#include "./include/allocator.hpp"

typedef std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, int>, 10>>
    map_customly_allocated;


template <int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};

template <>
struct Factorial<0> {
    static const int value = 1;
};

template <typename T, T... Is>
map_customly_allocated generate_factorials(std::integer_sequence<T, Is...> _int_seq) {
    map_customly_allocated result;
    ((result.insert( std::make_pair(Is, (int)Factorial<Is>::value) )), ... );
    return result;  
}

int main() {
    
    map_customly_allocated factorials = generate_factorials(std::make_integer_sequence<int, 10>{});

    for (int i = 0; i < factorials.size(); i++) {
        std::cout << "Factorial of " << i << " is " << factorials[i] << std::endl;
    }

    MyQueue<int> queue;
    for (int i = 0; i < factorials.size(); i++) {
        queue.push(factorials[i]);
    }

    for (auto &node : queue) {
        std::cout <<node.data << std::endl;
    }

    return 0;
}
