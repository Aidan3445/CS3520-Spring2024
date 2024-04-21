#ifndef DATE_TIME_HPP
#define DATE_TIME_HPP

#include "utility.hpp"
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
	DateTime(int month = 0, int day = 0, int year = 0, int hour = 0, int minute = 0);

	// destructor
	~DateTime() = default;

	// copy constructor
	DateTime(const DateTime& d);

	// assignment operator
	DateTime& operator=(const DateTime& d);

	// getters
	int getMonth() const;
	int getDay() const;
	int getYear() const;
	int getHour() const;
	int getMin() const;

	// get the first day of the week
	DateTime getFirstDayOfWeek() const;

	// string outputs
	// get the date in the format "MM/DD/YYYY"
	std::string getDate() const;
	// get the day of the week
	std::string getDayOfWeek() const;
	// get the time in the format "HH:MM"
	std::string getTime() const;

	// check if the date is within 7 days of the current date
	bool sameWeek(const DateTime& d) const;

	// add and subtract time
	DateTime add(const int& month = 0,
				 const int& day = 0,
				 const int& year = 0,
				 const int& hour = 0,
				 const int& minute = 0) const;
	DateTime sub(const int& month = 0,
				 const int& day = 0,
				 const int& year = 0,
				 const int& hour = 0,
				 const int& minute = 0) const;

	// operator overloads
	bool operator<(const DateTime& d) const;
	bool operator>(const DateTime& d) const;
	bool operator==(const DateTime& d) const;
	bool operator<=(const DateTime& d) const;
	bool operator>=(const DateTime& d) const;

	// friend functions
	friend std::ostream& operator<<(std::ostream& os, const DateTime& d);
	friend std::istream& operator>>(std::istream& is, const DateTime& d);

	static std::pair<DateTime, DateTime> readEventTimes();
	static DateTime readStartTime();
};

#endif	// DATE_TIME_HPP
