#ifndef ANTS_HPP
#define ANTS_HPP

#include "breedableBug.hpp"

// ant class
class Ant : public Bug {};

// subdivide the ants
typedef Ant MaleAnt;
typedef Ant FemaleAnt;

// female ants have some additional functionality
// queen ant class
class QueenAnt : public FemaleAnt, public BreedableBug {
  public:
	// constructor
	QueenAnt(int starveTime, int breedTime, char symbol);
};

// Cataglyphis ant class (a type of queen ant)
class CataglyphisAnt : public QueenAnt {};

#endif
