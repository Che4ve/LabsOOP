
#include <string.h>
#include <iostream>

#include "../include/thirteen.h"

int main(int argc, char** argv) {
    Thirteen number;

    std::cout << "Enter number in 13-digit base: ";
    std::string str;
    std::cin >> str;

    number.set(str.c_str());

    std::cout 
            << number.get() << "₁₃" << "  :  " 
            << number.inTenBase() << "₁₀" 
            << std::endl;
    
    std::cout << "Enter number in 10-digit base: ";
    int n;
    std::cin >> n;

    number.set(n);

    std::cout 
            << number.inTenBase() << "₁₀" << "  :  " 
            << number.get() << "₁₃" 
            << std::endl;
    
    return 0;
}
