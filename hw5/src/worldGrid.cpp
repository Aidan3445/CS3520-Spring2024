#include "../include/worldGrid.hpp"
#include <deque>

// constructor
WorldGrid::WorldGrid(int width, int height) : width(width), height(height) {
	// initialize the grid
	this->grid = std::vector<std::vector<std::unique_ptr<Bug>>>(width);

	for (int i = 0; i < width; i++) {
		// Create a vector of unique_ptr<Bug>, initialized to nullptr, for each row
		std::vector<std::unique_ptr<Bug>> row(height);
		// Insert the row into the grid
		this->grid[i] = std::move(row);
	}

	// initialize the count history
	this->countHistory = std::deque<std::pair<int, int>>();
}

// destructor - can use default because of smart pointers
WorldGrid::~WorldGrid() = default;

// get the position of a bug
std::pair<int, int> WorldGrid::getBugPosition(const Bug* const bug) const {
	if (bug == nullptr) {
		throw std::invalid_argument("Bug is nullptr");
	}

	// loop through the grid
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			// if the bug is found, return its position
			if (this->grid[i][j] != nullptr && this->grid[i][j].get() == bug) {
				return std::make_pair(i, j);
			}
		}
	}
	// if the bug is not found, throw an exception
	std::cout << bug << std::endl;
	throw std::invalid_argument("Bug not found in grid");
}

// get the 8-neighbors of a bug
Bug*** WorldGrid::getAdjacencies(const Bug* const bug) const {
	//  get the position of the bug
	std::pair<int, int> position = this->getBugPosition(bug);
	int x = position.first;
	int y = position.second;

	// create a 2D array of Bug pointers
	Bug*** adjacencies = new Bug**[3];
	for (int i = 0; i < 3; i++) {
		adjacencies[i] = new Bug*[3];
		for (int j = 0; j < 3; j++) {
			// initialize the array with nullptr
			adjacencies[i][j] = nullptr;
		}
	}

	// loop through the 3x3 grid around the bug
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			int newX = x + i;
			int newY = y + j;

			// set the adjacency
			// if the new pos is itself or nullptr, set to nullptr
			if (newX < 0 || newX >= this->width || newY < 0 || newY >= this->height ||
				this->grid[newX][newY] == nullptr || (newX == x && newY == y)) {
				adjacencies[i + 1][j + 1] = nullptr;
			} else {
				adjacencies[i + 1][j + 1] = this->grid[newX][newY].get();
			}
		}
	}

	// return the 3x3 grid
	return adjacencies;
}

// move a bug on their turn and handle breeding/starving
void WorldGrid::moveBug(int x, int y) {
	// if the bug is nullptr, skip
	if (this->grid[x][y] == nullptr) {
		return;
	}

	// get the bug
	Bug* bug = this->grid[x][y].get();

	// get the direction the bug wants to move
	std::pair<int, int> direction = bug->moveDirection(this);

	// check if bounce needs to be applied
	// if the bug is at an edge and moving out set the direction to 0
	// also double the other direction to reflect the bounce
	if ((x == 0 && direction.first == -1) || (x == this->width - 1 && direction.first == 1)) {
		direction.first = 0;
		direction.second *= 2;
	}
	if ((y == 0 && direction.second == -1) || (y == this->height - 1 && direction.second == 1)) {
		direction.second = 0;
		direction.first *= 2;
	}

	int newX = x + direction.first;
	int newY = y + direction.second;

	// in certain edge cases the bug may be off the grid after the bounce
	// correct this by setting the position to the edge of the grid
	if (newX < 0) {
		newX = 0;
	} else if (newX >= this->width) {
		newX = this->width - 1;
	}
	if (newY < 0) {
		newY = 0;
	} else if (newY >= this->height) {
		newY = this->height - 1;
	}


	// check if the new position has a bug already,
	// we have to check the current grid and the new grid
	// because we are moving the bugs in the same time step
	if (this->grid[newX][newY] == nullptr) {
		// if the new position is empty, move the bug
		bug->tryMove(nullptr);
	} else if (!bug->tryMove(this->grid[newX][newY].get())) {
		// if the bug cannot eat, it will not move
		newX = x;
		newY = y;
		return;
	}

	// set the new position of the bug
	this->grid[newX][newY] = std::move(this->grid[x][y]);

	Bug* newBug = this->grid[newX][newY].get();

	// remove the bug new position
	return;
}

// spawn the child of a bug in a random 16-neighborhood cell
void WorldGrid::spawnBug(const Bug* const parent, std::unique_ptr<Bug> child) {
	// get the position of the parent
	std::pair<int, int> position = this->getBugPosition(parent);
	int x = position.first;
	int y = position.second;

	// get the available positions in the 16-neighborhood
	std::vector<std::pair<int, int>> availablePositions;
	for (int i = -2; i <= 2; i++) {
		for (int j = -2; j <= 2; j++) {
			int checkX = x + i;
			int checkY = y + j;
			if (checkX >= 0 && checkX < this->width && checkY >= 0 && checkY < this->height) {
				if (this->grid[checkX][checkY] == nullptr) {
					availablePositions.push_back(std::make_pair(checkX, checkY));
				}
			}
		}
	}

	// if there are no available positions, return
	if (availablePositions.size() == 0) {
		return;
	}

	// get a random position
	int randomIndex = rand() % availablePositions.size();
	std::pair<int, int> randomPosition = availablePositions[randomIndex];

	// set the position of the child
	this->grid[randomPosition.first][randomPosition.second] = std::move(child);
}

// should the simulation continue
// the simulation has a minimum of 25 time steps
// if over the course of 25 time steps the number of ants and doodlebugs
// has not changed by more than 5, the simulation should stop
bool WorldGrid::continueSimulation() const {
	// if the history is less than 25, return true
	if (this->countHistory.size() < 25) {
		return true;
	}

	// if the history starts and ends with values within 5 of each other, return false
	std::pair<int, int> oldest = this->countHistory.front();
	std::pair<int, int> newest = this->countHistory.back();

	// note that this means will small populations the simulation will stop immediately after 25
	// time steps. this is intended due to the inactive nature of small populations in 100x100 grid
	return !(abs(oldest.first - newest.first) < 5 && abs(oldest.second - newest.second) < 5);
}

// add a bug to the grid
WorldGrid& WorldGrid::operator+(std::unique_ptr<Bug> bug) {
	// get random x and y for the bug
	int x, y;
	do {
		x = rand() % this->width;
		y = rand() % this->height;
	} while (this->grid[x][y] != nullptr);

	// add the bug to the grid
	this->grid[x][y] = std::move(bug);

	// return the grid
	return *this;
}

// remove a bug from the grid
WorldGrid& WorldGrid::operator-(const Bug* const bug) {
	// get the position of the bug
	std::pair<int, int> position = this->getBugPosition(bug);
	int x = position.first;
	int y = position.second;

	// remove the bug from the grid
	this->grid[x][y] = std::move(nullptr);

	// return the grid
	return *this;
}

// increment the time step
WorldGrid& WorldGrid::operator++() {
	// increment the time step and time since last event
	this->time++;

	std::vector<std::pair<Bug*, std::pair<int, int>>> ants;
	std::vector<std::pair<Bug*, std::pair<int, int>>> doodleBugs;

	// loop through the grid
	for (int x = 0; x < this->width; x++) {
		for (int y = 0; y < this->height; y++) {
			// if the bug is nullptr, skip
			if (this->grid[x][y] == nullptr) {
				continue;
			}

			// if the bug is an ant, add it to the ants vector
			if (this->grid[x][y].get()->getType() != BugType::DOODLEBUG) {
				ants.push_back(std::make_pair(this->grid[x][y].get(), std::make_pair(x, y)));
			} else {
				doodleBugs.push_back(std::make_pair(this->grid[x][y].get(), std::make_pair(x, y)));
			}
		}
	}

	// pass in the number of ants and doodlebugs to the temporary history
	this->countHistory.push_back(std::make_pair(ants.size(), doodleBugs.size()));
	if (this->countHistory.size() > 25) {
		this->countHistory.pop_front();
	}

	// shuffle doodlebugs and ants to randomize the order of movement
	std::shuffle(doodleBugs.begin(), doodleBugs.end(), std::default_random_engine(rand()));
	std::shuffle(ants.begin(), ants.end(), std::default_random_engine(rand()));

	// doodleBugs move first
	for (auto doodleBug : doodleBugs) {
		// get the position of the bug
		int x = doodleBug.second.first;
		int y = doodleBug.second.second;

		this->moveBug(x, y);
	}

	// filter out the ants that have been eaten
	ants.erase(std::remove_if(
				   ants.begin(),
				   ants.end(),
				   [this](std::pair<Bug*, std::pair<int, int>> ant) {
					   return this->grid[ant.second.first][ant.second.second].get()->getType() ==
							  BugType::DOODLEBUG;
				   }),
			   ants.end());

	// ants move next
	for (auto ant : ants) {
		// get the position of the bug
		int x = ant.second.first;
		int y = ant.second.second;

		this->moveBug(x, y);
	}

	// loop through the ants and doodleBugs for breeding
	for (auto doodleBug : doodleBugs) {
		// if the doodleBug can breed, add a new doodleBug to the grid
		doodleBug.first->breed(this);
	}

	for (auto ant : ants) {
		// if the cast succeeded and the ant can breed, add a new ant to the grid
		ant.first->breed(this);
	}

	// loop through the ants and doodleBugs for starvation
	for (auto doodleBug : doodleBugs) {
		// get the position of the bug
		int x = doodleBug.second.first;
		int y = doodleBug.second.second;
		Bug* db = doodleBug.first;

		// if the doodleBug is starving, remove it from the grid
		if (db->starved()) {
			*this - db;
		}
	}

	for (auto ant : ants) {
		// get the position of the bug
		int x = ant.second.first;
		int y = ant.second.second;
		Bug* a = ant.first;

		// if the ant is starving, remove it from the grid
		if (a->starved()) {
			*this - a;
		}
	}

	// print the grid
	std::cout << *this;

	// return the grid
	return *this;
}

// for easy printing
std::ostream& operator<<(std::ostream& out, const WorldGrid& grid) {
	// loop through the grid
	// we need to loop through the grid in the opposite order
	// and y is the outer loop because we want to print the grid
	// with the origin (0, 0) at the bottom left
	for (int y = grid.height - 1; y >= 0; y--) {
		for (int x = 0; x < grid.width; x++) {
			// print the symbol of the bug
			if (grid.grid[x][y] == nullptr) {
				out << "· ";
			} else {
				out << grid.grid[x][y].get() << ' ';
			}
		}
		out << std::endl;
	}
	out << "Time: " << grid.time << std::endl;

	// return the output stream
	return out;
}
