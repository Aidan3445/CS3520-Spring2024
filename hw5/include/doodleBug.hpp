#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP

#include "../include/bug.hpp"

// doodlebug class
class DoodleBug : public Bug {
  private:
	std::pair<int, int> previousDirection;

  public:
	// constructor
	DoodleBug(int starveTime, int breedTime);
	// determine if the doodlebug breeds
	virtual bool breed(const WorldGrid* const world) override;
	// try to move the doodlebug to a new position
	virtual std::pair<int, int> moveDirection(WorldGrid* world) override;
	// try to move the doodlebug to a new position
	virtual bool tryMove(Bug* bug) override;
};

#endif
