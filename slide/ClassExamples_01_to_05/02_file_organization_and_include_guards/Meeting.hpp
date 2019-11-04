#ifndef MEETING_HPP_
#define MEETING_HPP_

#include "Location.hpp"
#include "Date.hpp"

class Meeting {
public:
  Meeting( Location location, Date date );

private:
  Location m_location;
  Date m_date;
};

#endif