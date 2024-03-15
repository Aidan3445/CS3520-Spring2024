#ifndef PROJECTTEAM_HPP
#define PROJECTTEAM_HPP

#include "student.hpp"
#include <stdexcept>
#include <vector>

class ProjectTeam {
  private:
	std::string teamName;
	int teamID;
	std::string projectTitle;
	std::vector<Student*> members;

  public:
	ProjectTeam();
	ProjectTeam(std::string teamName, int teamID, std::string projectTitle);
	~ProjectTeam();

	ProjectTeam operator-(const int& removeCount);
	ProjectTeam operator+(Student& newMember);
	ProjectTeam operator+(const ProjectTeam& newTeam);
	std::vector<ProjectTeam*> operator/(const int& splitInto);

	friend std::ostream& operator<<(std::ostream& out, const ProjectTeam& team);
	friend std::istream& operator>>(std::istream& in, ProjectTeam& team);
};

#endif	// PROJECTTEAM_HPP
