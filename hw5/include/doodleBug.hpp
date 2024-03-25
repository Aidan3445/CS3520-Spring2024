#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP

#include "breedableBug.hpp"

// doodlebug class
class DoodleBug : public BreedableBug {
  public:
	// constructor
	DoodleBug(int starveTime, int breedTime, char symbol);
};

#endif
