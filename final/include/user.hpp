#ifndef USER_HPP
#define USER_HPP

// Forward definition
class Event;

#include "wallet.hpp"
#include <fstream>
#include <memory>
#include <string>

class User {
  private:
	// id of the user
	const std::string id;
	// wallet for buying tickets and reserving spaces
	std::shared_ptr<Wallet> wallet;

  protected:
	// constructor
	User(std::string id, double balance);

  public:
	// getters
	std::string myID() const;
	std::shared_ptr<Wallet> myWallet() const;

	// write to file
	void writeToFile(std::ofstream& file) const;

	// get residency status as a string
	virtual std::string residency() const = 0;

	// get hourly rate for the user type
	virtual int hourlyRate() const = 0;

	// get the hour limit for the user type
	virtual int hourLimit() const = 0;

	virtual ~User() = default;
};

// City User
class City : public User {
  public:
	// constructor
	City(const std::string& id, const double& balance);

	// get residency status as a string
	std::string residency() const override;

	// get hourly rate for the user type
	int hourlyRate() const override;

	// get the hour limit for the user type
	int hourLimit() const override;

	virtual ~City() = default;
};

// Resident User
class Resident : public User {
  public:
	// constructor
	Resident(const std::string& id, const double& balance);

	// get residency status as a string
	std::string residency() const override;

	// get hourly rate for the user type
	int hourlyRate() const override;

	// get the hour limit for the user type
	int hourLimit() const override;

	virtual ~Resident() = default;
};

class NonResident : public Resident {
  public:
	// constructor
	NonResident(const std::string& id, const double& balance);

	// get residency status as a string
	std::string residency() const override;

	// get hourly rate for the user type
	int hourlyRate() const override;

	virtual ~NonResident() = default;
};

#endif	// USER_HPP
