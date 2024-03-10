#include "../include/Comparator.hpp"

// total skill level evaluator and comparator
int evaluateTeamTotalSkill(const ProjectTeam* team) {
	return team->cppSkillSum() + team->gdbSkillSum() + team->algoSkillSum();
}
bool evaluateStudentTotalSkill(const StudentPref* s1, const StudentPref* s2) {
	return (int)s1->cppSkill + (int)s1->gdbSkill + (int)s1->algoSkill <
		   (int)s2->cppSkill + (int)s2->gdbSkill + (int)s2->algoSkill;
}

// cpp skill level evaluator and comparator
int evaluateTeamCppSkill(const ProjectTeam* team) { return team->cppSkillSum(); }
bool compareStudentCppSkill(const StudentPref* s1, const StudentPref* s2) {
	return (int)s1->cppSkill < (int)s2->cppSkill;
}

// gdb skill level evaluator and comparator
int evaluateTeamGdbSkill(const ProjectTeam* team) { return team->gdbSkillSum(); }
bool compareStudentGdbSkill(const StudentPref* s1, const StudentPref* s2) {
	return (int)s1->gdbSkill < (int)s2->gdbSkill;
}
// algo skill level evaluator and comparator
int evaluateTeamAlgoSkill(const ProjectTeam* team) { return team->algoSkillSum(); }
bool compareStudentAlgoSkill(const StudentPref* s1, const StudentPref* s2) {
	return (int)s1->algoSkill < (int)s2->algoSkill;
}

// comparator for sorting teams by how many members they need
int evaluateTeamNeedMembers(const ProjectTeam* team) { return team->members.size(); }

// camparators
Comparator totalSkillComp(evaluateTeamTotalSkill, evaluateStudentTotalSkill);
Comparator cppSkillComp(evaluateTeamCppSkill, compareStudentCppSkill);
Comparator gdbSkillComp(evaluateTeamGdbSkill, compareStudentGdbSkill);
Comparator algoSkillComp(evaluateTeamAlgoSkill, compareStudentAlgoSkill);
Comparator needMembersComp(evaluateTeamNeedMembers, NULL);
