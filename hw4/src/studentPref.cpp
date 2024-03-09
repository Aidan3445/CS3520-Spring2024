#include "../include/StudentPref.hpp"

// is a student rejected by this student
bool StudentPref::isRejected(const StudentPref* student) const {
    return std::any_of(rejectedPartners.begin(), rejectedPartners.end(),
            [student](const StudentPref* rejected) { return rejected == student;
            });
}

// overload the == operator for StudentPref
bool StudentPref::operator==(const StudentPref* rhs) const {
    return username == rhs->username;
}

// student preference comparator for number of preferred vs rejected students
// more preferred students should be ahead of fewer preferred students, then
// more rejected students should be ahead of fewer rejected students
bool StudentPrefComparator::preferrencesComp::operator()
    (const StudentPref& lhs, const StudentPref& rhs) const {
        if (lhs.preferredPartners.size() > rhs.preferredPartners.size()) {
            return true;
        } else if (lhs.preferredPartners.size() < rhs.preferredPartners.size()) {
            return false;
        } else {
            if (lhs.rejectedPartners.size() > rhs.rejectedPartners.size()) {
                return true;
            } else {
                return false;
            }
        }
    }

// student preference comparator for total skill level
// higher total skill level should be ahead of lower total skill level
bool StudentPrefComparator::totalSkillComp::operator()
    (const StudentPref& lhs, const StudentPref& rhs) const {
        return (int)lhs.cppSkill + (int)lhs.gdbSkill + (int)lhs.algoSkill > 
            (int)rhs.cppSkill + (int)rhs.gdbSkill + (int)rhs.algoSkill;
    }

// student preference comparator for C++ skill level
// higher C++ skill level should be ahead of lower C++ skill level
bool StudentPrefComparator::cppSkillComp::operator()
    (const StudentPref& lhs, const StudentPref& rhs) const {
        return lhs.cppSkill > rhs.cppSkill;
    }

// student preference comparator for GDB skill level
// higher GDB skill level should be ahead of lower GDB skill level
bool StudentPrefComparator::gdbSkillComp::operator()
    (const StudentPref& lhs, const StudentPref& rhs) const {
        return lhs.gdbSkill > rhs.gdbSkill;
    }

// student preference comparator for algorithm skill level
// higher algorithm skill level should be ahead of lower algorithm skill level
bool StudentPrefComparator::algoSkillComp::operator()
    (const StudentPref& lhs, const StudentPref& rhs) const {
        return lhs.algoSkill > rhs.algoSkill;
    }
