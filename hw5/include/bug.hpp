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
	char symbol;

	// constructor
	Bug(int starveTime, char symbol);

  public:
	// determine if the bug is starving
	virtual bool starved(int timeStep) const = 0;
	// try to move the bug and return the new position
	virtual std::pair<int, int> move(WorldGrid* world) = 0;
	// for easy printing of the bug
	friend std::ostream& operator<<(std::ostream& out, const Bug& bug);
};

#endif
