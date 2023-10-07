
#include <string.h>
#include <iostream>

#include "../include/thirteen.h"

int main(int argc, char** argv) {
    Thirteen a;

    std::cout << "Enter a in 10-digit base: ";
    int n;
    std::cin >> n;
    
    try {
        a.set(n);
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        a.set(0);
    }

    std::cout 
            << a.inTenBase() << "₁₀" << "  :  " 
            << a.get() << "₁₃" 
            << std::endl;

    Thirteen b;

    std::cout << "Enter b in 13-digit base: ";
    std::string str;
    std::cin >> str;

    try {
        b.set(str.c_str());
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        b.set(0);
    }

    std::cout
            << b.get() << "₁₃" << "  :  " 
            << b.inTenBase() << "₁₀" 
            << std::endl;
    
    Thirteen c;

    c = a - b;

    std::cout << a.get() << " - " 
                << b.get() << " = " 
                << c.get() << std::endl;

    return 0;
}
