#include "../include/ProjectTeam.hpp"
#include <iostream>

// comparator for sorting teams by how many members they need
bool NeedMembersComparator::operator()
    (const ProjectTeam* lhs, const ProjectTeam* rhs) const {
        return lhs->members.size() < rhs->members.size();
    }

// is a student rejected by this team
bool ProjectTeam::isRejected(const StudentPref* student) const {
    return std::any_of(members.begin(), members.end(), [student](const StudentPref* member) {
            return member->isRejected(student) || student->isRejected(member);
            });
}

// is the team full
bool ProjectTeam::isFull() const {
    return members.size() > 3;
}
