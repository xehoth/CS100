#include <iostream>

template< class T1, class T2, class T3 >
Triplet<T1,T2,T3>::Triplet() {}

template< class T1, class T2, class T3 >
T1 &
Triplet<T1,T2,T3>::GetFirst() {
  return m_first;
}

template< class T1, class T2, class T3 >
T2 &
Triplet<T1,T2,T3>::GetSecond() {
  return m_second;
}

template< class T1, class T2, class T3 >
T3 &
Triplet<T1,T2,T3>::GetThird() {
  return m_third;
}

template< class T1, class T2, class T3 >
void
Triplet<T1,T2,T3>::SetFirst( T1 & var ) {
  m_first = var;
}

template< class T1, class T2, class T3 >
void
Triplet<T1,T2,T3>::SetSecond( T2 & var ) {
  m_second = var;
}

template< class T1, class T2, class T3 >
void
Triplet<T1,T2,T3>::SetThird( T3 & var ) {
  m_third = var;
}

template< class T1, class T2, class T3 >
void
Triplet<T1,T2,T3>::Print() {
  std::cout << "element 1: " << m_first << "\n";
  std::cout << "element 2: " << m_second << "\n";
  std::cout << "element 3: " << m_third << "\n";
}