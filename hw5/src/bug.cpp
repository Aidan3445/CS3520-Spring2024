#include "../include/bug.hpp"

// constructor for bug
Bug::Bug(int starveTime, BugType type) : starveTime(starveTime), breedTime(0), type(type) {}
Bug::Bug(int starveTime, int breedTime, BugType type) :
	starveTime(starveTime), breedTime(breedTime), type(type) {}

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
	out << bug->getCharFromType(bug->type);
	return out;
}
