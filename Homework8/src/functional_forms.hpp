/**
 * Copyright (c) 2019, Hongtu Xu
 * All rights reserved.
 *
 * @date 2019-12-19
 * @author Hongtu Xu
 */
#ifndef FUNCTIONAL_FORMS_HPP_
#define FUNCTIONAL_FORMS_HPP_

#include <cstdlib>
#include <cmath>
#include <utility>

/* For all lambda functions below, if you are not clear how they work, please
 * refer to the given example for details. */

/*
 * Return a lambda function that takes one parameter (m) and returns a
 * pair<double, double> that: has (f1+f2)(m) as first, and (d(f1+f2)/dx)(m) as
 * second.
 */
auto derSum = [](auto f1, auto f2) {
  return [=](auto m) -> std::pair<double, double> {
    auto p1 = f1(m), p2 = f2(m);
    return {p1.first + p2.first, p1.second + p2.second};
  };
};

/*
 * Return a lambda function that takes one parameter (m) and returns a
 * pair<double, double> that: has (f1-f2)(m) as first, and (d(f1-f2)/dx)(m) as
 * second.
 */
auto derSub = [](auto f1, auto f2) {
  return [=](auto m) -> std::pair<double, double> {
    auto p1 = f1(m), p2 = f2(m);
    return {p1.first - p2.first, p1.second - p2.second};
  };
};

/*
 * Return a lambda function that takes one parameter (m) and returns a
 * pair<double, double> that: has (f1*f2)(m) as first, and (d(f1*f2)/dx)(m) as
 * second.
 */
auto derMul = [](auto f1, auto f2) {
  return [=](auto m) -> std::pair<double, double> {
    auto p1 = f1(m), p2 = f2(m);
    return {p1.first * p2.first, p1.second * p2.first + p1.first * p2.second};
  };
};

/*
 * Return a lambda function that takes one parameter (m) and returns a
 * pair<double, double> that: has (f1/f2)(m) as first, and (d(f1/f2)/dx)(m) as
 * second.
 */
auto derDiv = [](auto f1, auto f2) {
  return [=](auto m) -> std::pair<double, double> {
    auto p1 = f1(m), p2 = f2(m);
    return {p1.first / p2.first, (p1.second * p2.first - p2.second * p1.first) /
                                     (p2.first * p2.first)};
  };
};

/*
 * Return a lambda function that takes one parameter (m) and returns a
 * pair<double, double> that: has (f1(f2))(m) as first, and (d(f1(f2))/dx)(m) as
 * second.
 */
auto derComp = [](auto f1, auto f2) {
  return [=](auto m) -> std::pair<double, double> {
    auto t = f2(m);
    auto p = f1(t.first);
    return {p.first, p.second * t.second};
  };
};

/*
 * Return a lambda function that takes one parameter (m) and returns a
 * pair<double, double> that: has [(f1)(m)]^exp as first, and (d(f1^exp)/dx)(m)
 * as second.
 */
auto derPow = [](auto f, int exp) {
  return [=](auto m) -> std::pair<double, double> {
    auto p = f(m);
    return {pow(p.first, exp), exp * pow(p.first, exp - 1) * p.second};
  };
};

#endif