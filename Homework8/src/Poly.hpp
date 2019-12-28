/**
 * Copyright (c) 2019, Hongtu Xu
 * All rights reserved.
 *
 * @date 2019-12-19
 * @author Hongtu Xu
 */
#ifndef POLY_HPP_
#define POLY_HPP_

#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

#ifdef _DEBUG
template <typename T>
void debug(T s) {
  std::cerr << s << std::endl;
  exit(-1);
}

void checkRange(int i, int n) {
  if (i > n)
    debug("out of range at " + std::to_string(i) +
          " size: " + std::to_string(n));
}
#endif

#ifdef USE_FFT
namespace fft {
  const double PI = acos(-1);
  const int MAXN = 50000;

  const int MAX_M = 1 << 17 | 1;
  using FFT_D = double;

  struct Complex {
    FFT_D r, i;

    Complex operator+(const Complex &p) const { return {r + p.r, i + p.i}; }

    Complex operator-(const Complex &p) const { return {r - p.r, i - p.i}; }

    Complex operator*(const Complex &p) const {
      return {r * p.r - i * p.i, r * p.i + i * p.r};
    }

    void operator*=(const Complex &x) {
      double t = r;
      r = r * x.r - i * x.i;
      i = t * x.i + i * x.r;
    }

    Complex conj() const { return {r, -i}; }

    Complex inv() const {
      FFT_D x = r * r + i * i;
      return {r / x, -i / x};
    }

    void operator+=(const Complex &p) {
      r += p.r;
      i += p.i;
    }
  };

  std::vector<Complex> rt, irt;

  void init(int n) {
    rt[0] = {1, 0};
    rt[1] = {cos(2 * PI / n / 2), sin(2 * PI / n / 2)};
    for (int i = 2; i < n; ++i) rt[i] = rt[i - 1] * rt[1];
    irt[0] = {1, 0};
    irt[1] = rt[1].inv();
    for (int i = 2; i < n; ++i) irt[i] = irt[i - 1] * irt[1];
    for (int i = 0, j = 0; i < n; ++i) {
      if (i > j) {
        std::swap(rt[i], rt[j]);
        std::swap(irt[i], irt[j]);
      }
      for (int k = n >> 1; (j ^= k) < k; k >>= 1)
        ;
    }
  }

  void dit(Complex *a, int n) {
    for (int i = 1, l = n >> 1; i < n; i <<= 1, l >>= 1) {
      for (int j = 0, o = 0; j < i; j++, o += l << 1) {
        const Complex &w = rt[i + j];
        for (int k = o; k < o + l; k++) {
          Complex t = a[k + l] * w;
          a[k + l] = a[k] - t;
          a[k] += t;
        }
      }
    }
  }

  void dif(Complex *a, int n) {
    for (int i = n >> 1, l = 1; i; i >>= 1, l <<= 1) {
      for (int j = 0, o = 0; j < i; j++, o += l << 1) {
        const Complex &w = irt[i + j];
        for (int k = o; k < o + l; k++) {
          Complex t = a[k + l];
          a[k + l] = (a[k] - t) * w;
          a[k] += t;
        }
      }
    }
    for (int i = 0; i < n; i++) a[i].r /= n;
  }

  template <typename T>
  void trans(std::vector<T> &ret, const std::vector<Complex> &t) {
    for (int i = 0; i < static_cast<int>(ret.size()); ++i) ret[i] = t[i].r;
  }

  template <>
  void trans(std::vector<int> &ret, const std::vector<Complex> &t) {
    for (int i = 0; i < static_cast<int>(ret.size()); ++i)
      ret[i] = static_cast<int>(t[i].r + 0.2);
  }

  template <typename T>
  std::vector<T> convolve(const std::vector<T> &a, const std::vector<T> &b) {
    int k = 2;
    for (; k <= static_cast<int>(a.size() + b.size()) - 2;) k <<= 1;
    if (static_cast<int>(rt.size()) < k) {
      rt.resize(k);
      irt.resize(k);
      init(k);
    }
    std::vector<Complex> ta(k), tb(k);
    std::vector<T> ret(a.size() + b.size() - 1);
    for (int i = 0; i < static_cast<int>(a.size()); ++i) ta[i].r = a[i];
    for (int i = 0; i < static_cast<int>(b.size()); ++i) tb[i].r = b[i];
    dit(ta.data(), k);
    dit(tb.data(), k);
    for (int i = 0; i < k; ++i) ta[i] *= tb[i];
    dif(ta.data(), k);
    trans(ret, ta);
    return ret;
  }
}  // namespace fft
#endif

template <typename T>
class Poly {
 public:
  /* Default constructor */
  Poly() : _coeffs(1) {}

  /* Constructor for a poly that's a constant number */
  Poly(T constant) : _coeffs(1, constant) {}

  /* Given a vector of coefficients */
  Poly(const std::vector<T> &coeffs) : _coeffs(coeffs) {}

  /* Given an rvalue reference of a vector of coefficients */
  Poly(std::vector<T> &&coeffs) : _coeffs(std::move(coeffs)) {}

  /* Given an array of coefficients with size of the array*/
  Poly(T *coeffs, size_t numberCoeffs)
      : _coeffs(coeffs, coeffs + numberCoeffs) {}

  /* Given an initializer_list */
  Poly(std::initializer_list<T> coeffs) : _coeffs(coeffs) {}

  virtual ~Poly() {}

  /* Copying constructor */
  Poly(const Poly<T> &poly) : _coeffs(poly._coeffs) {}

  /* Copying constructor with rvalue reference */
  Poly(Poly<T> &&poly) : _coeffs(std::move(poly._coeffs)) {}

  /* Assignment operator */
  Poly<T> &operator=(const Poly<T> &poly) {
    if (this == &poly) return *this;
    _coeffs = poly._coeffs;
    return *this;
  }

  /* Assignment operator with rvalue reference */
  Poly<T> &operator=(Poly<T> &&poly) {
    if (this == &poly) return *this;
    _coeffs = std::move(poly._coeffs);
    return *this;
  }

  int deg() const { return _coeffs.size() - 1; }

  int size() const { return _coeffs.size(); }

  void reDeg(int deg) { _coeffs.resize(deg + 1); }

  void fixDeg() {
    int i = _coeffs.size() - 1;
    for (; i; i--)
      if (_coeffs[i]) break;
    reDeg(i);
  }

  const std::vector<T> &data() const { return _coeffs; }
  std::vector<T> &data() { return _coeffs; }

  const T &operator[](int i) const {
#ifdef _DEBUG
    checkRange(i, _coeffs.size());
#endif
    return _coeffs[i];
  }

  T &operator[](int i) {
#ifdef _DEBUG
    checkRange(i, _coeffs.size());
#endif
    return _coeffs[i];
  }

  Poly operator-() const {
    Poly ret(*this);
    for (int i = 0; i < ret.size(); ++i) ret[i] = -ret[i];
    return ret;
  }

  /*
   * Below are operations of polynomials.
   * They are quite self-explanatory.
   */

  Poly<T> operator+(const Poly<T> &rhs) const {
    Poly ret(*this);
    ret += rhs;
    return ret;
  }

  Poly<T> operator-(const Poly<T> &rhs) const {
    Poly ret(*this);
    ret -= rhs;
    return ret;
  }

  Poly<T> operator*(const Poly<T> &rhs) const {
#ifndef USE_FFT
    Poly ret;
    ret.reDeg(deg() + rhs.deg());
    for (int i = 0; i < size(); ++i)
      for (int j = 0; j < rhs.size(); ++j) ret[i + j] += _coeffs[i] * rhs[j];
#else
    Poly ret(fft::convolve(_coeffs, rhs.data()));
#endif

#ifndef NO_AUTO_FIX_DEG
    ret.fixDeg();
#endif
    return ret;
  }

  Poly<T> &operator+=(const Poly<T> &rhs) {
    if (deg() < rhs.deg()) reDeg(rhs.deg());
    for (int i = 0; i < rhs.size(); ++i) _coeffs[i] += rhs[i];
#ifndef NO_AUTO_FIX_DEG
    fixDeg();
#endif
    return *this;
  }

  Poly<T> &operator-=(const Poly<T> &rhs) {
    if (deg() < rhs.deg()) reDeg(rhs.deg());
    for (int i = 0; i < rhs.size(); ++i) _coeffs[i] -= rhs[i];
#ifndef NO_AUTO_FIX_DEG
    fixDeg();
#endif
    return *this;
  }

  Poly<T> &operator*=(const Poly<T> &rhs) {
    *this = *this * rhs;
    return *this;
  }

  /*
   * This function evaluates the polynomial at "param",
   * and returns the value of evaluation.
   * For example, evaluating x+3 at param=7 gives 10.
   */
  T eval(T param) const {
    T x = 1, ret = 0;
    for (auto i : _coeffs) {
      ret += x * i;
      x *= param;
    }
    return ret;
  }

  /*
   * This function takes the derivative of the polynomial,
   * and returns a new polynomial of its derivative.
   * For example, calling this function for x^2
   * will return a polynomial 2x.
   */
  Poly<T> der() const {
    Poly ret;
    if (deg() <= 0) return ret;
    ret.reDeg(deg() - 1);
    for (int i = 0; i < deg(); ++i) ret[i] = _coeffs[i + 1] * (i + 1);
    return ret;
  }

  /*
   * This function returns a pair of:
   * 1. the value (evaluation) of the polynomial at "param".
   * 2. the value of the first-order derivative of the polynomial at "param".
   * For example, calling this operator for x^2-2x at "param"=4
   * will return (8, 6).
   */
  std::pair<T, T> operator()(T param) const {
    return {eval(param), der().eval(param)};
  }

 private:
  std::vector<T> _coeffs;
};

#endif