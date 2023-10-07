#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "./vector13.h"

class Thirteen {
private:
    Vector13 symbols;
    int tenBaseEquiv;

    bool _is13base(uchar upperChar);
    uchar _itouc(int num);
    int _uctoi(uchar c);
    
public:
    Thirteen();
    Thirteen(int tenBaseNum);
    Thirteen(const char* str13base);
    ~Thirteen() noexcept;

    void set(int tenBaseNum);
    void set(const char* str13base);
    std::string get() const;

    int inTenBase() const;

    Thirteen& operator=(const Thirteen& other);
    Thirteen& operator+=(const Thirteen& other);
    Thirteen& operator-=(const Thirteen& other);

    friend const Thirteen operator+(const Thirteen& lhs, const Thirteen& rhs);
    friend const Thirteen operator-(const Thirteen& lhs, const Thirteen& rhs);

    bool operator==(const Thirteen& other) const;
    bool operator>(const Thirteen& other) const;
    bool operator<(const Thirteen& other) const;
};


