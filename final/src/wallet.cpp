#include "include/wallet.hpp"

// constructor
Wallet::Wallet() {
    this->balance = 0;
}

// get the balance of the wallet
unsigned int Wallet::getBalance() {
    return this->balance;
}

// add money to the wallet
void Wallet::addMoney(unsigned int amount) {
    this->balance += amount;
}

// remove money from the wallet
// this will throw an error and NOT remove any money
// if the amount is greater than the balance
void Wallet::removeMoney(unsigned int amount) {
    if (amount > this->balance) {
        throw "Not Enough Money";
    }
    this->balance -= amount;
}