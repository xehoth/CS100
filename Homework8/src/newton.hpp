/**
 * Copyright (c) 2019, Hongtu Xu
 * All rights reserved.
 *
 * @date 2019-12-19
 * @author Hongtu Xu
 */
#ifndef NEWTON_HPP_
#define NEWTON_HPP_

#include <cstdlib>
#include <algorithm>
#include <cmath>
/*
 * This function finds the nearest root of a function by Newton's method.
 * f is a lambda function that's returned by any function in problem 2.
 * Starting from "startingPoint", you are to find a nearest root x_0, where
 * |x_0| < eps (0.000001 by default).
 */
template <typename T>
double findNearestRoot(T f, double startingPoint, double eps = 0.000001) {
  for (double nx = startingPoint + 1; std::abs(startingPoint - nx) > eps;) {
    auto p = f(startingPoint);
    nx = startingPoint - p.first / p.second;
    std::swap(nx, startingPoint);
  }
  return startingPoint;
}

#endif