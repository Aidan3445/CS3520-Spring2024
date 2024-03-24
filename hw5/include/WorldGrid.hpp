#ifndef WORLDGRID_HPP
#define WORLDGRID_HPP
#include "Bug.hpp"

class WorldGrid {
  private:
	// width and height of the grid
	const int width;
	const int height;
	// 2D array of Bug pointers
	Bug*** grid;
	// time step counter
	int time;

  public:
	// constructor and destructor
	WorldGrid(int width, int height);
	~WorldGrid();
	// get the 8-neighbors of a bug
	Bug*** getAdjacencies(Bug* bug) const;
	// move a bug using its move function
	void moveBug(Bug* bug);

	// spawn/add a bug to the grid
	WorldGrid& operator+(const Bug* bug);
	// remove a bug from the grid
	WorldGrid& operator-(const Bug* bug);
	// increment the time step
	WorldGrid& operator++();
};

#endif
