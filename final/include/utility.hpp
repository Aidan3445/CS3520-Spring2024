#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

// Color codes for text
#define HEADER "\033[1m"
#define RESET "\033[0m"
#define EVENT_NAME "\033[94m"
#define USER "\033[36m"
#define DOLLARS "\033[32m$"
#define WEEK_DAY "\033[1;33m"
#define DATE_TIME "\033[33m"
#define ERROR "\033[91m"

#define CLEAR_LINE "\033[A\33[2K\r"

namespace util {
// helper to remove spaces
std::string removeSpaces(const std::string& str);

// helper to get the next field
std::string next(const std::string& line, const char& divider);

std::string nextIgnoreSpaces(const std::string& line, const char& divider);

std::string next(const std::string& line);
// helper to get the next element in a list
std::string nextEl(std::string& line, const char& divider);

std::string nextEl(std::string& line);
// helper to shift the line
void shift(std::string& line, const char& divider);
void shift(std::string& line);
// helper to shift the line for elements
void shiftEl(std::string& line);
}  // namespace util

#endif	// UTIL_HPP
