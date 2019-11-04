#ifndef BIRTHDAY_HPP_
#define BIRTHDAY_HPP_

#include "Name.hpp"
#include "Date.hpp"

class Birthday {
public:
  Birthday( Name name, Date date );

private:
  Name m_name;
  Date m_date;
};

#endif