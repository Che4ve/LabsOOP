
#include <string.h>
#include <iostream>

#include "../include/thirteen.h"

int main(int argc, char** argv) {
    Thirteen number("ab");
    Thirteen a("baba");
    Thirteen b("abc");
    Thirteen c("ca");
    std::cout << "Hello, World!" << std::endl;

    number = a + b;

    std::cout << number.get() << "  :  " << number.inTenBase() << std::endl;
    
    return 0;
}
