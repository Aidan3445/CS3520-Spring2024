#include "../include/bug.hpp"

// constructor for bug
Bug::Bug(int starveTime, char symbol) : starveTime(starveTime), symbol(symbol) {}

// overload the << operator for easy printing of the bug
std::ostream& operator<<(std::ostream& out, const Bug& bug) {
	out << bug.symbol;
	return out;
}

// constructor for breedable bug
Breedable::Breedable(int breedTime) : breedTime(breedTime) {}
