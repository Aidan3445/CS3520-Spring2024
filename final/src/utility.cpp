#include "../include/utility.hpp"

namespace util {
// helper to remove spaces
std::string removeSpaces(const std::string& str) {
	char res[str.length()];
	int index = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] != ' ') {
			res[index] = str[i];
			index++;
		}
	}
	res[index] = '\0';
	return res;
}

// helper to get the next field
std::string next(const std::string& line, const char& divider) {
	std::string field = line.substr(0, line.find(divider));
	return field;
}

std::string nextIgnoreSpaces(const std::string& line, const char& divider) {
	return removeSpaces(next(line, divider));
}

std::string next(const std::string& line) { return next(line, ';'); }
// helper to get the next element in a list
std::string nextEl(std::string& line, const char& divider) {
	std::string field = line.substr(0, line.find(divider));
	return field;
}

std::string nextEl(std::string& line) { return nextEl(line, ','); }
// helper to shift the line
void shift(std::string& line, const char& divider) { line = line.substr(line.find(divider) + 1); }
void shift(std::string& line) { return shift(line, ';'); }
// helper to shift the line for elements
void shiftEl(std::string& line) { return shift(line, ','); }
}  // namespace util
