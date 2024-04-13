#ifndef DATE_TIME_HPP
#define DATE_TIME_HPP

#include <iostream>

class DateTime {
  private:
	unsigned int month, day, year, hour, minute;

  public:
	DateTime(unsigned int month,
			 unsigned int day,
			 unsigned int year,
			 unsigned int hour,
			 unsigned int minute);

	/** Getters */
	unsigned int getMonth() const;
	unsigned int getDay() const;
	unsigned int getYear() const;
	unsigned int getHour() const;
	unsigned int getMin() const;

	/** Checks if the given event is within 7 days of this event */
	bool withinSevenDays(const DateTime& d) const;

	/** Operators */
	DateTime operator+(const DateTime& d) const;
	DateTime operator-(const DateTime& d) const;
	DateTime operator<(const DateTime& d) const;
	DateTime operator>(const DateTime& d) const;
	DateTime operator==(const DateTime& d) const;
	friend std::ostream& operator<<(std::ostream& os, const DateTime& d);
	friend std::istream& operator>>(std::istream& is, const DateTime& d);
};

#endif	// DATE_TIME_HPP
