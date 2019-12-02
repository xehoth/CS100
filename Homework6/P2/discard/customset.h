/**
 * Copyright (c) 2019, HongtuXu
 * All rights reserved.
 *
 * @author HongtuXu
 * @date 2019-11-17
 */
#ifndef _CUSTOMSET_H_
#define _CUSTOMSET_H_
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <utility>

template <typename T>
class CustomSet {
   public:
    CustomSet() = default;

    CustomSet(const CustomSet &other) : data(other.data), d(other.d) {}

    CustomSet(T arr[], int size) {
        for (int i = 0; i < size; i++) add(arr[i]);
    }

    ~CustomSet() {}

    const int size() const { return data.size(); }

    const bool add(const T &item) {
        if (d.find(item) != d.end()) return false;
        d.insert(item);
        data.push_back(item);
        return true;
    }

    const T *find(const T &item) const {
        auto p = d.find(item);
        if (p == d.end()) return nullptr;
        return &(*p);
    }

    const bool erase(const T &item) {
        if (d.find(item) == d.end()) return false;
        d.erase(item);
        data.erase(std::find(data.begin(), data.end(), item));
        return true;
    }

    CustomSet intersection(const CustomSet &other) const {
        std::set<T> tmp;
        std::set_intersection(d.begin(), d.end(), other.d.begin(), other.d.end(),
                              std::inserter(tmp, tmp.begin()));
        if (tmp.empty()) return CustomSet();
        std::vector<T> arr;
        arr.reserve(tmp.size());
        for (const auto &i : d)
            if (tmp.find(i) != tmp.end()) arr.push_back(i);
        return CustomSet(arr.data(), arr.size());
    }

    void sortSet() { std::sort(data.begin(), data.end()); }

    void printSet() const {
        std::cout << "{";
        for (int i = 0; i < (int)d.size(); ++i) {
            std::cout << data[i];
            if (i != (int)d.size() - 1) std::cout << ", ";
        }
        std::cout << "}\n";
    }

    CustomSet operator+(const T &item) const {
        CustomSet ret(*this);
        ret.add(item);
        return ret;
    }

    CustomSet operator+(const CustomSet &that) const {
        CustomSet ret(*this);
        for (const auto &i : that.data) ret.add(i);
        return ret;
    }

    CustomSet &operator+=(const T &item) {
        add(item);
        return *this;
    }

    CustomSet &operator+=(const CustomSet &that) {
        if (this == &that) return *this;
        for (const auto &i : that.data) add(i);
        return *this;
    }

    CustomSet operator-(const T &item) const {
        CustomSet ret(*this);
        ret.erase(item);
        return ret;
    }

    CustomSet operator-(const CustomSet &that) const {
        if (this == &that) return CustomSet();
        std::set<T> tmp;
        std::set_difference(d.begin(), d.end(), that.d.begin(), that.d.end(),
                            std::inserter(tmp, tmp.begin()));
        std::vector<T> arr;
        arr.reserve(tmp.size());
        for (const auto &i : data)
            if (tmp.find(i) != tmp.end()) arr.push_back(i);
        return CustomSet(arr.data(), arr.size());
    }

    CustomSet &operator-=(const T &item) {
        erase(item);
        return *this;
    }

    CustomSet &operator-=(const CustomSet &that) {
        if (this == &that) {
            d.clear();
            data.clear();
            return *this;
        }
        std::set<T> tmp;
        std::set_difference(d.begin(), d.end(), that.d.begin(), that.d.end(),
                            std::inserter(tmp, tmp.begin()));
        std::vector<T> arr;
        arr.reserve(tmp.size());
        for (const auto &i : data)
            if (tmp.find(i) != tmp.end()) arr.push_back(i);
        data = arr;
        d = tmp;
        return *this;
    }

    CustomSet<std::pair<T, T> > operator*(const CustomSet &that) const {
        CustomSet<std::pair<T, T> > ret;
        for (const auto &a : data)
            for (const auto &b : that.data) ret.add({a, b});
        return ret;
    }

    CustomSet operator&(const CustomSet &other) const {
        CustomSet ret = intersection(other);
        return ret;
    }

    CustomSet &operator&=(const CustomSet &other) {
        *this = (*this) & other;
        return *this;
    }

    const std::vector<T> &getData() const { return data; }
    std::vector<T> &getData() { return data; }

   private:
    std::vector<T> data;
    std::set<T> d;
};
#endif
