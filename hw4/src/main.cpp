#include "../include/Comparator.hpp"
#include "../include/GroupCreator.hpp"
#include <iomanip>

namespace utils {
std::string toLower(std::string str) {
	for (char& c : str) {
		c = tolower(c);
	}
	return str;
}
}  // namespace utils

int main() {
	GroupCreator gc("data/Assignment4 Roster Pref3.csv", 5, 6);
	// read student preferences from a CSV file
	std::vector<StudentPref*> students = gc.readStudentPrefs();
	// map the students to their preferences
	for (auto& student : students) {
		for (auto& partnerUsername : student->preferredPartnersUsernames) {
			auto it =
				std::find_if(students.begin(), students.end(), [&partnerUsername](StudentPref* s) {
					return utils::toLower(s->username) == utils::toLower(partnerUsername);
				});
			if (it != students.end()) {
				student->preferredPartners.push_back(*it);
			}
		}

		for (auto& partnerUsername : student->rejectedPartnersUsernames) {
			auto it =
				std::find_if(students.begin(), students.end(), [&partnerUsername](StudentPref* s) {
					return utils::toLower(s->username) == utils::toLower(partnerUsername);
				});
			if (it != students.end()) {
				student->rejectedPartners.push_back(*it);
			}
		}
	}

	// create preferential teams
	std::vector<ProjectTeam*> teams = gc.preferentialTeams(students);

	std::cout << "\033[4mcpp gdb alg sum: Team # | Members...\033[0m" << std::endl;
	for (int i = 0; i < teams.size(); i++) {
		std::cout << std::setw(2) << teams[i]->cppSkillSum() << ", " << std::setw(2)
				  << teams[i]->gdbSkillSum() << ", " << std::setw(2) << teams[i]->algoSkillSum()
				  << ", " << std::setw(3)
				  << teams[i]->cppSkillSum() + teams[i]->gdbSkillSum() + teams[i]->algoSkillSum()
				  << ": Team " << i + 1 << " | ";
		for (auto& member : teams[i]->members) {
			std::cout << member->username << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "Initial Standard deviation: " << gc.standardDeviation(teams, totalSkillComp)
			  << std::endl
			  << std::endl;

	// balance the teams, multiple iterations allow for better balancing
	for (int i = 0; i < 100; i++) {
		teams = gc.balanceTeams(teams, totalSkillComp, 100, 1);
		teams = gc.balanceTeams(teams, algoSkillComp, 100, 1);
		teams = gc.balanceTeams(teams, cppSkillComp, 100, 1);
		teams = gc.balanceTeams(teams, gdbSkillComp, 100, 1);
	}

	std::cout << "\033[4mcpp gdb alg sum: Team # | Members...\033[0m" << std::endl;
	for (int i = 0; i < teams.size(); i++) {
		std::cout << std::setw(2) << teams[i]->cppSkillSum() << ", " << std::setw(2)
				  << teams[i]->gdbSkillSum() << ", " << std::setw(2) << teams[i]->algoSkillSum()
				  << ", " << std::setw(3)
				  << teams[i]->cppSkillSum() + teams[i]->gdbSkillSum() + teams[i]->algoSkillSum()
				  << ": Team " << i + 1 << " | ";
		for (auto& member : teams[i]->members) {
			std::cout << member->username << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "Balanced Standard deviation: " << gc.standardDeviation(teams, totalSkillComp)
			  << std::endl;
	std::cout << "(Standard deviation of total skill level from the mean of indidual student skill "
				 "levels)"
			  << std::endl
			  << std::endl;

	// check preferences and rejections
	for (auto& student : students) {
		for (auto& partner : student->preferredPartners) {
			if (student->team != partner->team) {
				std::cout << "\033[31m" << student->username << " prefers " << partner->username
						  << " but is not on the same team\033[0m" << std::endl;
			} else {
				std::cout << "\033[32m" << student->username << " prefers " << partner->username
						  << " and is on the same team\033[0m" << std::endl;
			}
		}
		for (auto& partner : student->rejectedPartners) {
			if (student->team == partner->team) {
				std::cout << "\033[31m" << student->username << " rejects " << partner->username
						  << " but is on the same team\033[0m" << std::endl;
			} else {
				std::cout << "\033[32m" << student->username << " rejects " << partner->username
						  << " and is not on the same team\033[0m" << std::endl;
			}
		}
	}

	gc.writeTeamsToCSV("data/Teams.csv", teams);


	// free memory
	for (auto& team : teams) {
		delete team;
	}

	return 0;
}
