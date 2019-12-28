#include "Poly.hpp"

#include <iostream>
#include <math.h>

typedef double TYPE;

void doTest( const Poly<TYPE> & poly, TYPE param, TYPE expectation ) {
  TYPE result = poly.eval(param)-expectation;
  if( fabs(result) > 0.000001 )
    std::cout << "Error!\n";
  else
    std::cout << "Success!\n";
}

int main() {
  
  //testing interface of the polynomial class
                                                                                                                                                                                                                                                                            
  //constructors
  Poly<TYPE> p1;                                      doTest(p1,10,0);
  Poly<TYPE> p2(2);                                   doTest(p2,10,2);
  std::vector<TYPE> cs{ 0, 1, 0, -2};
  Poly<TYPE> p3(cs);                                  doTest(p3,2,-14);
  TYPE arr[] = {1,0,2};
  Poly<TYPE> p4(arr,3);                               doTest(p4,3,19);
  
  //copy/move constructor
  Poly<TYPE> p5(p3);                                  doTest(p5,2,-14);
  
  //assignments
  Poly<TYPE> p6 = p5;                                 doTest(p6,2,-14);

  //operations
  Poly<TYPE> p7 = p3 + p4;                            doTest(p7,2,-5);
  Poly<TYPE> p8 = p7 - p3;                            doTest(p8,3,19);
  p8 *= p7;
  TYPE res1 = p8.eval(-4);
  TYPE res2 = p4.eval(-4) * p7.eval(-4);
  if( fabs(res1-res2) < 0.000001 )
    std::cout << "Success!\n";
  else
    std::cout << "Error!\n";

  //evaluators
  doTest(p4.der(),2,8);
  std::pair<TYPE,TYPE> res = p4(2);
  if(fabs(res.first-9)<0.000001)
    std::cout << "Success!\n";
  else
    std::cout << "Error!\n";
  if(fabs(res.second-8)<0.000001)
    std::cout << "Success!\n";
  else
    std::cout << "Error!\n";
}