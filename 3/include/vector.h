#include <iostream>

template <typename T>
class Vector {
    public:
        Vector() : size(0), capacity(10), data(new T[capacity]) {}

        // Copy constructor
        Vector(const Vector& other) : size(other.size), capacity(other.capacity), data(new T[capacity]) {
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }

        // Destructor
        ~Vector() {
            delete[] data;
        }

        // Push an element into the vector
        void push_back(const T& element) {
            if (size >= capacity) {
                expand();
            }
            data[size++] = element;
        }

        // Delete an element at a specific index
        void erase(int index) {
            if (index < 0 || index >= size) {
                throw std::out_of_range("Index out of range");
            }

            for (int i = index; i < size - 1; i++) {
                data[i] = data[i + 1];
            }

            size--;

            // Optional: Shrink the capacity if needed
            if (size < capacity / 2) {
                shrink();
            }
        }

        // Get the size of the vector
        int get_size() const {
            return size;
        }

        // Get an element at a specific index
        T& operator[](int index) {
            if (index < 0 || index >= size) {
                throw std::out_of_range("Index out of range");
            }
            return data[index];
        }

        T* begin() {
            return data;
        }

        T* end() {
            return data + size;
        }

    private:
        int size;
        int capacity;
        T* data;

        // Expand the capacity of the vector
        void expand() {
            capacity *= 2;
            T* new_data = new T[capacity];
            for (int i = 0; i < size; i++) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
        }

        // Shrink the capacity of the vector
        void shrink() {
            capacity /= 2;
            T* new_data = new T[capacity];
            for (int i = 0; i < size; i++) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
        }
};