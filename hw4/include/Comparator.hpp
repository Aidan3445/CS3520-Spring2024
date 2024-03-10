#ifndef COMPARATOR_HPP
#define COMPARATOR_HPP
#include "ProjectTeam.hpp"
#include <functional>

// comparator used to compare and evaluate teams
struct Comparator {
    // team evaluation function
    std::function<int (const ProjectTeam*)> teamEval;
    // student comparator function
    std::function<bool (const StudentPref* s1, const StudentPref* s2)> studentComp;

    // constructor
    Comparator(
            std::function<int (const ProjectTeam*)> teamEval,
            std::function<bool (const StudentPref* s1, const StudentPref* s2)> studentComp)
        : teamEval(teamEval), studentComp(studentComp) {}
   
    struct TeamComp {
        // reference to the comparator
        const Comparator &comp;

        // constructor
        TeamComp(const Comparator &comp) : comp(comp) {}

        bool operator()(const ProjectTeam* lhs, const ProjectTeam* rhs) {
            return comp.teamEval(lhs) < comp.teamEval(rhs);
        }
    };

};

// camparators
extern Comparator totalSkillComp;
extern Comparator cppSkillComp;
extern Comparator gdbSkillComp;
extern Comparator algoSkillComp;
extern Comparator needMembersComp;

#endif

