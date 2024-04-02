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
DoodleBug::DoodleBug(int starveTime, int breedTime) :
	Bug(starveTime, breedTime, BugType::DOODLEBUG) {
	int x = rand() % 2 - 1;
	int y = rand() % 2 - 1;
	// initialize random previous direction
	this->previousDirection = std::make_pair(x, y);
}

// determine if the doodlebug can breed
bool DoodleBug::breed(const WorldGrid* const world) {
	// skip if its too early to breed
	if (lastBreed < breedTime) {
		lastBreed++;
		return false;
	}

	// reset last breed
	this->resetLastBreed();

	return true;
}

// try to move the doodlebug
std::pair<int, int> DoodleBug::moveDirection(WorldGrid* world) {
	// std::cout << "DoodleBug moveDirection" << std::endl;

	// get adjacent cells
	Bug*** adjacent = world->getAdjacencies(this);

	// check for ant to eat
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (adjacent[i][j] != nullptr) {
				if (adjacent[i][j]->getType() != BugType::DOODLEBUG) {
					// std::cout << "DoodleBug moveDirection: found ant" << adjacent[i][j]
					//		  << std::endl;
					//  eat the ant
					*world - adjacent[i][j];
					// reset last action after eating
					this->resetLastAction();
					return std::make_pair(i - 1, j - 1);
				}
			}
		}
	}

	// no eating, increment last action
	this->lastAction++;

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
	if (bug == nullptr || bug->getType() != BugType::DOODLEBUG) {
		return true;
	}

	return false;
}
