#include "../include/ants.hpp"
#include "../include/worldGrid.hpp"

// constructor for ants
Ant::Ant(int starveTime, AntType type) : Bug(starveTime, Ant::getAntSymbol(type)), type(type) {}

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

// get tyoe of the bug
BugType Ant::getType() const { return BugType::ANT; }

// get type of the ant
AntType Ant::getAntType() const { return this->type; }

// get symbol from type
char Ant::getAntSymbol(AntType type) {
	switch (type) {
		case AntType::FEMALE: return 'W';
		case AntType::MALE: return 'O';
		case AntType::QUEEN: return 'Q';
		default: throw std::invalid_argument("Invalid AntType");
	}
}

// constructor for queen ants
QueenAnt::QueenAnt(int starveTime, int breedTime) :
	Ant(starveTime, AntType::QUEEN), Breedable(breedTime) {}

// determine if the queen ant is starving or hasnt bred in 3 breed cycles
bool QueenAnt::starved() const {
	std::cout << "Last action: " << lastAction << " Starve time: " << starveTime << std::endl;
	return lastAction >= starveTime || lastBreed >= (3 * breedTime);
}

// determine if the queen ant breeds
bool QueenAnt::breed(WorldGrid* world) {
	// skip if its too early to breed
	if (lastBreed < breedTime) {
		lastBreed++;
		return false;
	}

	// get the adjacencies of the queen ant
	Bug*** adjacencies = world->getAdjacencies(const_cast<QueenAnt*>(this));

	std::cout << "Adjacencies: " << adjacencies << std::endl;

	// loop through the adjacencies for a male ant
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Ant* ant = dynamic_cast<Ant*>(adjacencies[i][j]);

			std::cout << "Ant: " << ant << std::endl;

			// if the adjacent location is a bug and it is a MaleAnt
			if (ant && ant->getAntType() == AntType::MALE) {
				// return true
				return true;
			}
		}
	}

	lastBreed++;
	// return false
	return false;
}
