#include "../include/GroupCreator.hpp"

// read students from a CSV file in unsorted order
std::vector<StudentPref*> GroupCreator::readStudentPrefs() {
    std::vector<StudentPref*> students;

    // open the file
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        throw std::runtime_error("Could not open file");
    }

    // read the file line by line
    std::string line;
    // skip the first line with the column headers
    std::getline(file, line);
    while (std::getline(file, line)) {
        students.push_back(new StudentPref(line));
    }

    // close the file
    file.close();

    // validate that number of students is compatible with group sizes specified
    // this algebra uses a sort of greedy algorithm to calculate if teams are possible
    // first make max number of teams using groups of the smallest size
    int n = students.size() / groupMinSize; // using integer floor division
                                            // get the number of students left over
    int r = students.size() % groupMinSize;
    // we know r < groupMinSize, so we need to know if there are enough spots on the
    // teams already made to fit the remaining students
    if (r > n * (groupMaxSize - groupMinSize)) {
        std::cerr << "Error: cannot make teams of size " << 
            groupMinSize << " --> " << groupMaxSize << " with " << students.size() << " students" << std::endl;
        throw std::runtime_error("Invalid group sizes for number of students");
    }

    return students;
}

// write teams to a CSV file
void GroupCreator::writeTeamsToCSV(std::string filename, std::vector<ProjectTeam*> teams) {
    // open the file
    std::ofstream file;
    file.open(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        throw std::runtime_error("Could not open file");
    }

    // write the column headers
    file << "Team,Members" << std::endl;

    // write the teams to the file
    for (int i = 0; i < teams.size(); i++) {
        file << "Team " << i + 1 << ",";
        for (int j = 0; j < teams[i]->members.size(); j++) {
            file << teams[i]->members[j]->username;
            if (j < teams[i]->members.size() - 1) {
                file << ";";
            } 
        }
        file << std::endl;
    }

    // close the file
    file.close();
}

// create teams based on student preferences
std::vector<ProjectTeam*> GroupCreator::preferentialTeams(std::vector<StudentPref*> students) {
    // teams initially stored in a set to keep them sorted by how many members they need
    std::set<ProjectTeam*, Comparator::TeamComp> teams(needMembersComp);

    for (StudentPref* student : students) {
        // if the student is not already on a team
        if (student->team == nullptr) {
            // create team or add to existing team
            auto validTeam = std::find_if(teams.begin(), teams.end(), [student](const ProjectTeam* team) {
                    return !team->isFull() && !team->isRejected(student);
                    });
            ProjectTeam* team;
            if (validTeam != teams.end()) {
                team = *validTeam;
            } else {
                team = new ProjectTeam(groupMinSize, groupMaxSize);
                teams.insert(team);
            }

            // add the student to the team
            team->members.push_back(student);
            student->team = team;

            // add the student's preferences to the team
            for (StudentPref* pref : student->preferredPartners) {
                // if the team is full, stop adding members
                if (team->isFull()) {
                    break;
                }

                // if the preference is not already on a team
                // and the preference is not rejected by another member of the team
                // and the student is not rejected by the preference
                if (pref->team == nullptr && !team->isRejected(pref) && !pref->isRejected(student)) {
                    // add the preference to the team
                    team->members.push_back(pref);
                    pref->team = team;
                }
            }
        } 
    }

    // for the final team, we need to keep the teams sorted while we add students
    // so we will use a vector to store the teams in sorted order
    std::vector<ProjectTeam*> sortedTeams(teams.begin(), teams.end());

    // begin the process of filling the last team
    auto revIt = teams.rbegin();
    while (revIt != teams.rend()) {
        ProjectTeam* team = *revIt;

        // if the first team is full, stop adding members
        if ((*sortedTeams.begin())->members.size() >= groupMinSize) {
            break;
        }

        // if the team is not full, add students to it from the other teams of 4
        for (auto student : team->members) {
            if (!(*sortedTeams.begin())->isRejected(student)) {
                (*sortedTeams.begin())->members.push_back(student);
                student->team = *sortedTeams.begin();
                // use find to get the iterator
                team->members.erase(std::find(team->members.begin(), team->members.end(), student));

                // re-sort the teams
                std::sort(sortedTeams.begin(), sortedTeams.end(), [](ProjectTeam* a, ProjectTeam* b) {
                        return needMembersComp.teamEval(a) < needMembersComp.teamEval(b);
                        });
                break;
            }
        }
        revIt++;
    }

    // convert the set of teams to a vector
    return sortedTeams;
}

// balance the teams by swaping students around
std::vector<ProjectTeam*> GroupCreator::balanceTeams(std::vector<ProjectTeam*> teams, Comparator comp, 
        int maxIterations, double maxDelta) {
    // create set with teams sorted by comparator
    std::set<ProjectTeam*, Comparator::TeamComp> teamSet(teams.begin(), teams.end(), comp);

    // if there is only one team, we are done
    if (teams.size() < 2) {
        return teams;
    }

    // get lowest team
    ProjectTeam* lowest = *teamSet.begin();
    std::sort(lowest->members.begin(), lowest->members.end(), comp.studentComp);

    // iterate through the teams and swap students from the top and bottom
    while (standardDeviation(teams, comp) > maxDelta && maxIterations > 0) {
        for (StudentPref* student : lowest->members) {
            // iterate through the teams from the back and try to swap students
            for (auto it = teamSet.rbegin(); it != teamSet.rend(); it++) {
                if (lowest == *it) {
                    break;
                }
                // get the team with the highest evaluation
                // and sort the members by the student comparator
                ProjectTeam* highest = *it;
                std::sort(highest->members.begin(), highest->members.end(), comp.studentComp);
                // iterare backwards through the highest team to find a student to swap
                for (auto it2 = highest->members.rbegin(); it2 != highest->members.rend(); it2++) {
                    StudentPref* student2 = *it2;
                    // if the student is not rejected by the highest team
                    // and the student2 is not rejected by the lowest team
                    // and student2 is evaluated higher than student
                    // then swap the students
                    if (!highest->isRejected(student) && !lowest->isRejected(student2) && comp.studentComp(student, student2)) {
                        // swap the students
                        student->team = highest;
                        student2->team = lowest;
                        highest->members.push_back(student);
                        lowest->members.push_back(student2);
                        highest->members.erase(std::find(highest->members.begin(), highest->members.end(), student2));
                        lowest->members.erase(std::find(lowest->members.begin(), lowest->members.end(), student));

                        // re-sort the teams
                        std::sort(highest->members.begin(), highest->members.end(), comp.studentComp);
                        std::sort(lowest->members.begin(), lowest->members.end(), comp.studentComp);

                        // re-insert the teams into the set to update the order
                        teamSet.erase(highest);
                        teamSet.erase(lowest);
                        teamSet.insert(highest);
                        teamSet.insert(lowest);
                        goto outer_break;
                    }
                }
            }
        }
outer_break:

        maxIterations--;
    }

    return teams;
}

// calculate the standard deviation of a set of teams
double GroupCreator::standardDeviation(std::vector<ProjectTeam*> teams, Comparator comp) {
    // standard deviation = sqrt(variance) 
    double mean = 0;
    for (ProjectTeam* team : teams) {
        mean += comp.teamEval(team);
    }
    mean /= teams.size();

    double variance = 0;
    for (ProjectTeam* team : teams) {
        variance += pow(comp.teamEval(team) - mean, 2);
    }
    variance /= teams.size();

    return sqrt(variance);
}
