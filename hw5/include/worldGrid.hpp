#ifndef WORLDGRID_HPP
#define WORLDGRID_HPP
#include "bug.hpp"
#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

class WorldGrid {
  private:
	// width and height of the grid
	const int width;
	const int height;
	// 2D vector of Bug pointers
	std::vector<std::vector<std::unique_ptr<Bug>>> grid;
	// time step counter
	int time = 0;

	// get the position of a bug
	std::pair<int, int> getBugPosition(Bug* bug) const;

  public:
	// constructor and destructor
	WorldGrid(int width, int height);
	~WorldGrid();
	// get the 8-neighbors of a bug
	Bug*** getAdjacencies(Bug* bug) const;
	// move a bug using its move function
	std::pair<int, int> moveBug(int x, int y);

	// spawn/add a bug to the grid
	WorldGrid& operator+(Bug* bug);
	// remove a bug from the grid
	WorldGrid& operator-(Bug* bug);
	// increment the time step
	WorldGrid& operator++();

	// for easy printing
	friend std::ostream& operator<<(std::ostream& out, const WorldGrid& grid);
};

#endif
