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
void Ant::breed(WorldGrid* const world) { return; }


QueenAnt::QueenAnt(int starveTime,
				   int breedTime,
				   double spawnFemaleChance,
				   double femaleIsQueenChance,
				   double queenIsCataglyphisChance) :
	Ant(starveTime, breedTime, BugType::QUEENANT),
	spawnFemaleChance(spawnFemaleChance), femaleIsQueenChance(femaleIsQueenChance),
	queenIsCataglyphisChance(queenIsCataglyphisChance) {}

// determine if the queen ant is starving or hasnt bred in 3 breed cycles
bool QueenAnt::starved() const { return lastAction >= starveTime || lastBreed >= (3 * breedTime); }

// determine if the queen ant breeds
void QueenAnt::breed(WorldGrid* const world) {
	//  call base breed to test for starve time
	if (lastBreed < breedTime) {
		lastBreed++;
		return;
	}

	// get the adjacencies of the queen ant
	Bug*** adjacencies = world->getAdjacencies(this);

	// loop through the adjacencies for a male ant
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			// if the adjacent location is a bug and it is a MaleAnt
			if (adjacencies[i][j] != nullptr && adjacencies[i][j]->getType() == BugType::MALEANT) {
				// spawn 10 ants
				for (int i = 0; i < 10; i++) {
					world->spawnBug(this, spawnAnt());
				}
				resetLastBreed();
				return;
			}
		}
	}

	lastBreed++;
	return;
}

// spawn an ant according to the chances specified in the constructor
std::unique_ptr<Ant> QueenAnt::spawnAnt() {
	int spawn = rand() % 100000 / 1000;
	// is the ant female?
	if (spawn < spawnFemaleChance * 100) {
		spawn = rand() % 100000 / 1000;
		// is the ant a queen
		if (spawn < femaleIsQueenChance * 100) {
			spawn = rand() % 100000 / 1000;
			// is the queen a Cataglyphis
			if (spawn < queenIsCataglyphisChance * 100) {
				return std::make_unique<CataglyphisAnt>(this->starveTime,
														this->breedTime,
														this->spawnFemaleChance,
														this->femaleIsQueenChance);
			}
			return std::make_unique<QueenAnt>(this->starveTime,
											  this->breedTime,
											  this->spawnFemaleChance,
											  this->femaleIsQueenChance,
											  this->queenIsCataglyphisChance);
		}
		return std::make_unique<Ant>(this->starveTime, this->breedTime, BugType::FEMALEANT);
	}
	return std::make_unique<Ant>(this->starveTime, this->breedTime, BugType::MALEANT);
}

// cataglyphis ant constructor
// cataglyphis ants that spawn queens are always also cataglyphis ants
CataglyphisAnt::CataglyphisAnt(int starveTime,
							   int breedTime,
							   double spawnFemaleChance,
							   double femaleIsQueenChance) :
	QueenAnt(starveTime, breedTime, spawnFemaleChance, femaleIsQueenChance, 1) {}

// determine if the Cataglyphis breeds
// Cataglyphis ants can always breed if it has been a full breed cycle
void CataglyphisAnt::breed(WorldGrid* const world) {
	if (lastBreed < breedTime) {
		lastBreed++;
		return;
	}

	// spawn 10 ants
	for (int i = 0; i < 10; i++) {
		world->spawnBug(this, spawnAnt());
	}

	// reset last breed
	resetLastBreed();
	return;
}
