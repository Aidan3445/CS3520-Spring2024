#ifndef PROJECTTEAM_HPP
#define PROJECTTEAM_HPP

#include "StudentPref.hpp"

struct ProjectTeam {
    // list of members
    std::vector<StudentPref*> members;

    // get the sum of the skill levels of the team in a particular area
    int cppSkillSum() const;
    int gdbSkillSum() const;
    int algoSkillSum() const;

    // is the team full
    bool isFull() const;

    // return if a student is rejected by any member of the team
    bool isRejected(const StudentPref* student) const;
};

// comparators for ProjectTeam
struct NeedMembersComparator {
    // compare two teams based on the number of members they need
    bool operator()(const ProjectTeam* lhs, const ProjectTeam* rhs) const;
};

struct SkillLevelComparator {
    // compare two teams based on the sum of their skill levels
    bool operator()(const ProjectTeam* lhs, const ProjectTeam* rhs) const;
};

#endif
