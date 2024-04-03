#include "../include/ants.hpp"
#include "../include/doodleBug.hpp"
#include "../include/worldGrid.hpp"
#include <cmath>
#include <thread>

int main() {
	// set random seed
	srand(time(0));

	// initialize variables
	int doodleBugs, ants, queenAnts;
	double initialAntChance = 0.5, antSpawnGenderChance = 0.6, antSpawnQueenChance = 0.005,
		   antSpawnCataglyphisChance = 0.001;

	// get user input for the number of bugs
	std::cout << "Enter the number of doodlebugs: ";
	std::cin >> doodleBugs;
	std::cout << "Enter the number of queen ants: ";
	std::cin >> queenAnts;
	std::cout << "Enter the number of additional ants: ";
	std::cin >> ants;

	std::cout << "Default ant spawn rates: " << std::endl;
	std::cout << " - Initial ant gender chance (non-queen): " << initialAntChance * 100
			  << "% female" << std::endl;
	std::cout << " - Ant spawn gender chance: " << antSpawnGenderChance * 100 << "% female"
			  << std::endl;
	std::cout << " - Female ant chance to be a queen: " << antSpawnQueenChance << std::endl;
	std::cout << " - Queen ant chance to be a Cataglyphis: " << antSpawnCataglyphisChance
			  << std::endl;

	// allow user to opt-in to setting the ant spawn rates for ants in the simulation
	char setAntGenderOdds;
	do {
		std::cout << "Would you like to set custom ant gender odds? (y/n): ";
		std::cin >> setAntGenderOdds;
	} while (setAntGenderOdds != 'y' && setAntGenderOdds != 'n');

	if (setAntGenderOdds == 'y') {
		do {
			std::cout << "Enter the initial non-queen ant gender chance (0.0 - 1.0): ";
			std::cin >> initialAntChance;
		} while (initialAntChance < 0.0 || initialAntChance > 1.0);

		do {
			std::cout << "Enter the ant spawn gender chance (0.0 - 1.0): ";
			std::cin >> antSpawnGenderChance;
		} while (antSpawnGenderChance < 0.0 || antSpawnGenderChance > 1.0);

		do {
			std::cout << "Enter the chance for a female ant to become a queen (0.0 - 1.0): ";
			std::cin >> antSpawnQueenChance;
		} while (antSpawnQueenChance < 0.0 || antSpawnQueenChance > 1.0);

		do {
			std::cout << "Enter the chance for a queen ant to become a Cataglyphis (0.0 - 1.0): ";
			std::cin >> antSpawnCataglyphisChance;
		} while (antSpawnCataglyphisChance < 0.0 || antSpawnCataglyphisChance > 1.0);
	}

	// establish a default size of 100 but increase if the number of bugs exceeds the default size
	int size = 100;
	if (doodleBugs + ants + queenAnts > size * size) {
		size = std::ceil(std::sqrt(doodleBugs + ants + queenAnts) * 2);
	}

	// create a WorldGrid object
	WorldGrid world(size, size);

	// add doodlebugs to the world
	for (int i = 0; i < doodleBugs; i++) {
		world + std::make_unique<DoodleBug>(20, 10);
	}

	// add queen ants to the world
	for (int i = 0; i < queenAnts; i++) {
		world + std::make_unique<QueenAnt>(
					5, 30, antSpawnGenderChance, antSpawnQueenChance, antSpawnCataglyphisChance);
	}

	// add ants to the world
	for (int i = 0; i < ants; i++) {
		BugType type;
		if (rand() % 100 < initialAntChance * 100) {
			type = BugType::FEMALEANT;
		} else {
			type = BugType::MALEANT;
		}
		world + std::make_unique<Ant>(5, type);
	}

	// wait for user to intialize and start the simulation
	std::cout << world;
	char c;
	std::cout << "Enter a key to begin the simulation: ";
	std::cin >> c;
	while (world.continueSimulation()) {
		++world;
		// sleep for .5 seconds
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	std::cout << "Simulation over" << std::endl;
}
