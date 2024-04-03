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
	int x, y;
	do {
		// initialize random previous direction that is not 0, 0
		x = rand() % 2 - 1;
		y = rand() % 2 - 1;
	} while (x == 0 && y == 0);

	// initialize random previous direction
	this->previousDirection = std::make_pair(x, y);
}

// determine if the doodlebug can breed
void DoodleBug::breed(WorldGrid* const world) {
	// skip if its too early to breed
	if (lastBreed < breedTime) {
		lastBreed++;
		return;
	}

	// spawn a new doodlebug
	world->spawnBug(this, std::make_unique<DoodleBug>(starveTime, breedTime));

	// reset last breed
	this->resetLastBreed();
}

// try to move the doodlebug
std::pair<int, int> DoodleBug::moveDirection(WorldGrid* world) {
	// get adjacent cells
	Bug*** adjacent = world->getAdjacencies(this);

	// check for ant to eat
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (adjacent[i][j] != nullptr) {
				if (adjacent[i][j]->getType() != BugType::DOODLEBUG) {
					//  eat the ant
					*world - adjacent[i][j];
					// reset last action after eating
					this->resetLastAction();
					// update previous direction
					this->previousDirection = std::make_pair(i - 1, j - 1);
					return std::make_pair(i - 1, j - 1);
				}
			}
		}
	}

	// no eating, increment last action
	this->lastAction++;

	// no ant found move in next clockwise direction
	if (this->previousDirection == downRight) {
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
	} else if (this->previousDirection == upLeft) {
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
