#ifndef ANTS_HPP
#define ANTS_HPP

#include "bug.hpp"
#include <memory>

// ant class
class Ant : public Bug {
  public:
	// constructor
	Ant(int starveTime, BugType type);
	Ant(int starveTime, int breedTime, BugType type);

	// try to move the ant in a random direction
	virtual std::pair<int, int> moveDirection(WorldGrid* world) override;
	// ants cannot eat other bugs
	virtual bool tryMove(Bug* bug) override;
	// ants that are not queens cannot breed
	virtual void breed(WorldGrid* const world) override;
};

// female ants have some additional functionality
// queen ant class
class QueenAnt : public Ant {
  protected:
	const double spawnFemaleChance;
	const double femaleIsQueenChance;
	const double queenIsCataglyphisChance;
	// spawn an ant according to the odds above
	std::unique_ptr<Ant> spawnAnt();

  public:
	// constructor
	QueenAnt(int starveTime,
			 int breedTime,
			 double spawnFemalChance,
			 double femaleIsQueenChance,
			 double queenIsCataglyphisChance);

	// determine if the queen ant is starving
	virtual bool starved() const override;
	// determine if the queen ant breeds
	virtual void breed(WorldGrid* const world) override;
};

// Cataglyphis ant class (a type of queen ant)
class CataglyphisAnt : public QueenAnt {
  public:
	// constructor
	CataglyphisAnt(int starveTime,
				   int breedTime,
				   double spawnFemaleChance,
				   double femaleIsQueenChance);

	// determine if the Cataglyphis breeds
	virtual void breed(WorldGrid* const world) override;
};

#endif
