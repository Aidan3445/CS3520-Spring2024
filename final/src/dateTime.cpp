#include "../include/dateTime.hpp"

#define JANDAYS 31
#define FEBDAYS 28
#define LEAPFEBDAYS 29
#define MARDAYS 31
#define APRDAYS 30
#define MAYDAYS 31
#define JUNDAYS 30
#define JULDAYS 31
#define AUGDAYS 31
#define SEPDAYS 30
#define OCTDAYS 31
#define NOVDAYS 30
#define DECDAYS 31

// Helper function to check if the given date and time is valid
bool validDateTime(unsigned int month,
				   unsigned int day,
				   unsigned int year,
				   unsigned int hour,
				   unsigned int minute) {
	// ensure valid month and day
	if (month == 0 && day > JANDAYS) {
		return false;
	} else if (month == 1 && day > LEAPFEBDAYS && year % 4 == 0) {
		return false;
	} else if (month == 1 && day > FEBDAYS) {
		return false;
	} else if (month == 2 && day > MARDAYS) {
		return false;
	} else if (month == 3 && day > APRDAYS) {
		return false;
	} else if (month == 4 && day > MAYDAYS) {
		return false;
	} else if (month == 5 && day > JUNDAYS) {
		return false;
	} else if (month == 6 && day > JULDAYS) {
		return false;
	} else if (month == 7 && day > AUGDAYS) {
		return false;
	} else if (month == 8 && day > SEPDAYS) {
		return false;
	} else if (month == 9 && day > OCTDAYS) {
		return false;
	} else if (month == 10 && day > NOVDAYS) {
		return false;
	} else if (month == 11 && day > DECDAYS) {
		return false;
	} else if (month > 11) {
		return false;
	}

	// ensure valid hour and minute
	if (hour > 23) {
		return false;
	} else if (minute > 59) {
		return false;
	}
	return true;
}

// Constructor
DateTime::DateTime(unsigned int month,
				   unsigned int day,
				   unsigned int year,
				   unsigned int hour,
				   unsigned int minute) {
	// ensure valid date and time
	while (!validDateTime(month, day, year, hour, minute)) {
		std::cout << "Invalid date and time. Please enter a valid date and time." << std::endl;
		std::cout << "Month: ";
		std::cin >> month;
		std::cout << "Day: ";
		std::cin >> day;
		std::cout << "Year: ";
		std::cin >> year;
		std::cout << "Hour: ";
		std::cin >> hour;
		std::cout << "Minute: ";
		std::cin >> minute;
	}

	this->month = month;
	this->day = day;
	this->year = year;
	this->hour = hour;
	this->minute = minute;
}

// Getters
unsigned int DateTime::getMonth() const { return month; }

unsigned int DateTime::getDay() const { return day; }

unsigned int DateTime::getYear() const { return year; }

unsigned int DateTime::getHour() const { return hour; }

unsigned int DateTime::getMin() const { return minute; }

// Check if the date is within 7 days of the current date
bool DateTime::withinSevenDays(const DateTime& d) const {
	DateTime diff = *this - d;

	return diff.day <= 7;
}

// Operator overloads
DateTime DateTime::operator+(const DateTime& d) const {
	unsigned int newMonth = month + d.month;
	unsigned int newDay = day + d.day;
	unsigned int newYear = year + d.year;
	unsigned int newHour = hour + d.hour;
	unsigned int newMinute = minute + d.minute;

	// adjust date and time if necessary
	if (newMinute >= 60) {
		newHour++;
		newMinute -= 60;
	}
	if (newHour >= 24) {
		newDay++;
		newHour -= 24;
	}

	if (newMonth == 0 && newDay > JANDAYS) {
		newMonth++;
		newDay -= JANDAYS;
	} else if (newMonth == 1 && newDay > LEAPFEBDAYS && newYear % 4 == 0) {
		newMonth++;
		newDay -= LEAPFEBDAYS;
	} else if (newMonth == 1 && newDay > FEBDAYS) {
		newMonth++;
		newDay -= FEBDAYS;
	} else if (newMonth == 2 && newDay > MARDAYS) {
		newMonth++;
		newDay -= MARDAYS;
	} else if (newMonth == 3 && newDay > APRDAYS) {
		newMonth++;
		newDay -= APRDAYS;
	} else if (newMonth == 4 && newDay > MAYDAYS) {
		newMonth++;
		newDay -= MAYDAYS;
	} else if (newMonth == 5 && newDay > JUNDAYS) {
		newMonth++;
		newDay -= JUNDAYS;
	} else if (newMonth == 6 && newDay > JULDAYS) {
		newMonth++;
		newDay -= JULDAYS;
	} else if (newMonth == 7 && newDay > AUGDAYS) {
		newMonth++;
		newDay -= AUGDAYS;
	} else if (newMonth == 8 && newDay > SEPDAYS) {
		newMonth++;
		newDay -= SEPDAYS;
	} else if (newMonth == 9 && newDay > OCTDAYS) {
		newMonth++;
		newDay -= OCTDAYS;
	} else if (newMonth == 10 && newDay > NOVDAYS) {
		newMonth++;
		newDay -= NOVDAYS;
	} else if (newMonth == 11 && newDay > DECDAYS) {
		newMonth++;
		newDay -= DECDAYS;
	}

	return DateTime(newMonth, newDay, newYear, newHour, newMinute);
}

DateTime DateTime::operator-(const DateTime& d) const {
	unsigned int newMonth = month - d.month;
	unsigned int newDay = day - d.day;
	unsigned int newYear = year - d.year;
	unsigned int newHour = hour - d.hour;
	unsigned int newMinute = minute - d.minute;

	// adjust date and time if necessary
	if (newMinute < 0) {
		newHour--;
		newMinute += 60;
	}
	if (newHour < 0) {
		newDay--;
		newHour += 24;
	}

	if (newMonth == 0 && newDay < 0) {
		newMonth--;
		newDay += JANDAYS;
	} else if (newMonth == 1 && newDay < 0) {
		newMonth--;
		newDay += FEBDAYS;
	} else if (newMonth == 2 && newDay < 0) {
		newMonth--;
		newDay += MARDAYS;
	} else if (newMonth == 3 && newDay < 0) {
		newMonth--;
		newDay += APRDAYS;
	} else if (newMonth == 4 && newDay < 0) {
		newMonth--;
		newDay += MAYDAYS;
	} else if (newMonth == 5 && newDay < 0) {
		newMonth--;
		newDay += JUNDAYS;
	} else if (newMonth == 6 && newDay < 0) {
		newMonth--;
		newDay += JULDAYS;
	} else if (newMonth == 7 && newDay < 0) {
		newMonth--;
		newDay += AUGDAYS;
	} else if (newMonth == 8 && newDay < 0) {
		newMonth--;
		newDay += SEPDAYS;
	} else if (newMonth == 9 && newDay < 0) {
		newMonth--;
		newDay += OCTDAYS;
	} else if (newMonth == 10 && newDay < 0) {
		newMonth--;
		newDay += NOVDAYS;
	} else if (newMonth == 11 && newDay < 0) {
		newMonth--;
		newDay += DECDAYS;
	}

	return DateTime(newMonth, newDay, newYear, newHour, newMinute);
}
