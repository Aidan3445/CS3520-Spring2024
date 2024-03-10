#include "../include/StudentPref.hpp"

// overload the == operator for StudentPref
bool StudentPref::operator==(const StudentPref* rhs) const { return username == rhs->username; }

// is a student rejected by this student
bool StudentPref::isRejected(const StudentPref* student) const {
	return std::any_of(rejectedPartners.begin(),
					   rejectedPartners.end(),
					   [student](const StudentPref* rejected) { return rejected == student; });
}
