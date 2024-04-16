#include "../include/dateTime.hpp"

// define color codes
#define RESET "\033[0m"
#define WEEK_DAY "\033[1;33m"
#define DATE_TIME "\033[33m"

// constructor
DateTime::DateTime(int month, int day, int year, int hour, int minute) {
	tm t = {0};
	// months are 0-indexed
	t.tm_mon = month - 1;
	t.tm_mday = day;
	// years are years since 1900
	t.tm_year = year - 1900;
	t.tm_hour = hour;
	t.tm_min = minute;
	// disable daylight savings time
	t.tm_isdst = -1;

	// convert to time_t
	dateAndTime = mktime(&t);
}

// copy constructor
DateTime::DateTime(const DateTime& d) { dateAndTime = d.dateAndTime; }

// assignment operator
DateTime& DateTime::operator=(const DateTime& d) {
	if (this == &d) {
		return *this;
	}

	dateAndTime = d.dateAndTime;
	return *this;
}

// getters
int DateTime::getMonth() const {
	tm* t = localtime(&dateAndTime);
	return t->tm_mon + 1;
}

int DateTime::getDay() const {
	tm* t = localtime(&dateAndTime);
	return t->tm_mday;
}

int DateTime::getYear() const {
	tm* t = localtime(&dateAndTime);
	return t->tm_year + 1900;
}

int DateTime::getHour() const {
	tm* t = localtime(&dateAndTime);
	return t->tm_hour;
}

int DateTime::getMin() const {
	tm* t = localtime(&dateAndTime);
	return t->tm_min;
}

// string representations of the date and time
std::string DateTime::getDate() const {
	tm* t = localtime(&dateAndTime);
	std::stringstream ss;
	ss << DATE_TIME << std::setfill('0') << std::setw(2) << getMonth() << '/' << std::setfill('0')
	   << std::setw(2) << getDay() << '/' << std::setfill('0') << std::setw(4) << getYear()
	   << RESET;
	return ss.str();
}

std::string DateTime::getDayOfWeek() const {
	tm* t = localtime(&dateAndTime);
	std::string dayOfWeek;
	switch (t->tm_wday) {
		case 0: dayOfWeek = "Sunday"; break;
		case 1: dayOfWeek = "Monday"; break;
		case 2: dayOfWeek = "Tuesday"; break;
		case 3: dayOfWeek = "Wednesday"; break;
		case 4: dayOfWeek = "Thursday"; break;
		case 5: dayOfWeek = "Friday"; break;
		case 6: dayOfWeek = "Saturday"; break;
		default: return "Invalid day";
	}

	std::stringstream ss;
	ss << WEEK_DAY << dayOfWeek << " " << RESET << getDate();

	return ss.str();
}

std::string DateTime::getTime() const {
	tm* t = localtime(&dateAndTime);
	std::stringstream ss;
	ss << DATE_TIME << std::setfill('0') << std::setw(2) << getHour() << ':' << std::setfill('0')
	   << std::setw(2) << getMin() << RESET;
	return ss.str();
}

// get the first day of the week
DateTime DateTime::getFirstDayOfWeek() const {
	tm t = *localtime(&dateAndTime);
	t.tm_mday -= t.tm_wday;
	mktime(&t);
	return DateTime(t.tm_mon + 1, t.tm_mday, t.tm_year + 1900);
}

// check if the date is within 7 days of the current date
bool DateTime::sameWeek(const DateTime& d) const {
	DateTime thisWeek = getFirstDayOfWeek();
	DateTime dWeek = d.getFirstDayOfWeek();
	return thisWeek == dWeek;
}

// operator overloads
DateTime DateTime::add(
	const int& month, const int& day, const int& year, const int& hour, const int& minute) const {
	return DateTime(
		getMonth() + month, getDay() + day, getYear() + year, getHour() + hour, getMin() + minute);
}

DateTime DateTime::sub(
	const int& month, const int& day, const int& year, const int& hour, const int& minute) const {
	return DateTime(
		getMonth() - month, getDay() - day, getYear() - year, getHour() - hour, getMin() - minute);
}

bool DateTime::operator<(const DateTime& d) const { return dateAndTime < d.dateAndTime; }

bool DateTime::operator>(const DateTime& d) const { return dateAndTime > d.dateAndTime; }

bool DateTime::operator==(const DateTime& d) const { return dateAndTime == d.dateAndTime; }

bool DateTime::operator<=(const DateTime& d) const { return dateAndTime <= d.dateAndTime; }

bool DateTime::operator>=(const DateTime& d) const { return dateAndTime >= d.dateAndTime; }

// friend functions
std::ostream& operator<<(std::ostream& os, const DateTime& d) {
	tm* t = localtime(&d.dateAndTime);
	os << d.getDate() << " " << d.getTime();
	return os;
}
