#include "../include/GroupCreator.hpp"
#include "../include/ProjectTeam.hpp"
#include <iostream>
#include <vector>

namespace utils {
    std::string toLower(std::string str) {
        for (char &c : str) {
            c = tolower(c);
        }
        return str;
    }
}

int main() {
    GroupCreator gc;
    // read student preferences from a CSV file
    std::vector<StudentPref*> students = gc.readStudentPrefs("data/Assignment4 Roster Pref3.csv");
    // map the students to their preferences
    for (auto &student : students) {
        for (auto &partnerUsername : student->preferredPartnersUsernames) {
            auto it = std::find_if(students.begin(), students.end(), [&partnerUsername](StudentPref* s) {
                    return utils::toLower(s->username) == utils::toLower(partnerUsername);
                    });
            if (it != students.end()) {
                student->preferredPartners.push_back(*it);
            }
        }

        for (auto &partnerUsername : student->rejectedPartnersUsernames) {
            auto it = std::find_if(students.begin(), students.end(), [&partnerUsername](StudentPref* s) {
                    return utils::toLower(s->username) == utils::toLower(partnerUsername);
                    });
            if (it != students.end()) {
                student->rejectedPartners.push_back(*it);
            }
        }
    }

    // create preferential teams
    std::vector<ProjectTeam*> teams = gc.preferentialTeams(students);

    for (auto &team : teams) {
        std::cout << "Team (" << team->members.size() << "): ";
        for (auto &member : team->members) {
            std::cout << member->username << " ";
        }
        std::cout << std::endl;
    }

    //teams = gc.balanceTeams(teams, Comparator(), 100, 0.01);
    //std::cout << "Standard deviation: " << gc.standardDeviation(teams, Comparator()) << std::endl;
    return 0;
}
