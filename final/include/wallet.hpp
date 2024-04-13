#ifndef WALLET_HPP
#define WALLET_HPP

class Wallet {
  private:
	// hold the amount of money in the wallet
	int balance = 0;

  public:
	// constructor
	Wallet();

	// get the balance of the wallet
	int getBalance();

	// add money to the wallet
	void addMoney(int amount);

	// remove money from the wallet
	// this will throw an error and NOT remove any money
	// if the amount is greater than the balance
	void removeMoney(int amount);
};

#endif	// WALLET_HPP
