#ifndef BREEDBUG_HPP
#define BREEDBUG_HPP

#include "Bug.hpp"

class BreedableBug : public Bug {
  private:
	// number of time steps before a bug breeds
	const int breedTime;
	// the time step when the bug last bred
	int lastBreed;

  protected:
	// constructor
	BreedableBug(int breedTime, int starveTime, char symbol);

  public:
	virtual bool breed(WorldGrid* world) const = 0;
};

#endif
