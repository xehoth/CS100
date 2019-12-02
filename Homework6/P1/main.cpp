#include "customset.h"

int main() {
    double a[5] = {4.5, 6.2, 32, -4.0, 0};
    CustomSet<double> sample1(a, 5);
    double b[5] = {4.5, 2.2, 10, -2, 0};
    CustomSet<double> sample2(b, 5);
    sample1 &= sample2;
    // sample1.sortSet();
    sample1.printSet();  // prints "{-4, 6, 32}\n"
}