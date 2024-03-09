#ifndef GROUPCREATOR_HPP
#define GROUPCREATOR_HPP

#include "Comparator.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>

struct GroupCreator {
    // read student preferences from a CSV file
    std::vector<StudentPref*> readStudentPrefs(std::string filename);

    // write teams to a CSV file
    void writeTeamsToCSV(std::string filename, std::vector<ProjectTeam*> teams);

    // create teams from preferences
    std::vector<ProjectTeam*> preferentialTeams(std::vector<StudentPref*> students);

    // update teams to have more balanced skill levels in each area
    std::vector<ProjectTeam*> balanceTeams(std::vector<ProjectTeam*> teams, Comparator comp, 
            int maxIterations, double maxDelta);

    // calculate the standard deviation of a set of teams
    double standardDeviation(std::vector<ProjectTeam*> teams, Comparator comp);
};

#endif
