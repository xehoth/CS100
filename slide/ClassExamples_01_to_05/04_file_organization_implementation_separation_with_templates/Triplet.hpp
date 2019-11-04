#ifndef TRIPLET_HPP_
#define TRIPLET_HPP_

#include <stdio.h>

template<class T1, class T2, class T3>
class Triplet {
public:
  Triplet();

  T1 & GetFirst();
  T2 & GetSecond();
  T3 & GetThird();

  void SetFirst( T1 & var );
  void SetSecond( T2 & var );
  void SetThird( T3 & var );

  void Print();

private:
  T1 m_first;
  T2 m_second;
  T3 m_third;
};

#include "Triplet_impl.hpp"

#endif