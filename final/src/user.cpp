#include "../include/user.hpp"

// Constructor
User::User(std::string id, double balance) : id(id) {
	this->wallet = std::shared_ptr<Wallet>(new Wallet());
	this->wallet.get()->deposit(balance);
}

City::City(const std::string& id, const double& balance) : User(id, balance) {}
Resident::Resident(const std::string& id, const double& balance) : User(id, balance) {}
NonResident::NonResident(const std::string& id, const double& balance) : Resident(id, balance) {}

// getters
std::string User::myID() const { return this->id; }

std::shared_ptr<Wallet> User::myWallet() const { return this->wallet; }

// write to file
void User::writeToFile(std::ofstream& file) const {
	file << myID() << " " << myWallet().get()->getBalance() << " " << residency();
}

// residency
std::string City::residency() const { return "CITY"; }
std::string Resident::residency() const { return "RESIDENT"; }
std::string NonResident::residency() const { return "NON_RESIDENT"; }

// hourly rate
int City::hourlyRate() const { return 5; }
int Resident::hourlyRate() const { return 10; }
int NonResident::hourlyRate() const { return 15; }

// hour limit
int City::hourLimit() const { return 48; }
int Resident::hourLimit() const { return 24; }
