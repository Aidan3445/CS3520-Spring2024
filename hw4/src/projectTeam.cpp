#include "../include/ProjectTeam.hpp"

// is a student rejected by this team
bool ProjectTeam::isRejected(const StudentPref* student) const {
    return std::any_of(members.begin(), members.end(), [student](const StudentPref* member) {
            return member->isRejected(student) || student->isRejected(member);
            });
}

// is the team full
bool ProjectTeam::isFull() const {
    return members.size() > minSize;
}

// calculate the skill level of the team for each skill
int ProjectTeam::cppSkillSum() const {
    return std::accumulate(members.begin(), members.end(), 0, [](int sum, const StudentPref* student) {
            return sum + (int)student->cppSkill;
            });
}

int ProjectTeam::gdbSkillSum() const {
    return std::accumulate(members.begin(), members.end(), 0, [](int sum, const StudentPref* student) {
            return sum + (int)student->gdbSkill;
            });
}

int ProjectTeam::algoSkillSum() const {
    return std::accumulate(members.begin(), members.end(), 0, [](int sum, const StudentPref* student) {
            return sum + (int)student->algoSkill;
            });
}
