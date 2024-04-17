#ifndef WALLET_HPP
#define WALLET_HPP

#include "utility.hpp"
#include <iostream>
#include <stdexcept>

class Wallet {
  private:
	// hold the amount of money in the wallet
	double balance = 0;

  public:
	// constructor
	Wallet();

	// get the balance of the wallet
	double getBalance();

	// add money to the wallet
	void deposit(const double& amount);

	// remove money from the wallet
	// this will throw an error and NOT remove any money
	// if the amount is greater than the balance
	void withdraw(const double& amount);

	// menu for interacting with the wallet
	void menu();
};

#endif	// WALLET_HPP
