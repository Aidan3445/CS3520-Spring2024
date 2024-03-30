#include "../include/doodleBug.hpp"
#include "../include/worldGrid.hpp"

#define up std::make_pair(0, 1)
#define upRight std::make_pair(1, 1)
#define right std::make_pair(1, 0)
#define downRight std::make_pair(1, -1)
#define down std::make_pair(0, -1)
#define downLeft std::make_pair(-1, -1)
#define left std::make_pair(-1, 0)
#define upLeft std::make_pair(-1, 1)

// constructor
DoodleBug::DoodleBug(int starveTime, int breedTime) : Bug(starveTime, 'X'), Breedable(breedTime) {
	this->previousDirection = std::make_pair(-1, 1);
}

// determine if the doodlebug can breed
bool DoodleBug::breed(WorldGrid* world) {
	// skip if its too early to breed
	if (lastBreed < breedTime) {
		lastBreed++;
		return false;
	}

	return true;
}

// try to move the doodlebug
std::pair<int, int> DoodleBug::moveDirection(WorldGrid* world) {
	// get adjacent cells
	Bug*** adjacent = world->getAdjacencies(this);

	// check for ant to eat
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (adjacent[i][j] != nullptr) {
				Ant* ant = dynamic_cast<Ant*>(adjacent[i][j]);
				if (ant) {
					return std::make_pair(i, j);
				}
			}
		}
	}

	// no ant found move in next clockwise direction
	if (this->previousDirection == upLeft) {
		this->previousDirection = up;
		return up;
	} else if (this->previousDirection == up) {
		this->previousDirection = upRight;
		return upRight;
	} else if (this->previousDirection == upRight) {
		this->previousDirection = right;
		return right;
	} else if (this->previousDirection == right) {
		this->previousDirection = downRight;
		return downRight;
	} else if (this->previousDirection == downRight) {
		this->previousDirection = down;
		return down;
	} else if (this->previousDirection == down) {
		this->previousDirection = downLeft;
		return downLeft;
	} else if (this->previousDirection == downLeft) {
		this->previousDirection = left;
		return left;
	} else if (this->previousDirection == left) {
		this->previousDirection = upLeft;
		return upLeft;
	}

	// or stay in the same place
	return std::make_pair(0, 0);
}

// try to move the doodlebug
bool DoodleBug::tryMove(Bug* bug) {
	// doodleBugs only can't eat other doodleBugs
	if (bug == nullptr || dynamic_cast<Ant*>(bug)) {
		resetLastAction();
		return true;
	}

	// move fails so increment lastAction for starvation
	this->lastAction++;
	return false;
}

// get the type of the bug
BugType DoodleBug::getType() const { return BugType::DOODLEBUG; }
