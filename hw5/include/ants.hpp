#ifndef ANTS_HPP
#define ANTS_HPP

#include "bug.hpp"

enum AntGender { FEMALE, MALE };

// ant class
class Ant : public Bug {
  protected:
	// ant gender
	const AntGender gender;

  public:
	// constructor
	Ant(int starveTime, char symbol, AntGender gender);
	// determine if the ant is starving
	virtual bool starved() const;
	// try to move the ant in a random direction
	virtual std::pair<int, int> move(WorldGrid* world);
	// ants cannot eat other bugs
	virtual bool tryMove(Bug* bug);
	// get the gender
	AntGender getGender() const;
};

// female ants have some additional functionality
// queen ant class
class QueenAnt : public Ant, public Breedable {
  public:
	// constructor
	QueenAnt(int starveTime, int breedTime, char symbol);

	// determine if the queen ant is starving
	virtual bool starved() const;
	// determine if the queen ant breeds
	virtual bool breed(WorldGrid* world) const;
};

// Cataglyphis ant class (a type of queen ant)
class CataglyphisAnt : public QueenAnt {
  public:
	// constructor
	CataglyphisAnt(int starveTime, int breedTime, char symbol);

	// determine if the Cataglyphis breeds
	virtual bool breed(WorldGrid* world) const;
};

#endif
