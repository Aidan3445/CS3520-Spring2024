#ifndef BUG_HPP
#define BUG_HPP

// forward declaration
#include <iostream>
#include <utility>
class WorldGrid;

// bug class for ants and doodlebugs
class Bug {
  protected:
	// number of time steps before a bug starves
	const int starveTime;
	// the time step when the bug last moved or ate
	int lastAction;
	// symbol to represent the bug in the grid
	const char symbol;

	// constructor
	Bug(int starveTime, char symbol);

  public:
	// determine if the bug is starving
	virtual bool starved() const = 0;
	// try to move the bug and return the new position
	virtual std::pair<int, int> move(WorldGrid* world) = 0;
	// try to move the bug to a new position
	virtual bool tryMove(Bug* bug) = 0;
	// reset the last action of the bug
	void resetLastAction();
	// for easy printing of the bug
	friend std::ostream& operator<<(std::ostream& out, const Bug* bug);
};

// breedable bug class for doodlebugs and queen ants
class Breedable {
  protected:
	// number of time steps before a bug breeds
	const int breedTime;
	// the time step when the bug last bred
	int lastBreed;

	// constructor
	Breedable(int breedTime);

  public:
	// determine if the bug breeds
	virtual bool breed(WorldGrid* world) const = 0;

	// bugs can access the lastBreed variable
	// friend class Bug;
};

#endif
