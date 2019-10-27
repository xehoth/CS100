/**
 * Copyright (c) 2019, Hongtu Xu
 * All rights reserved.
 *
 * @author Hongtu Xu
 * @date 2019-10-17
 */
#include <iostream>
#include <algorithm>
#include <cstring>

class DynamicArray {
   public:
    using ValueType = int;

    DynamicArray() : data(new ValueType[capacity = 5]()), size() {}
    DynamicArray(const DynamicArray &other) {
        data = new ValueType[capacity = other.capacity]();
        size = other.size;
        memcpy(data, other.data, sizeof(ValueType) * size);
    }

    ~DynamicArray() { release(); }

    DynamicArray &operator=(const DynamicArray &other) {
        if (this == &other) return *this;
        release();
        data = new ValueType[capacity = other.capacity]();
        size = other.size;
        memcpy(data, other.data, sizeof(ValueType) * size);
        return *this;
    }

    void assign(const DynamicArray &other) { *this = other; }

    int getSize() const { return size; }

    int getCapacity() const { return capacity; }

    int at(int index) const { return data[index]; }

    ValueType &operator[](int i) { return data[i]; }
    const ValueType &operator[](int i) const { return data[i]; }

    void push(const int item) { push_back(item); }

    void push_back(const ValueType &x) {
        data[size++] = x;
        if (size >= capacity) {
            std::cout << "(resize) from " << capacity << " to " << capacity * 2 << '\n';
            capacity <<= 1;
            ValueType *np = new ValueType[capacity]();
            memcpy(np, data, sizeof(ValueType) * size);
            delete[] data;
            data = np;
        }
    }

    bool remove(const int index) {
        if (index < 0 || index >= size) return false;
        memmove(data + index, data + index + 1, sizeof(ValueType) * (size - index - 1));
        size--;
        return true;
    }

   private:
    ValueType *data;
    int size, capacity;

    void release() {
        delete[] data;
        data = nullptr;
        size = capacity = 0;
    }
};
#ifdef _DEBUG
std::ostream &operator<<(std::ostream &out, const DynamicArray &x) {
    for (int i = 0; i < x.getSize(); i++) out << x.at(i) << ' ';
    out << '\n';
    return out;
}
#endif
