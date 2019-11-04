#ifndef NAME_HPP_
#define NAME_HPP_

#include <stdlib.h>

class Name{
  public:
    Name( char * name, int nameSize );

  private:
    char m_name[100];
};

#endif