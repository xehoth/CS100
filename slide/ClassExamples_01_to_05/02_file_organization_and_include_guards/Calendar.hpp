#ifndef CALENDAR_HPP_
#define CALENDAR_HPP_

#include "Birthday.hpp"
#include "Meeting.hpp"
#include <vector>

class Calendar {
public:
  Calendar();

private:
  std::vector<Meeting> m_meetings;
  std::vector<Birthday> m_birthdays;
};

#endif