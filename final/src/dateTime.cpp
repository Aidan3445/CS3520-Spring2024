#include "../include/dateTime.hpp"
#include <utility>


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

std::pair<DateTime, DateTime> DateTime::readEventTimes() {
	bool confirmed = false;
	DateTime example(10, 23, 2010, 14, 20);
	unsigned int month;
	unsigned int day;
	unsigned int year;
	unsigned int startHour;
	unsigned int startMin;
	unsigned int endHour;
	unsigned int endMin;
	char input;
	DateTime startTime;
	DateTime endTime;
	std::cout << "Enter an invalid character at any time to quit" << std::endl;
	while (!confirmed) {
		try {
			std::cout << "What is the start date of this event? (ex. " << example.getDate() << ")"
					  << std::endl;
			std::string line;
			std::getline(std::cin, line);
			month = stoi(util::next(line, '/'));
			util::shift(line, '/');
			day = stoi(util::next(line, '/'));
			util::shift(line, '/');
			year = stoi(line);

			std::cout << "What is the start time of this event? (ex. " << example.getTime() << ")"
					  << std::endl;

			std::getline(std::cin, line);
			util::shift(line, ' ');
			startHour = stoi(util::next(line, ':'));
			util::shift(line, ':');
			startMin = stoi(line);

			std::cout << "What is the end time of this event? (ex. " << example.getTime() << ")"
					  << std::endl;

			std::getline(std::cin, line);
			util::shift(line, ' ');
			endHour = stoi(util::next(line, ':'));
			util::shift(line, ':');
			endMin = stoi(line);

			// create times
			startTime = DateTime(month, day, year, startHour, startMin);
			endTime = DateTime(month, day, year, endHour, endMin);

			std::cout << "Is this the correct interval? " << startTime << " - " << endTime.getTime()
					  << std::endl;
			do {
				std::cout << "type [a] to accept or [t] to try again" << std::endl;
				std::cin >> input;
				std::cin.ignore();
			} while (input != 'a' && input != 't');
			confirmed = input == 'a';
		} catch (std::runtime_error& error) {
			std::cout << ERROR << "Invalid times" << RESET << std::endl;
			do {
				std::cout << "type [c] to try again or [q] to quit" << std::endl;
				std::cin >> input;
				std::cin.ignore();
			} while (input != 'c' && input != 'q');
			if (input == 'q') {
				// No date was read
				throw std::exception();
			}
		}
	}
	// Returns the read DateTime
	return std::make_pair(startTime, endTime);
}

DateTime DateTime::readStartTime() {
	bool confirmed = false;
	DateTime example(10, 23, 2010, 14, 20);
	unsigned int month;
	unsigned int day;
	unsigned int year;
	unsigned int startHour;
	unsigned int startMin;
	char input;
	DateTime startTime;
	std::cout << "Enter an invalid character at any time to quit" << std::endl;
	while (!confirmed) {
		try {
			std::cout << "What is the start date of this event? (ex. " << example.getDate() << ")"
					  << std::endl;
			std::string line;
			std::getline(std::cin, line);
			month = stoi(util::next(line, '/'));
			util::shift(line, '/');
			day = stoi(util::next(line, '/'));
			util::shift(line, '/');
			year = stoi(line);

			std::cout << "What is the start time of this event? (ex. " << example.getTime() << ")"
					  << std::endl;

			std::getline(std::cin, line);
			util::shift(line, ' ');
			startHour = stoi(util::next(line, ':'));
			util::shift(line, ':');
			startMin = stoi(line);

			// create times
			startTime = DateTime(month, day, year, startHour, startMin);

			std::cout << "Is this the correct time? " << startTime << std::endl;
			do {
				std::cout << "type [a] to accept or [t] to try again" << std::endl;
				std::cin >> input;
				std::cin.ignore();
			} while (input != 'a' && input != 't');
			confirmed = input == 'a';
		} catch (std::runtime_error& error) {
			std::cout << ERROR << "Invalid time" << RESET << std::endl;
			do {
				std::cout << "type [c] to try again or [q] to quit" << std::endl;
				std::cin >> input;
				std::cin.ignore();
			} while (input != 'c' && input != 'q');
			if (input == 'q') {
				// No date was read
				throw std::exception();
			}
		}
	}
	// Returns the read DateTime
	return startTime;
}