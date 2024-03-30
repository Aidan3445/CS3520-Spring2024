#include "../include/worldGrid.hpp"

int main() {
	// set random seed
	srand(time(0));

	// create a WorldGrid object
	WorldGrid world(5, 5);

	// create a new ant
	for (int i = 0; i < 5; i++) {
		world + std::make_unique<Ant>(5, AntType::MALE);
	}

	world + std::make_unique<QueenAnt>(5, 5);

	std::cout << world;

	char q;
	do {
		++world;
		std::cin >> q;
	} while (q != 'q');
}
