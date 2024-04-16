#include "../include/user.hpp"

// Constructor
User::User(std::string id, ResidencyStatus residencyStatus, unsigned int balance) :
	id(id), residencyStatus(residencyStatus) {
	this->wallet = std::shared_ptr<Wallet>(new Wallet());
	this->wallet.get()->deposit(balance);
}

// getters
std::string User::myID() const { return this->id; }

std::shared_ptr<Wallet> User::myWallet() const { return this->wallet; }

ResidencyStatus User::myResidency() const { return this->residencyStatus; }

// convert a string to a residency status and vice versa
ResidencyStatus User::stringToResidencyStatus(const std::string& residency) {
	if (residency == "RESIDENT") {
		return RESIDENT;
	} else if (residency == "NON_RESIDENT") {
		return NON_RESIDENT;
	} else if (residency == "CITY") {
		return CITY;
	} else {
		throw std::invalid_argument("Invalid residency status: " + residency);
	}
}

std::string User::residencyStatusToString(ResidencyStatus residency) {
	switch (residency) {
		case RESIDENT: return "RESIDENT";
		case NON_RESIDENT: return "NON_RESIDENT";
		case CITY: return "CITY";
		default: throw std::invalid_argument("Invalid residency status");
	}
}
