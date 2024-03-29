#include "../include/ants.hpp"
#include "../include/worldGrid.hpp"

int main() {
	// set random seed
	srand(time(0));

	// create a WorldGrid object
	WorldGrid world(5, 5);

	// create a new ant
	for (int i = 0; i < 24; i++) {
		Ant* ant = new Ant(3, 'o', AntGender::MALE);
		world + ant;
	}

	std::cout << world;

	char q;
	do {
		++world;
		std::cin >> q;
	} while (q != 'q');
}
