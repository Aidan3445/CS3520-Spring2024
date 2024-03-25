#include "../include/worldGrid.hpp"

// constructor
WorldGrid::WorldGrid(int width, int height) : width(width), height(height) {
	// create the grid
	this->grid = new Bug**[width];
	for (int i = 0; i < width; i++) {
		this->grid[i] = new Bug*[height];
		for (int j = 0; j < height; j++) {
			// initialize the grid with nullptr
			this->grid[i][j] = nullptr;
		}
	}
}

// destructor
WorldGrid::~WorldGrid() {
	// delete the grid
	for (int i = 0; i < this->width; i++) {
		delete[] this->grid[i];
	}
	delete[] this->grid;
}

// get the position of a bug
std::pair<int, int> WorldGrid::getBugPosition(Bug* bug) const {
	// loop through the grid
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			// if the bug is found, return its position
			if (this->grid[i][j] == bug) {
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

			// if the position is the bug itself, place nullptr
			if (i == 0 && j == 0) {
				adjacencies[newX][newY] = nullptr;
				continue;
			}

			// check if bounce needs to be applied
			if (newX < 0 || newX >= this->width) {
				// a bounce essentilly undoes the move in the x direction
				// and then applies the move again in the y direction
				newX -= i;
				newY += j;
			}
			if (newY < 0 || newY >= this->height) {
				// a bounce essentilly undoes the move in the y direction
				// and then applies the move again in the x direction
				newY += i;
				newX -= j;
			}
			// note that because of the bounce:
			// - the position is guaranteed to be within the grid
			// - there may be duplicates in the 3x3 neighborhood


			// set the adjacency
			adjacencies[i + 1][j + 1] = this->grid[x + i][y + j];
		}
	}

	// return the 3x3 grid
	return adjacencies;
}

// move a bug on their turn and handle breeding/starving
void WorldGrid::moveBug(int x, int y) {
	// get the bug
	Bug* bug = this->grid[x][y];

	// if the bug is nullptr, skip
	if (bug == nullptr) {
		return;
	}

	// get the direction the bug wants to move
	std::pair<int, int> direction = bug->move(this);

	int newX = x + direction.first;
	int newY = y + direction.second;

	// check if bounce needs to be applied
	if (newX < 0 || newX >= this->width) {
		// a bounce essentilly undoes the move in the x direction
		// and then applies the move again in the y direction
		newX -= direction.first;
		newY += direction.second;
	}
	if (newY < 0 || newY >= this->height) {
		// a bounce essentilly undoes the move in the y direction
		// and then applies the move again in the x direction
		newY += direction.first;
		newX -= direction.second;
	}

	// if the new position is not empty, skip
	if (this->grid[newX][newY] != nullptr) {
		return;
	}

    // otherwise, update the bug's position
	this->grid[x][y] = nullptr;
	this->grid[newX][newY] = bug;
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
	this->grid[x][y] = bug;

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

	// loop through the grid
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			// move the bug
			this->moveBug(i, j);
		}
	}

	// return the grid
	return *this;
}

// for easy printing
std::ostream& operator<<(std::ostream& out, const WorldGrid& grid) {
	// loop through the grid
	for (int i = 0; i < grid.width; i++) {
		for (int j = 0; j < grid.height; j++) {
			// print the symbol of the bug
			if (grid.grid[i][j] == nullptr) {
				out << ' ';
			} else {
				out << grid.grid[i][j];
			}
		}
		out << std::endl;
	}

	// return the output stream
	return out;
}
