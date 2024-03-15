#include "../include/projectTeam.hpp"
#include "../include/student.hpp"
#include <cstdio>
#include <string>
#include <vector>

// default constructor
ProjectTeam::ProjectTeam() { this->members = std::vector<Student*>(); }

// constructor
ProjectTeam::ProjectTeam(std::string teamName, int teamID, std::string projectTitle) {
	this->teamName = teamName;
	this->teamID = teamID;
	this->projectTitle = projectTitle;
	this->members = std::vector<Student*>();
}

// destructor
ProjectTeam::~ProjectTeam() {
	// remove the team from the members
	for (Student* member : this->members) {
		member->clearTeam();
	}
	// clear the members
	this->members.clear();
}

ProjectTeam ProjectTeam::operator-(const int& removeCount) {
	// check if the removeCount is valid
	if (removeCount > this->members.size()) {
		throw std::invalid_argument("Cannot remove more members than there are in the team.");
	}

	// make copy of the team
	ProjectTeam newTeam = ProjectTeam(this->teamName, this->teamID, this->projectTitle);
	newTeam.members = this->members;

	// remove the last removeCount members from the team
	// remove more recent additions first
	for (int i = 0; i < removeCount; i++) {
		newTeam.members.back()->team = nullptr;
		newTeam.members.pop_back();
	}

	return newTeam;
}

ProjectTeam ProjectTeam::operator+(Student& newMember) {
	// make copy of the team
	ProjectTeam newTeam = ProjectTeam(this->teamName, this->teamID, this->projectTitle);
	newTeam.members = this->members;

	// add the new member to the team
	newTeam.members.push_back(&newMember);
	// set the team of the new member
	newMember.addToTeam(&newTeam);

	return newTeam;
}

ProjectTeam ProjectTeam::operator+(const ProjectTeam& newTeam) {
	// make copy of the team
	ProjectTeam combinedTeam = ProjectTeam(this->teamName, this->teamID, this->projectTitle);
	combinedTeam.members = this->members;

	// add the new members to the team
	for (Student* member : newTeam.members) {
		combinedTeam.members.push_back(member);
		// set the team of the new member
		member->team = nullptr;
		member->addToTeam(&combinedTeam);
	}

	return combinedTeam;
}

std::vector<ProjectTeam*> ProjectTeam::operator/(const int& splitInto) {
	// check if the splitInto is valid
	if (splitInto > this->members.size()) {
		throw std::invalid_argument(
			"Cannot split the team into more teams than there are members.");
	}

	// make vector of new teams
	std::vector<ProjectTeam*> newTeams = std::vector<ProjectTeam*>();

	// add this team to the vector of new teams
	newTeams.push_back(this);

	// split the team into splitInto teams
	// split the team into equal parts
	int splitSize = this->members.size() / splitInto;
	int remainder = this->members.size() % splitInto;
	// split the team into splitInto teams
	for (int i = 1; i < splitInto; i++) {
		ProjectTeam* splitTeam = new ProjectTeam(
			this->teamName + " split " + std::to_string(i), this->teamID + 1, this->projectTitle);
		// add the members to the split team
		for (int j = 0; j < splitSize; j++) {
			splitTeam->members.push_back(this->members.back());
			// set the team of the new member
			this->members.back()->team = nullptr;
			this->members.back()->addToTeam(splitTeam);
			this->members.pop_back();
		}

		// if there is a remainder, add one member extra to the split team
		if (i < remainder) {
			splitTeam->members.push_back(this->members.back());
			// set the team of the new member
			this->members.back()->team = nullptr;
			this->members.back()->addToTeam(splitTeam);
			this->members.pop_back();
		}

		// add the split team to the vector of new teams
		newTeams.push_back(splitTeam);
	}

	return newTeams;
}

std::ostream& operator<<(std::ostream& out, const ProjectTeam& team) {
	out << "Team Name: " << team.teamName << std::endl;
	out << "Team ID: " << team.teamID << std::endl;
	out << "Project Title: " << team.projectTitle << std::endl;
	out << "Team Members: (" << team.members.size() << ")" << std::endl;
	for (Student* member : team.members) {
		out << *member << std::endl;
	}
	return out;
}

std::istream& operator>>(std::istream& in, ProjectTeam& team) {
	std::string teamName;
	int teamID;
	std::string projectTitle;

	std::cout << "Enter team name: ";
	std::getline(in, teamName);
	std::cout << "Enter team ID (integer): ";
	in >> teamID;
	std::cout << "Enter project title: ";
	std::getline(in, projectTitle);

	team = ProjectTeam(teamName, teamID, projectTitle);
	return in;
}
