#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>

typedef unsigned char uchar;

const size_t defaultCapacityReserve = 8;

class Vector13 {
    private:
        uchar* data;
        size_t vectorSize;
        size_t capacity;

        
    public:
        Vector13();
        Vector13(const size_t capacity);
        Vector13(std::string str13base);
        ~Vector13();

        void set(std::string str13base);

        size_t size() const;
        bool isEmpty() const;
        std::string str() const;

        int pushBack(uchar c);

        int reserve(size_t capacity);
        int clear();
        
        int reverse();

        

        uchar operator[](size_t index);

};
