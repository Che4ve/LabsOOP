#include "../include/thirteen.h"

Thirteen::Thirteen() {
    tenBaseEquiv = 0;
    symbols.pushBack('0');
}

Thirteen::Thirteen(int tenBaseNum) {
    try {
        set(tenBaseNum);
    }
    catch (const std::invalid_argument &e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        set(0);
    }
}

Thirteen::Thirteen(const char* str13base) {
    try {
        set(str13base);
    }
    catch (const std::invalid_argument &e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        set(0);
    }
}

Thirteen::~Thirteen() noexcept {
    symbols.clear();
}

void Thirteen::set(int tenBaseNum) {
    if (tenBaseNum < 0) {
        throw std::invalid_argument("Negative value");
    }
    symbols.clear();
    tenBaseEquiv = tenBaseNum;
    if (tenBaseEquiv == 0) {
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
    tenBaseEquiv = 0;
    symbols.clear();
    symbols.set(str);
    for (size_t i = 0; i < symbols.size(); i++) {
        uchar c = symbols[i];
        if (_is13base(c) == false) {
            throw std::invalid_argument("Invalid 13-digit input");
        }
        tenBaseEquiv += _uctoi(c) * pow(13, symbols.size() - 1 - i);
    }
}

std::string Thirteen::get() const {
    return symbols.str();
}

int Thirteen::inTenBase() const {
    return tenBaseEquiv;
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
    this->tenBaseEquiv = other.tenBaseEquiv;
    this->set(this->tenBaseEquiv);
    return *this;
}
Thirteen& Thirteen::operator+=(const Thirteen& other) {
    this->tenBaseEquiv += other.tenBaseEquiv;
    this->set(this->tenBaseEquiv);
    return *this;
}
Thirteen& Thirteen::operator-=(const Thirteen& other) {
    try {
        this->tenBaseEquiv -= other.tenBaseEquiv;
        this->set(this->tenBaseEquiv);
        return *this;
    } catch (const std::invalid_argument &e) {
        std::cerr << "Subtraction error: " << e.what() << std::endl;
        this->set(0);
        return *this;
    }
}

const Thirteen operator+(const Thirteen& lhs, const Thirteen& rhs) {
    Thirteen res(lhs.inTenBase() + rhs.inTenBase());
    return res;
}
const Thirteen operator-(const Thirteen& lhs, const Thirteen& rhs) {
    Thirteen res(lhs.inTenBase() - rhs.inTenBase());
    return res;
}
bool Thirteen::operator==(const Thirteen& other) const {
    return this->tenBaseEquiv == other.tenBaseEquiv;
}

bool Thirteen::operator>(const Thirteen& other) const {
    return this->tenBaseEquiv > other.tenBaseEquiv;
}
bool Thirteen::operator<(const Thirteen& other) const {
    return this->tenBaseEquiv < other.tenBaseEquiv;
}

