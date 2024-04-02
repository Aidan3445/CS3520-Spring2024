#ifndef BUG_HPP
#define BUG_HPP

#include <iostream>
#include <utility>

// forward declaration
class WorldGrid;

enum BugType { MALEANT, FEMALEANT, QUEENANT, DOODLEBUG };

// bug class for ants and doodlebugs
class Bug {
  protected:
	// number of time steps before a bug starves
	const unsigned int starveTime;
	// the time step when the bug last moved or ate
	unsigned int lastAction;
	// number of time steps before a bug breeds
	const unsigned int breedTime;
	// the time step when the bug last bred
	unsigned int lastBreed;
	// the type of the bug
	const BugType type;


	// constructor
	Bug(int starveTime, BugType type);
	Bug(int starveTime, int breedTime, BugType type);

  public:
	const int id;
	// determine if the bug is starving
	virtual bool starved() const;
	// determine if the bug breeds
	virtual bool breed(const WorldGrid* const world) = 0;
	// get direction to move the bug
	virtual std::pair<int, int> moveDirection(WorldGrid* world) = 0;
	// try to move the bug to a new position
	virtual bool tryMove(Bug* bug) = 0;
	// get the type of the bug
	virtual BugType getType() const;
	// reset the last action of the bug
	void resetLastAction();
	// reset the last breed of the bug
	void resetLastBreed();
	// get char for bug type
	static char getCharFromType(BugType bugType);
	// for easy printing of the bug
	friend std::ostream& operator<<(std::ostream& out, const Bug* bug);
};

#endif
