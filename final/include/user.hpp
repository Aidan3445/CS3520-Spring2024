#ifndef USER_HPP
#define USER_HPP

// Forward definition
class Event;

#include "wallet.hpp"
#include <memory>
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
	std::shared_ptr<Wallet> wallet;

  public:
	// Constructor
	User(std::string id, ResidencyStatus residencyStatus, unsigned int balance);

	// getters
	std::string myID() const;
	std::shared_ptr<Wallet> myWallet() const;
	ResidencyStatus myResidency() const;

	// convert a string to a residency status and vice versa
	static ResidencyStatus stringToResidencyStatus(const std::string& residency);
	static std::string residencyStatusToString(ResidencyStatus residency);
};

#endif	// USER_HPP
