#ifndef BREEDBUG_HPP
#define BREEDBUG_HPP

#include "bug.hpp"

class BreedableBug : public Bug {
  protected:
	// number of time steps before a bug breeds
	const int breedTime;
	// the time step when the bug last bred
	int lastBreed;

	// constructor
	BreedableBug(int starveTime, int breedTime, char symbol);

  public:
	virtual bool breed(WorldGrid* world) const = 0;
};

#endif
