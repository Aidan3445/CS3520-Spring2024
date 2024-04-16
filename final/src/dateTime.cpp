#include "../include/dateTime.hpp"


// constructor
DateTime::DateTime(unsigned int month,
				   unsigned int day,
				   unsigned int year,
				   unsigned int hour,
				   unsigned int minute) {
	tm t = {0};
	// months are 0-indexed
	t.tm_mon = month - 1;
	t.tm_mday = day;
	// years are years since 1900
	t.tm_year = year - 1900;
	t.tm_hour = hour;
	t.tm_min = minute;

	// convert to time_t
	dateAndTime = mktime(&t);
}

// getters
unsigned int DateTime::getMonth() const {
	tm* t = localtime(&dateAndTime);
	return t->tm_mon + 1;
}

unsigned int DateTime::getDay() const {
	tm* t = localtime(&dateAndTime);
	return t->tm_mday;
}

unsigned int DateTime::getYear() const {
	tm* t = localtime(&dateAndTime);
	return t->tm_year + 1900;
}

unsigned int DateTime::getHour() const {
	tm* t = localtime(&dateAndTime);
	return t->tm_hour;
}

unsigned int DateTime::getMin() const {
	tm* t = localtime(&dateAndTime);
	return t->tm_min;
}

// string representations of the date and time
std::string DateTime::getDate() const {
	tm* t = localtime(&dateAndTime);
	std::stringstream ss;
	ss << getMonth() << '/' << getDay() << '/' << getYear();
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
	ss << dayOfWeek << " " << getDate();

	return ss.str();
}

std::string DateTime::getTime() const {
	tm* t = localtime(&dateAndTime);
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(2) << getHour() << ':' << std::setfill('0') << std::setw(2)
	   << getMin();
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
DateTime DateTime::add(const unsigned int& month,
					   const unsigned int& day,
					   const unsigned int& year,
					   const unsigned int& hour,
					   const unsigned int& minute) const {
	return DateTime(
		getMonth() + month, getDay() + day, getYear() + year, getHour() + hour, getMin() + year);
}

DateTime DateTime::sub(const unsigned int& month,
					   const unsigned int& day,
					   const unsigned int& year,
					   const unsigned int& hour,
					   const unsigned int& minute) const {
	return DateTime(
		getMonth() - month, getDay() - day, getYear() - year, getHour() - hour, getMin() - year);
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
