#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <iostream>
#include <string>

// forward declaration
class ProjectTeam;

class Student {
  private:
	std::string name;
	std::string studentEmail;
	std::string year;
	ProjectTeam* team;

	void addToTeam(ProjectTeam* const team);
	void clearTeam();

	friend class ProjectTeam;

  public:
	Student();
	Student(std::string name, std::string studentEmail, std::string year);

	friend std::ostream& operator<<(std::ostream& out, const Student& student);
	friend std::istream& operator>>(std::istream& in, Student& student);
};

#endif	// STUDENT_HPP
