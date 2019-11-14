/**
 * Copyright (c) 2019, xehoth
 * All rights reserved.
 *
 * @author xehoth
 * @date 2019-10-26
 */
#include <iostream>
#include <string>
#include <cmath>
#include <map>

inline bool checkRange(double x, double start, double end) {
    if (x < start || x > end) {
        // todo error handling
        return false;
    }
    return true;
}

double linearF(std::map<double, double> &data, double x) {
    auto p = data.lower_bound(x);
    std::map<double, double>::iterator xk, xk1;
    if (p == data.begin()) {
        xk = p;
        xk1 = std::next(p);
    } else if (p == data.end()) {
        xk1 = std::prev(p);
        xk = std::prev(xk1);
    } else {
        xk = std::prev(p);
        xk1 = p;
    }
    return ((x - xk->first) * xk1->second + (xk1->first - x) * xk->second) /
           (xk1->first - xk->first);
}

class LookupTable {
   public:
    // constructor, start: start position; end: end position; increment: the increment "dx"
    // You should calculate the value in range [start, end], with increment "increment"
    LookupTable(double start, double end, double increment)
        : start(start), end(end), increment(increment) {}
    // virtual destructor
    virtual ~LookupTable() = 0;
    // get the value f(x) of the given x
    virtual double getValue(double x) = 0;

   protected:
    double start, end, increment;
    std::map<double, double> table;
};

LookupTable::~LookupTable() {}

class SquareLookupTable : public LookupTable {
   public:
    SquareLookupTable(double start, double end, double increment)
        : LookupTable(start, end, increment) {
        for (double i = start; i <= end; i += increment) table[i] = i * i;
    }

    double getValue(double x) override {
        if (!checkRange(x, start, end)) return 0;

        auto p = table.find(x);
        if (p != table.end()) return p->second;
        return linearF(table, x);
    }
};

class SinLookupTable : public LookupTable {
   public:
    SinLookupTable(double start, double end, double increment)
        : LookupTable(start, end, increment) {
        for (double i = start; i <= end; i += increment) table[i] = sin(i);
    }

    double getValue(double x) override {
        if (!checkRange(x, start, end)) return 0;

        auto p = table.find(x);
        if (p != table.end()) return p->second;
        return linearF(table, x);
    }
};

class LogLookupTable : public LookupTable {
   public:
    LogLookupTable(double start, double end, double increment)
        : LookupTable(start, end, increment) {
        for (double i = start; i <= end; i += increment) table[i] = log(i);
    }

    double getValue(double x) override {
        if (!checkRange(x, start, end)) return 0;

        auto p = table.find(x);
        if (p != table.end()) return p->second;
        return linearF(table, x);
    }
};

//////////////////////////////////////////////////////////////////////
///////////////// DO NOT SUBMIT THE FOLLOWING LINES //////////////////
//////////////////////////////////////////////////////////////////////
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    double start, end, inc;
    std::cin >> start >> end >> inc;
    LookupTable *p = new LogLookupTable(start, end, inc);

    int n;
    std::cin >> n;
    for (double x; n--;) {
        std::cin >> x;
        std::cout << std::fixed << p->getValue(x) << '\n';
    }
    delete p;
    return 0;
}
