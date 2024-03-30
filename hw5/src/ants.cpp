#include "../include/ants.hpp"
#include "../include/worldGrid.hpp"

// constructor for ants
Ant::Ant(int starveTime, BugType type) : Bug(starveTime, type) {}
Ant::Ant(int starveTime, int breedTime, BugType type) : Bug(starveTime, breedTime, type) {}

// try to move the ant in a random direction
std::pair<int, int> Ant::moveDirection(WorldGrid* world) {
	// get random direction
	int x = rand() % 3 - 1;
	int y = rand() % 3 - 1;

	// return the direction pair
	return std::make_pair(x, y);
}

// try to move the ant to a new position
bool Ant::tryMove(Bug* bug) {
	// ants cannot eat other bugs
	// only move if the bug is nullptr or the bug is the ant itself
	if (bug == nullptr || bug == this) {
		resetLastAction();
		return true;
	}

	// move fails so increment lastAction for starvation
	this->lastAction++;
	return false;
}

// ants that are not queens cannot breed
bool Ant::breed(const WorldGrid* const world) {
	// increment lastBreed
	return false;
}


QueenAnt::QueenAnt(int starveTime, int breedTime) : Ant(starveTime, breedTime, BugType::QUEENANT) {}

// determine if the queen ant is starving or hasnt bred in 3 breed cycles
bool QueenAnt::starved() const {
	std::cout << "Last action: " << lastAction << " Starve time: " << starveTime << std::endl;
	return lastAction >= starveTime || lastBreed >= (3 * breedTime);
}

// determine if the queen ant breeds
bool QueenAnt::breed(const WorldGrid* const world) {
	std::cout << "lastBreed: " << lastBreed << " breedTime: " << breedTime << std::endl;
	// call base breed to test for starve time
	if (lastBreed < breedTime) {
		std::cout << "early Exit" << std::endl;
		lastBreed++;
		return false;
	}
	std::cout << "continue" << std::endl;

	// get the adjacencies of the queen ant
	Bug*** adjacencies = world->getAdjacencies(this);

	std::cout << "Adjacencies: " << adjacencies << std::endl;

	// loop through the adjacencies for a male ant
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			// if the adjacent location is a bug and it is a MaleAnt
			if (adjacencies[i][j] != nullptr && adjacencies[i][j]->getType() == BugType::MALEANT) {
				resetLastBreed();
				return true;
			}
		}
	}

	lastBreed++;
	// return false
	return false;
}
