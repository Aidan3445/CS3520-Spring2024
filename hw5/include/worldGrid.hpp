#ifndef WORLDGRID_HPP
#define WORLDGRID_HPP
#include "../include/bug.hpp"
#include <algorithm>
#include <deque>
#include <memory>
#include <random>
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
	std::deque<std::pair<int, int>> countHistory;

	// get the position of a bug
	std::pair<int, int> getBugPosition(const Bug* const bug) const;

  public:
	// constructor and destructor
	WorldGrid(int width, int height);
	~WorldGrid();
	// get the 8-neighbors of a bug
	Bug*** getAdjacencies(const Bug* const bug) const;
	// move a bug using its move function
	void moveBug(int x, int y);
	// spanw the child of a bug in a random 16-neighborhood cell
	void spawnBug(const Bug* const parent, std::unique_ptr<Bug> child);
	// should the simulation continue
	bool continueSimulation() const;

	// add a new bug to the grid in a random position
	WorldGrid& operator+(std::unique_ptr<Bug> bug);
	// remove a bug from the grid
	WorldGrid& operator-(const Bug* const bug);
	// increment the time step
	WorldGrid& operator++();

	// for easy printing
	friend std::ostream& operator<<(std::ostream& out, const WorldGrid& grid);
};

#endif
