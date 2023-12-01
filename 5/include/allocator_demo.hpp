#pragma once

#include <iostream>
#include <vector>

/*  === STL ===
template<class T>
class Allocator 
{
    typedef T value_type;
    Allocator(аргументы конструктора);
    template <class T> 
    Allocator(const <T>& other);
    T* allocate(std::size_t count_objects);
    void deallocate(T* ptr, std::size_t count_objects);
};

template<class T, class U>
bool operator==(const Allocator<T>&, const Allocator<U>&);
template<class T, class U>
bool operator!=(const Allocator<T>&, const Allocator<U>&);
*/

#define DEBUG

template <class T, uint32_t ObjectsCount = 1>
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

        CustomAllocator() = default;

        template <class U>
        CustomAllocator(const CustomAllocator<U, ObjectsCount>& other) 
        {
            _storage = other._storage;
            for (int i = 0; i < ObjectsCount; i++) {
                _storage[i] = other._storage.at(i);
                // std::cout << "Cell " << i << " is nullptr" << std::endl;
            }
        }

        pointer allocate(size_t count_objects) {
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
        }

        pointer reserve(size_t index) {
            if (index + 1 > ObjectsCount) {
                throw std::runtime_error("Allocator: Index out of bounds");
            }
            #ifdef DEBUG
            std::cout << "  Cell " << index << "is reserved" << std::endl;
            #endif

            _storage[index] = reinterpret_cast<T*>(1);
            return _storage[index];
        }

        


    private:
        value_type _buffer[ObjectsCount]{};
        std::vector<pointer> _storage{ ObjectsCount, nullptr };
};

template <class T, class U, uint32_t Count>
bool operator==(const CustomAllocator<T, Count>& lhs, const CustomAllocator<U, Count>& rhs) {
    // Compare the storage vectors
    return lhs._storage == rhs._storage;
}

template <class T, class U, uint32_t Count>
bool operator!=(const CustomAllocator<T, Count>& lhs, const CustomAllocator<U, Count>& rhs) {
    // Use the opposite of the == operator
    return !(lhs == rhs);
}