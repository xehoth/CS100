#include <stdlib.h>
#include "Name.hpp"
#include "Date.hpp"

int main() {
  Date myDate(1,1,2019);
  char * name = "Laurent\n";
  Name myName(name,8);
  return 0;
}