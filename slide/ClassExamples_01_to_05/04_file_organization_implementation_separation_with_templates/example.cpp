//This example shows how to cleanly add a template class
//for which the definition and implementation are still split
//into two files (Definition in Triplet.hpp, implementation in Triplet_impl.hpp)
//There is no absolute need to do this separation, it is merely a style question.
//It is nice to separate the implementation from the interface, and the present
//example shows how to do it with template classes.

#include <stdio.h>
#include <Triplet.hpp>

int main() {
  int var1 = 0;
  float var2 = 1;
  double var3 = 2;

  Triplet<int,float,double> triplet;
  triplet.SetFirst(var1);
  triplet.SetSecond(var2);
  triplet.SetThird(var3);

  triplet.Print();
  std::cout << triplet.GetFirst() << "\n";
  std::cout << triplet.GetSecond() << "\n";
  std::cout << triplet.GetThird() << "\n";
}