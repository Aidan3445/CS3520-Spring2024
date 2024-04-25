#include "../include/wallet.hpp"

// constructor
Wallet::Wallet() { this->balance = 0; }

// get the balance of the wallet
double Wallet::getBalance() { return this->balance; }

// add money to the wallet
void Wallet::deposit(const double& amount) {
	// limit to $10,000.00 in the wallet at any time
	if (this->balance + amount > 10000) {
		throw std::runtime_error("Wallet cannot contain more than $10,000.00");
		return;
	}

	this->balance += amount;
}

// remove money from the wallet
// this will throw an error and NOT remove any money
// if the amount is greater than the balance
void Wallet::withdraw(const double& amount) {
	if (amount > this->balance) {
		throw std::runtime_error("Insufficient funds");
	}
	this->balance -= amount;
}

// menu for interacting with the wallet
void Wallet::menu() {
	bool running = true;
	while (running) {
		std::cout << "What would you like to do?\n"
				  << HEADER << "   [b]" << RESET << "  Balance\n"
				  << HEADER << "   [d]" << RESET << "  Deposit\n " << HEADER << "  [w]" << RESET
				  << "  Withdraw\n " << HEADER << "  [e]" << RESET << "  Exit" << std::endl;

		// get input from the user
		char chosen;
		std::cin >> chosen;

		switch (chosen) {
			case 'b':
				std::cout << "Balance: " << DOLLARS << this->getBalance() << RESET << std::endl;
				break;
			case 'd':
				std::cout << "How much would you like to deposit?" << std::endl;
				double depositAmount;
				std::cin >> depositAmount;
				try {
					this->deposit(depositAmount);
				} catch (std::runtime_error& e) {
					std::cout << ERROR << e.what() << RESET << std::endl;
					break;
				}
				std::cout << "Deposited " << DOLLARS << depositAmount << RESET << std::endl;
				break;
			case 'w':
				std::cout << "How much would you like to withdraw?" << std::endl;
				double withdrawAmount;
				std::cin >> withdrawAmount;
				try {
					this->withdraw(withdrawAmount);
					std::cout << "Withdrew $" << ERROR << withdrawAmount << RESET << std::endl;
					std::cout << "Remaining balance: " << DOLLARS << this->getBalance() << RESET
							  << std::endl;
				} catch (std::runtime_error& e) {
					std::cout << ERROR << e.what() << RESET << std::endl;
				}
				break;
			case 'e':
				std::cout << "Exitting wallet" << std::endl;
				running = false;
				break;
			default: std::cout << "Invalid Input" << std::endl;
		}
	}

	std::cin.ignore();
}
