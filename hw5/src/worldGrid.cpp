#include "../include/worldGrid.hpp"

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
}

// destructor - can use default because of smart pointers
WorldGrid::~WorldGrid() = default;

// get the position of a bug
std::pair<int, int> WorldGrid::getBugPosition(Bug* bug) const {
	// loop through the grid
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			// if the bug is found, return its position
			if (this->grid[i][j].get() == bug) {
				return std::make_pair(i, j);
			}
		}
	}
	// if the bug is not found, return (-1, -1)
	return std::make_pair(-1, -1);
}

// get the 8-neighbors of a bug
Bug*** WorldGrid::getAdjacencies(Bug* bug) const {
	// get the position of the bug
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

			// check if bounce needs to be applied
			// if the bug is at an edge and moving out set the direction to 0
			// also double the other direction to reflect the bounce
			if ((x == 0 && i == -1) || (x == this->width - 1 && i == 1)) {
				i = 0;
				j *= 2;
			}
			if ((y == 0 && j == -1) || (y == this->height - 1 && j == 1)) {
				j = 0;
				i *= 2;
			}
			// note that because of the bounce:
			// - the position is guaranteed to be within the grid
			// - there may be duplicates in the 3x3 neighborhood

			// set the adjacency
			// if the new pos is itself or nullptr, set to nullptr
			if (this->grid[newX][newY] == nullptr || (newX == x && newY == y)) {
				adjacencies[i + 1][j + 1] = nullptr;
			} else {
				// set the adjacency to the bug at the new position
				adjacencies[i + 1][j + 1] = this->grid[newX][newY].get();
			}
		}
	}

	// return the 3x3 grid
	return adjacencies;
}

// move a bug on their turn and handle breeding/starving
std::pair<int, int> WorldGrid::moveBug(int x, int y) {
	// get the bug
	Bug* bug = this->grid[x][y].get();

	// if the bug is nullptr, skip
	if (bug == nullptr) {
		return std::make_pair(x, y);
	}


	// get the direction the bug wants to move
	std::pair<int, int> direction = bug->move(this);
	std::cout << "Bug " << this->grid[x][y].get() << " at (" << x << ", " << y
			  << ") moving in direction (" << direction.first << ", " << direction.second << ")"
			  << std::endl;


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


	std::cout << "Bug " << this->grid[x][y].get() << " at (" << x << ", " << y << ") moving to ("
			  << newX << ", " << newY << ")" << std::endl;

	// remove the bug new position
	return std::make_pair(newX, newY);
}

// add a bug to the grid
WorldGrid& WorldGrid::operator+(Bug* bug) {
	// get random x and y for the bug
	int x, y;
	do {
		x = rand() % this->width;
		y = rand() % this->height;
	} while (this->grid[x][y] != nullptr);

	// add the bug to the grid
	this->grid[x][y] = std::unique_ptr<Bug>(bug);

	std::cout << "Bug added at (" << x << ", " << y << ")" << std::endl;

	// return the grid
	return *this;
}

// remove a bug from the grid
WorldGrid& WorldGrid::operator-(Bug* bug) {
	// get the position of the bug
	std::pair<int, int> position = this->getBugPosition(bug);
	int x = position.first;
	int y = position.second;

	// remove the bug from the grid
	this->grid[x][y] = nullptr;

	// return the grid
	return *this;
}

// increment the time step
WorldGrid& WorldGrid::operator++() {
	// increment the time step
	this->time++;

	std::vector<Bug*> movedBugs;

	// loop through the grid
	for (int x = 0; x < this->width; x++) {
		for (int y = 0; y < this->height; y++) {
			// if the bug is nullptr or in the movedBugs vector, skip
			if (this->grid[x][y] == nullptr ||
				std::find(movedBugs.begin(), movedBugs.end(), this->grid[x][y].get()) !=
					movedBugs.end()) {
				continue;
			}

			// move the bug
			std::pair<int, int> newPosition = this->moveBug(x, y);
			int newX = newPosition.first;
			int newY = newPosition.second;

			// check if the new position has a bug already,
			// we have to check the current grid and the new grid
			// because we are moving the bugs in the same time step
			if (!this->grid[x][y].get()->tryMove(this->grid[newX][newY].get())) {
				// if the bug cannot eat, it will not move
				newX = x;
				newY = y;
				std::cout << "Bug " << this->grid[x][y].get() << " at (" << x << ", " << y
						  << ") failed to move" << std::endl;
			}

			// set the new position of the bug
			this->grid[newX][newY] = std::move(this->grid[x][y]);

			// add the bug to the movedBugs vector
			movedBugs.push_back(std::move(this->grid[newX][newY].get()));
		}
	}

	// loop through the grid and check for starvation
	for (int x = 0; x < this->width; x++) {
		for (int y = 0; y < this->height; y++) {
			// if the bug is nullptr, skip
			if (this->grid[x][y] == nullptr) {
				continue;
			}

			// if the bug is starving, remove it
			if (this->grid[x][y].get()->starved()) {
				std::cout << "Bug " << this->grid[x][y].get() << " at (" << x << ", " << y
						  << ") starved" << std::endl;
				this->grid[x][y] = nullptr;
			}
		}
	}

	// print the grid
	std::cout << *this << std::endl;

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
				out << " * ";
			} else {
				out << ' ' << grid.grid[x][y].get() << ' ';
			}
		}
		out << std::endl;
	}

	// return the output stream
	return out;
}
