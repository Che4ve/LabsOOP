#include "../include/thirteen.h"

Thirteen::Thirteen() {
    tenBaseEqiuv = 0;
    symbols.pushBack('0');
}

Thirteen::Thirteen(int tenBaseNum) {
    set(tenBaseNum);
}

Thirteen::Thirteen(const char* str13base) {
    set(str13base);
}

Thirteen::~Thirteen() {
    symbols.clear();
}

void Thirteen::set(int tenBaseNum) {
    symbols.clear();
    tenBaseEqiuv = tenBaseNum;
    if (tenBaseEqiuv == 0) {
        symbols.pushBack('0');
        return;
    }
    while (tenBaseNum > 0) {
        int remainder = tenBaseNum % 13;
        symbols.pushBack(_itouc(remainder));
        tenBaseNum /= 13;
    }
    symbols.reverse();
}

void Thirteen::set(const char* str13base) {
    std::string str = str13base;
    tenBaseEqiuv = 0;
    symbols.clear();
    symbols.set(str);
    for (size_t i = 0; i < symbols.size(); i++) {
        uchar c = symbols[i];
        if (_is13base(c) == false) {
            this->set(0);
            return;
        }
        tenBaseEqiuv += _uctoi(c) * pow(13, symbols.size() - 1 - i);
    }
}

std::string Thirteen::get() {
    return symbols.str();
}

void Thirteen::printNumber() {
    for (int i = 0; i < symbols.size(); i++) {
        printf("%c", symbols[i]);
    }
}

int Thirteen::inTenBase() const {
    return tenBaseEqiuv;
}

bool Thirteen::_is13base(uchar upperChar) {
    return (upperChar >= '0' && upperChar <= '9') || (upperChar >= 'A' && upperChar <= 'C');
}

uchar Thirteen::_itouc(int num) {
    if (num < 0 || num >= 13) {
        return '\0';
    }
    if (num < 10) {
        return num + '0';
    } else {
        return (num % 10) + 'A';
    }
}

int Thirteen::_uctoi(uchar c) {
    if (_is13base(c) == false) {
        return -1;
    }
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else {
        return c - 'A' + 10;
    }
}

Thirteen& Thirteen::operator=(const Thirteen& other) {
    this->tenBaseEqiuv = other.tenBaseEqiuv;
    this->set(this->tenBaseEqiuv);
    return *this;
}

const Thirteen operator+(Thirteen& lhs, const Thirteen& rhs) {
    Thirteen res(lhs.inTenBase() + rhs.inTenBase());
    return res;
}
