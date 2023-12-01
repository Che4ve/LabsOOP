#pragma once

#include <iostream>
#include <vector>

// #define DEBUG

template <class T, size_t ObjectsCount = 1>
class CustomAllocator {
    // Проверочка
    static_assert(!std::is_same_v<T, void>, "Allocator: Type can not be 'void'");
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T *;
        using size_type = std::size_t;
        
        template<typename U>
        struct rebind { using other = CustomAllocator<U, ObjectsCount>; };

        CustomAllocator() : _buffer(nullptr) {
            _buffer = (pointer)malloc(ObjectsCount * sizeof(T));
            if (_buffer == nullptr) {
                throw std::runtime_error("Allocator: Memory allocation failed");
            }
        }
    
        template <class U>
        CustomAllocator(const CustomAllocator<U, ObjectsCount>& other) 
        {
            _storage = other._storage;
            for (int i = 0; i < ObjectsCount; i++) {
                _storage[i] = other._storage.at(i);
                // std::cout << "Cell " << i << " is nullptr" << std::endl;
            }
        }

        ~CustomAllocator() {
            if (_buffer != nullptr) {
                #ifdef DEBUG  
                std::cout << "Freeing _buffer" << std::endl;
                #endif 
                free(_buffer);
            }
        }

        pointer allocate(size_t count_objects) {
            if (_buffer == nullptr) {
                throw std::runtime_error("Allocator: Memory not properly allocated");
            }
            size_t i = 0;
            while (i < ObjectsCount && _storage[i] != nullptr) {
                ++i;
            }
            if (i + count_objects > ObjectsCount) {
                throw std::runtime_error("Allocator: Not enough allocated memory");
            }
            for (size_t j = 0; j < count_objects; j++) {
                reserve(i + j);
            }

            #ifdef DEBUG    
            std::cout << "Allocated " << count_objects << " objects" << std::endl;
            #endif  
            
            return _storage[i];
        }

        void deallocate(T* ptr, std::size_t count_objects) {
            // Nothing to do here // 
            #ifdef DEBUG  
            std::cout << "Deallocating " << count_objects << " objects" << std::endl;
            #endif 
        }

        pointer reserve(size_t index) {
            if (index >= ObjectsCount) {
                throw std::runtime_error("Allocator: Index out of bounds");
            }
            #ifdef DEBUG
            std::cout << "  Cell " << index << " is reserved" << std::endl;
            #endif

            _storage[index] = _buffer + index;
            return _storage[index];
        }

        


    private:
        value_type* _buffer;
        std::vector<pointer> _storage{ ObjectsCount, nullptr };
};

template <class T, class U, size_t ObjectsCount>
bool operator==(const CustomAllocator<T, ObjectsCount>& lhs, const CustomAllocator<U, ObjectsCount>& rhs) {
    // Compare the storage vectors
    return lhs._storage == rhs._storage;
}

template <class T, class U, size_t ObjectsCount>
bool operator!=(const CustomAllocator<T, ObjectsCount>& lhs, const CustomAllocator<U, ObjectsCount>& rhs) {
    return !(lhs == rhs);
}
