#include "Name.hpp"
#include "string.h"

Name::Name( char * name, int nameSize ) {
  memcpy(m_name,name,nameSize);
}