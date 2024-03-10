#ifndef GROUPCREATOR_HPP
#define GROUPCREATOR_HPP

#include "Comparator.hpp"
#include <cmath>
#include <fstream>
#include <set>
#include <string>

struct GroupCreator {
	std::string filename;
	int groupMinSize;
	int groupMaxSize;
	// constructor
	GroupCreator(std::string filename, int groupMinSize, int groupMaxSize) :
		filename(filename), groupMinSize(groupMinSize), groupMaxSize(groupMaxSize) {
		// validate the group sizes
		if (groupMinSize < 1 || groupMaxSize < 1 || groupMinSize > groupMaxSize) {
			throw std::invalid_argument("Invalid group size");
		}
	}

	// read student preferences from a CSV file
	std::vector<StudentPref*> readStudentPrefs();

	// write teams to a CSV file
	void writeTeamsToCSV(std::string filename, std::vector<ProjectTeam*> teams);

	// create teams from preferences
	std::vector<ProjectTeam*> preferentialTeams(std::vector<StudentPref*> students);

	// update teams to have more balanced skill levels in each area
	std::vector<ProjectTeam*> balanceTeams(std::vector<ProjectTeam*> teams,
										   Comparator comp,
										   int maxIterations,
										   double maxDelta);

	// calculate the standard deviation of a set of teams
	double standardDeviation(std::vector<ProjectTeam*> teams, Comparator comp);
};

#endif
