#include "../include/bug.hpp"

// constructor for bug
Bug::Bug(int starveTime, char symbol) : starveTime(starveTime), symbol(symbol) {}

// determine if the ant is starving
bool Bug::starved() const { return lastAction >= starveTime; }
// reset the last action of the bug
void Bug::resetLastAction() { lastAction = 0; }

// overload the << operator for easy printing of the bug
std::ostream& operator<<(std::ostream& out, const Bug* bug) {
	out << bug->symbol;
	return out;
}

// constructor for breedable bug
Breedable::Breedable(int breedTime) : breedTime(breedTime) {}
