#ifndef LOCATION_HPP_
#define LOCATION_HPP_

#include <stdlib.h>

class Location{
  public:
    Location( float longitude, float latitude );

  private:
    float m_longitude;
    float m_latitude;
};

#endif