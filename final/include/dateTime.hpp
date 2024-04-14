#ifndef DATE_TIME_HPP
#define DATE_TIME_HPP

#include <iostream>

// Class to represent a 24-hour date and time
class DateTime {
  private:
	// date and time components are 0-indexed
	// january is 0, 1st is 0, 12:00 AM is 0
	unsigned int month, day, year, hour, minute;

  public:
	// constructor
	DateTime(unsigned int month = 1,
			 unsigned int day = 1,
			 unsigned int year = 2024,
			 unsigned int hour = 0,
			 unsigned int minute = 0);

	// getters
	unsigned int getMonth() const;
	unsigned int getDay() const;
	unsigned int getYear() const;
	unsigned int getHour() const;
	unsigned int getMin() const;

	// check if the date is within 7 days of the current date
	bool withinSevenDays(const DateTime& d) const;

	// operator overloads
	DateTime operator+(const DateTime& d) const;
	DateTime operator-(const DateTime& d) const;
	DateTime operator<(const DateTime& d) const;
	DateTime operator>(const DateTime& d) const;
	DateTime operator==(const DateTime& d) const;

	// friend functions
	friend std::ostream& operator<<(std::ostream& os, const DateTime& d);
	friend std::istream& operator>>(std::istream& is, const DateTime& d);
};

#endif	// DATE_TIME_HPP
