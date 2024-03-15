#include "../include/student.hpp"

// default constructor
Student::Student() { this->team = nullptr; }

// constructor
Student::Student(std::string name, std::string studentEmail, std::string year) {
	this->name = name;
	this->studentEmail = studentEmail;
	this->year = year;
	this->team = nullptr;
}

// add player to a team
void Student::addToTeam(ProjectTeam* const team) {
	// make sure the player is not already on a team
	if (this->team != nullptr) {
		throw std::invalid_argument("Student is already on a team.");
	}

	this->team = team;
}

// remove player from a team
void Student::clearTeam() { this->team = nullptr; }

// overload the << operator to print a student
std::ostream& operator<<(std::ostream& out, const Student& student) {
	out << "Name: " << student.name << std::endl;
	out << "Email: " << student.studentEmail << std::endl;
	out << "Year: " << student.year << std::endl;
	return out;
}

// overload the >> operator to read a student
std::istream& operator>>(std::istream& in, Student& student) {
	std::string name;
	std::string email;
	std::string year;

	std::cout << "Enter student name: ";
	std::getline(in, name);
	std::cout << "Enter student email: ";
	std::getline(in, email);
	std::cout << "Enter student year: ";
	std::getline(in, year);

	student = Student(name, email, year);
	return in;
}
