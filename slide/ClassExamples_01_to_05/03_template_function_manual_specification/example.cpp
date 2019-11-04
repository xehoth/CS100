#include <stdio.h>
#include <iostream>

template<class T>
T max( T e1, T e2 ) {
  if( e1 > e2 ) return e1;
  return e2;
}

int main() {
  int e1 = 0;
  int e2 = 1;
  float e3 = 2;

  //template types are implicitly given by input parameter types (not ambiguous)
  max(e1,e2);
  //template types need to be given explicitly if ambiguous
  max<float>(e1,e3);
  
}