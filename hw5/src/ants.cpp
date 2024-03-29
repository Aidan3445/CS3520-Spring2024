#include "../include/ants.hpp"
#include "../include/worldGrid.hpp"

// constructor for ants
Ant::Ant(int starveTime, char symbol, AntGender gender) : Bug(starveTime, symbol), gender(gender) {}

// determine if the ant is starving
bool Ant::starved() const { return lastAction >= starveTime; }

// try to move the ant in a random direction
std::pair<int, int> Ant::move(WorldGrid* world) {
	// get random direction
	int x = rand() % 3 - 1;
	int y = rand() % 3 - 1;

	// return the direction pair
	return std::make_pair(x, y);
}

// try to move the ant to a new position
bool Ant::tryMove(Bug* bug) {
	// ants cannot eat other bugs
	// only move if the bug is nullptr
	if (bug == nullptr) {
		resetLastAction();
		return true;
	}

	// move fails so increment lastAction for starvation
	this->lastAction++;
	return false;
}

// get gender of the ant
AntGender Ant::getGender() const { return this->gender; }

// constructor for queen ants
QueenAnt::QueenAnt(int starveTime, int breedTime, char symbol) :
	Ant(starveTime, symbol, AntGender::FEMALE), Breedable(breedTime) {}

// determine if the queen ant is starving or hasnt bred in 3 breed cycles
bool QueenAnt::starved() const { return lastAction >= starveTime || lastBreed >= (3 * breedTime); }

// determine if the queen ant breeds
bool QueenAnt::breed(WorldGrid* world) const {
	// get the adjacencies of the queen ant
	Bug*** adjacencies = world->getAdjacencies(const_cast<QueenAnt*>(this));

	// loop through the adjacencies for a male ant
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Bug* bug = adjacencies[i][j];
			// if the adjacent location is a bug and it is a MaleAnt
			if (bug != nullptr && dynamic_cast<Ant*>(bug) != nullptr &&
				dynamic_cast<Ant*>(bug)->getGender() == AntGender::MALE) {
				// return true
				return true;
			}
		}
	}

	// return false
	return false;
}
