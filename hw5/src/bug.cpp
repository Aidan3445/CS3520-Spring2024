#include "../include/bug.hpp"
#include "../include/doodleBug.hpp"

int genID() { return rand() % 4000 + 1000; }

// constructor for bug
Bug::Bug(int starveTime, BugType type) :
	starveTime(starveTime), breedTime(0), type(type), id(genID()) {}
Bug::Bug(int starveTime, int breedTime, BugType type) :
	starveTime(starveTime), breedTime(breedTime), type(type), id(genID()) {}

// determine if the ant is starving
bool Bug::starved() const { return lastAction >= starveTime; }

// get the type of the bug
BugType Bug::getType() const { return type; }

// reset the last action of the bug
void Bug::resetLastAction() { lastAction = 0; }

// reset the last breed of the bug
void Bug::resetLastBreed() { lastBreed = 0; }

// get the char for bug type
char Bug::getCharFromType(BugType bugType) {
	switch (bugType) {
		case BugType::MALEANT: return 'O';
		case BugType::FEMALEANT: return 'W';
		case BugType::QUEENANT: return 'Q';
		case BugType::DOODLEBUG: return 'X';
		default: throw std::invalid_argument("Invalid bug type");
	}
}

// overload the << operator for easy printing of the bug
std::ostream& operator<<(std::ostream& out, const Bug* bug) {
	// set color based on bug type
	switch (bug->type) {
		case BugType::MALEANT: out << "\033[0;32m"; break;
		case BugType::FEMALEANT: out << "\033[0;33m"; break;
		case BugType::QUEENANT: out << "\033[0;36m"; break;
		case BugType::DOODLEBUG: out << "\033[0;31m"; break;
		default: break;
	}

	out << Bug::getCharFromType(bug->type) << "\033[0m";
	return out;
}
