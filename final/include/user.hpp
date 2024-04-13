#ifndef USER_HPP
#define USER_HPP

// Forward definition
class Event;

#include "wallet.hpp"
#include <string>

// Enum for residency status
enum ResidencyStatus { RESIDENT, NON_RESIDENT, CITY };

class User {
  private:
	// id of the user
	const std::string id;
	// Whether this user is a resident, non-resident, or the city
	const ResidencyStatus residencyStatus;
	// wallet for buying tickets and reserving spaces
	Wallet wallet;

  public:
	// Constructor
	User(std::string id, ResidencyStatus residencyStatus, Wallet wallet);

	// getters
	std::string myID() const;
	Wallet myWallet() const;
	ResidencyStatus myResidency() const;
};

#endif	// USER_HPP
