#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "./vector13.h"

class Thirteen {
private:
    Vector13 symbols;
    int tenBaseEqiuv;

    bool _is13base(uchar upperChar);
    uchar _itouc(int num);
    int _uctoi(uchar c);
    

public:
    Thirteen();
    Thirteen(int tenBaseNum);
    Thirteen(const char* str13base);
    ~Thirteen();

    void set(int tenBaseNum);
    void set(const char* str13base);
    std::string get();

    void printNumber();
    int inTenBase() const;

    Thirteen& operator=(const Thirteen& other);
    friend const Thirteen operator+(Thirteen& lhs, const Thirteen& rhs);

};


