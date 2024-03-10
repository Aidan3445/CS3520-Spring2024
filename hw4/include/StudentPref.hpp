#ifndef STUDENTPREF_HPP
#define STUDENTPREF_HPP
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// forward declaration to avoid circular dependency
struct ProjectTeam;

struct StudentPref {
	// The skill level of a student in a particular area
	enum class skillLevel { beginner, intermediate, advanced };

	// convert skill level to string and vice versa
	static std::string skillLevelToString(skillLevel skill) {
		switch (skill) {
			case skillLevel::beginner: return "Beginner";
			case skillLevel::intermediate: return "Intermediate";
			case skillLevel::advanced: return "Advanced";
			default: throw std::invalid_argument("Invalid skill level");
		}
	}

	static skillLevel stringToSkillLevel(std::string skill) {
		if (skill == "Beginner") {
			return skillLevel::beginner;
		} else if (skill == "Intermediate") {
			return skillLevel::intermediate;
		} else if (skill == "Advanced") {
			return skillLevel::advanced;
		}

		throw std::invalid_argument("Invalid skill level: " + skill);
	}

	// read student preferences from a CSV line
	StudentPref(std::string line) {
		// first entry: username
		std::string username = line.substr(0, line.find(','));
		line = line.substr(line.find(',') + 1);

		// second entry: cpp skill
		skillLevel cppSkill = stringToSkillLevel(line.substr(0, line.find(',')));
		line = line.substr(line.find(',') + 1);

		// third entry: gdb skill
		skillLevel gdbSkill = StudentPref::stringToSkillLevel(line.substr(0, line.find(',')));
		line = line.substr(line.find(',') + 1);

		// fourth entry: algo skill
		skillLevel algoSkill = StudentPref::stringToSkillLevel(line.substr(0, line.find(',')));
		line = line.substr(line.find(',') + 1);

		// fifth entry (list): rejected partners
		std::vector<std::string> rejectedPartnersUsernames;
		std::string rejectedPartners = line.substr(0, line.find(','));
		while (rejectedPartners.find(';') != std::string::npos) {
			rejectedPartnersUsernames.push_back(
				rejectedPartners.substr(0, rejectedPartners.find(';')));
			rejectedPartners = rejectedPartners.substr(rejectedPartners.find(';') + 1);
		}
		// add the last entry
		if (rejectedPartners.size() > 0) {
			rejectedPartnersUsernames.push_back(rejectedPartners);
		}
		line = line.substr(line.find(',') + 1);

		// sixth entry (list): preferred partners
		std::vector<std::string> preferredPartnersUsernames;
		std::string preferredPartners = line.substr(0, line.find(','));
		while (preferredPartners.find(';') != std::string::npos) {
			preferredPartnersUsernames.push_back(
				preferredPartners.substr(0, preferredPartners.find(';')));
			preferredPartners = preferredPartners.substr(preferredPartners.find(';') + 1);
		}
		// add the last entry
		if (preferredPartners.size() > 0) {
			preferredPartnersUsernames.push_back(preferredPartners);
		}

		// set the member variables
		this->username = username;
		this->cppSkill = cppSkill;
		this->gdbSkill = gdbSkill;
		this->algoSkill = algoSkill;
		this->rejectedPartnersUsernames = rejectedPartnersUsernames;
		this->preferredPartnersUsernames = preferredPartnersUsernames;

		this->rejectedPartners = std::vector<StudentPref*>();
		this->preferredPartners = std::vector<StudentPref*>();
		this->team = nullptr;
	}

	// student's username
	std::string username;

	// skill levels
	skillLevel cppSkill;
	skillLevel gdbSkill;
	skillLevel algoSkill;

	// list of prefered and rejected partners
	std::vector<StudentPref*> rejectedPartners;
	std::vector<StudentPref*> preferredPartners;
	std::vector<std::string> preferredPartnersUsernames;
	std::vector<std::string> rejectedPartnersUsernames;

	// pointer to a student's team
	ProjectTeam* team;

	// is rejected by the student
	bool isRejected(const StudentPref* student) const;

	bool operator==(const StudentPref* rhs) const;
};

#endif
