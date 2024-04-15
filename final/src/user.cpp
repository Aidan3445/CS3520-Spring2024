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
