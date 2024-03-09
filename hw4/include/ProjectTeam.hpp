#ifndef PROJECTTEAM_HPP
#define PROJECTTEAM_HPP

#include "StudentPref.hpp"
#include <numeric>

struct ProjectTeam {
    // list of members
    std::vector<StudentPref*> members;
    // min and max size of the team
    int minSize;
    int maxSize;

    // constructor
    ProjectTeam(int minSize, int maxSize) : minSize(minSize), maxSize(maxSize) {}

    // get the sum of the skill levels of the team in a particular area
    int cppSkillSum() const;
    int gdbSkillSum() const;
    int algoSkillSum() const;

    // is the team full
    bool isFull() const;

    // return if a student is rejected by any member of the team
    bool isRejected(const StudentPref* student) const;
};

#endif
