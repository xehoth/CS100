/**
 * Copyright (c) 2019, HongtuXu
 * All rights reserved.
 *
 * @author HongtuXu
 * @date 2019-10-26
 */
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>

const double EPS = 1e-9;

inline int sign(const double x) { return (x > EPS) - (x < -EPS); }

double linearF(std::vector<std::pair<double, double> > &data, double x) {
    auto p = std::lower_bound(
        data.begin(), data.end(), x,
        [&](const std::pair<double, double> &a, const double b) { return sign(a.first - b) < 0; });
    std::vector<std::pair<double, double> >::iterator xk, xk1;
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

double get(std::vector<std::pair<double, double> > &data, double x) {
    auto p = std::lower_bound(
        data.begin(), data.end(), x,
        [&](const std::pair<double, double> &a, const double b) { return sign(a.first - b) < 0; });
    if (p != data.end() && sign(p->first - x) == 0) return p->second;
    return linearF(data, x);
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
    std::vector<std::pair<double, double> > table;
};

LookupTable::~LookupTable() {}

class SquareLookupTable : public LookupTable {
   public:
    SquareLookupTable(double start, double end, double increment)
        : LookupTable(start, end, increment) {
        for (double i = start; sign(i - end) <= 0; i += increment) table.emplace_back(i, i * i);
    }

    double getValue(double x) override { return get(table, x); }
};

class SinLookupTable : public LookupTable {
   public:
    SinLookupTable(double start, double end, double increment)
        : LookupTable(start, end, increment) {
        for (double i = start; sign(i - end) <= 0; i += increment) table.emplace_back(i, sin(i));
    }

    double getValue(double x) override { return get(table, x); }
};

class LogLookupTable : public LookupTable {
   public:
    LogLookupTable(double start, double end, double increment)
        : LookupTable(start, end, increment) {
        for (double i = start; sign(i - end) <= 0; i += increment) table.emplace_back(i, log(i));
    }

    double getValue(double x) override { return get(table, x); }
};

//////////////////////////////////////////////////////////////////////
///////////////// DO NOT SUBMIT THE FOLLOWING LINES //////////////////
//////////////////////////////////////////////////////////////////////
#include <iomanip>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    double start, end, inc;
    std::cin >> start >> end >> inc;
    LookupTable *p = new SquareLookupTable(start, end, inc);

    int n;
    std::cin >> n;
    for (double x; n--;) {
        std::cin >> x;
        std::cout << std::fixed << std::setprecision(8) << p->getValue(x) << '\n';
    }
    delete p;
    return 0;
}
