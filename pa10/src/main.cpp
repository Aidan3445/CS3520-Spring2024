#include "../include/projectTeam.hpp"

int main() {
	// let user make them a team
	Student you;
	ProjectTeam team1;

	std::cin >> you;

	std::cout << std::endl << "You are:" << std::endl << you << std::endl;

	std::cin >> team1;
	team1 = team1 + you;
	std::cout << std::endl << "Your team is:" << std::endl << team1 << std::endl;

	// create a team
	ProjectTeam team2 = ProjectTeam("Team 2", 50, "Project 1");

	// create some students
	Student student1 = Student("John Doe", "jd@neu.edu", "Freshman");
	Student student2 = Student("Sarah Liu", "sl@neu.edu", "Sophomore");
	Student student3 = Student("Mike Smith", "ms@neu.edu", "Junior");
	Student student4 = Student("Emily Johnson", "ej@neu.edu", "Senior");
	Student student5 = Student("Sofie Wendell", "sw@neu.edu", "Senior");
	Student student6 = Student("Mikaela Johnson", "mj@neu.edu", "Freshman");
	Student student7 = Student("Andrew Meyer", "am@neu.edu", "Sophomore");
	Student student8 = Student("Juan Diaz", "jd1@neu.edu", "Junior");
	Student student9 = Student("Sofia Diaz", "sd@neu.edu", "Junior");
	Student student10 = Student("Harry Jones", "hj@neu.edu", "Senior");
	Student student11 = Student("Hannah Smith", "hs@neu.edu", "Freshman");
	Student student12 = Student("Mia Davis", "md@neu.edu", "Sophomore");
	Student student13 = Student("Liam Schafer", "ls@neu.edu", "Junior");
	Student student14 = Student("Emma Baker", "eb@neu.edu", "Senior");
	Student student15 = Student("Olivia Frankel", "of@neu.edu", "Senior");

	// add students to the team
	team1 = team1 + student1 + student2;
	team2 = team2 + student3 + student4;
	std::cout << "two students added to team1 and two students added to team2" << std::endl;
	std::cout << team1 << std::endl;
	std::cout << team2 << std::endl;

	// add a team to another team
	std::cout << "teams added together" << std::endl;
	team1 = team1 + team2;
	std::cout << team1 << std::endl;

	// add too many students to the team
	ProjectTeam bigTeam = ProjectTeam("Big Team", 110, "Big Project");
	bigTeam = bigTeam + student5 + student6 + student7 + student8 + student9 + student10 +
			  student11 + student12 + student13 + student14 + student15;
	std::cout << "too many students added to bigTeam" << std::endl;
	std::cout << bigTeam << std::endl;

	// split the team into two teams
	std::cout << "bigTeam split into three teams" << std::endl;
	std::vector<ProjectTeam*> newTeams = bigTeam / 3;
	ProjectTeam team3 = *newTeams[0];
	ProjectTeam team4 = *newTeams[1];
	ProjectTeam team5 = *newTeams[2];
	std::cout << team3 << std::endl;
	std::cout << team4 << std::endl;
	std::cout << team5 << std::endl;

	// remove some students from the team
	std::cout << "two students removed from team5" << std::endl;
	team5 = team5 - 2;
	std::cout << team5 << std::endl;

	try {
		// remove too many students from the team
		std::cout << "try to remove two more, this should error" << std::endl;
		team5 = team5 - 2;
		std::cout << team5 << std::endl;
	} catch (std::invalid_argument& e) {
		std::cout << "\033[31mERROR: " << e.what() << "\033[0m" << std::endl;
	}
}
