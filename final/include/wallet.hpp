#ifndef WALLET_HPP
#define WALLET_HPP
#include <stdexcept>

class Wallet {
  private:
	// hold the amount of money in the wallet
	unsigned int balance = 0;

  public:
	// constructor
	Wallet();

	// get the balance of the wallet
	unsigned int getBalance();

	// add money to the wallet
	void deposit(unsigned int amount);

	// remove money from the wallet
	// this will throw an error and NOT remove any money
	// if the amount is greater than the balance
	void withdraw(unsigned int amount);
};

#endif	// WALLET_HPP
