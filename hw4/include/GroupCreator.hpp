#ifndef GROUPCREATOR_HPP
#define GROUPCREATOR_HPP

#include "ProjectTeam.hpp"
#include "StudentPref.hpp"
#include "Comparator.hpp"

struct GroupCreator {
    // read student preferences from a CSV file
    std::vector<StudentPref*> readStudentPrefs(std::string filename);

    // create teams from preferences
    std::vector<ProjectTeam*> preferentialTeams(std::vector<StudentPref*> students);

    // update teams to have more balanced skill levels in each area
    std::vector<ProjectTeam*> balanceTeams(std::vector<ProjectTeam*> teams, Comparator comp, 
            int maxIterations, double maxDelta);

    // calculate the standard deviation of a set of teams
    double standardDeviation(std::vector<ProjectTeam*> teams, Comparator comp);
};

#endif
