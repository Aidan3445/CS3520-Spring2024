#ifndef ANTS_HPP
#define ANTS_HPP

#include "bug.hpp"

enum AntType { FEMALE, MALE, QUEEN };

// ant class
class Ant : public Bug {
  protected:
	// ant gender
	const AntType type;

  public:
	// constructor
	Ant(int starveTime, AntType type);
	// try to move the ant in a random direction
	virtual std::pair<int, int> moveDirection(WorldGrid* world) override;
	// ants cannot eat other bugs
	virtual bool tryMove(Bug* bug) override;
	// get the type of the bug
	BugType getType() const override;
	// get the gender
	AntType getAntType() const;

	// get symbol from type
	static char getAntSymbol(AntType type);
};

// female ants have some additional functionality
// queen ant class
class QueenAnt : public Ant, Breedable {
  public:
	// constructor
	QueenAnt(int starveTime, int breedTime);

	// determine if the queen ant is starving
	virtual bool starved() const override;
	// determine if the queen ant breeds
	virtual bool breed(WorldGrid* world) override;
};

// Cataglyphis ant class (a type of queen ant)
class CataglyphisAnt : public QueenAnt {
  public:
	// constructor
	CataglyphisAnt(int starveTime, int breedTime);

	// determine if the Cataglyphis breeds
	virtual bool breed(WorldGrid* world) override;
};

#endif
