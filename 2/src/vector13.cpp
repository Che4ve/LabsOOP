#include "../include/vector13.h"

Vector13::Vector13() : data(nullptr), vectorSize(0), capacity(0) {}

Vector13::Vector13(const size_t capacity) {
    this->vectorSize = 0;
    this->capacity = capacity;
    reserve(capacity);
}

Vector13::Vector13(std::string str13base) {
    set(str13base);
}

Vector13::~Vector13() {
    delete[] data;
}

void Vector13::set(std::string str13base) {
    for (int i = 0; i < str13base.length(); i++) {
        uchar c = str13base[i];
        if (c == ' ') {
            str13base.erase(str13base.begin() + i);
        } else {
            break;
        }
        
    }
    size_t len = str13base.length();

    vectorSize = 0;
    capacity = len;
    reserve(capacity);
    for (size_t i = 0; i < len; i++) {
        uchar c = str13base[i];
        pushBack(toupper(c));
    }
}

size_t Vector13::size() const {
    return vectorSize;
}
bool Vector13::isEmpty() const {
    return vectorSize == 0;
}

int Vector13::pushBack(uchar c) {
    if (vectorSize >= capacity) {
        reserve(capacity + defaultCapacityReserve);
    }
    data[vectorSize++] = c;
    return 1;
}

int Vector13::reserve(size_t newCapacity) {
    uchar* buffer = new uchar[newCapacity];
    for (size_t i = 0; i < vectorSize; i++) {
        buffer[i] = data[i];
    }
    capacity = newCapacity;
    if (data != nullptr) {
        delete[] data;
    }
    data = buffer;
    return 1;
}

int Vector13::clear() {
    // Delete the dynamic array and free memory
    if (data != nullptr) {
        delete[] data;
    }
    // Reset size and capacity
    vectorSize = 0;
    capacity = 0;
    // Set data pointer to nullptr to prevent accessing deleted memory
    data = nullptr;
    return 1; // Or any suitable return value to indicate success
}



int Vector13::reverse() {
    uchar* buffer = new uchar[vectorSize];
    for (size_t i = 0; i < vectorSize; i++) {
        buffer[i] = data[vectorSize - 1 - i];
    }
    delete[] data;
    data = buffer;
    return 1;
}

std::string Vector13::str() const {
    std::stringstream ss;
    for (size_t i = 0; i < vectorSize; i++) {
        ss << data[i];
    }
    return ss.str();
}

uchar Vector13::operator[](size_t index) {
    if (index >= vectorSize || index < 0) {
        return '\0';
    }
    return data[index];
}
