#ifndef DATE_HPP_
#define DATE_HPP_

#include <stdlib.h>

class Date{
  public:
    Date( int year, int month, int day );

  private:
    int m_year;
    int m_month;
    int m_day;
};

#endif