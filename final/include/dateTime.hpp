#ifndef DATE_TIME_HPP
#define DATE_TIME_HPP

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <time.h>

// Class to represent a 24-hour date and time
class DateTime {
  private:
	// using ctime internally to hold the date and time
	time_t dateAndTime;

  public:
	// constructor
	DateTime(unsigned int month = 0,
			 unsigned int day = 0,
			 unsigned int year = 0,
			 unsigned int hour = 0,
			 unsigned int minute = 0);

	// getters
	unsigned int getMonth() const;
	unsigned int getDay() const;
	unsigned int getYear() const;
	unsigned int getHour() const;
	unsigned int getMin() const;

	// get the first day of the week
	DateTime getFirstDayOfWeek() const;

	// string outputs
	std::string getDayOfWeek() const;
	std::string getTime() const;

	// check if the date is within 7 days of the current date
	bool sameWeek(const DateTime& d) const;

	// operator overloads
	DateTime operator+(const DateTime& d) const;
	DateTime operator-(const DateTime& d) const;
	bool operator<(const DateTime& d) const;
	bool operator>(const DateTime& d) const;
	bool operator==(const DateTime& d) const;
	bool operator<=(const DateTime& d) const;
	bool operator>=(const DateTime& d) const;

	// friend functions
	friend std::ostream& operator<<(std::ostream& os, const DateTime& d);
	friend std::istream& operator>>(std::istream& is, const DateTime& d);
};

#endif	// DATE_TIME_HPP
