// Debug T-2
// Function template finds biggest of two or three objects. The function works on any data type
// which has greater than operator defined.

#include <iostream>
#include <string>
using namespace std;

template<class T>
void findBiggest(T a, T b, T c) {  // type of b should be T not int
	T large = a;
	if (b > large)
		large = b;
	if (c > large)	// < -> >
		large = c;
	// use large in the out statement
	cout << "The largest of " << a << " " << b << " " << c << " is " << large << endl;
}

template<class T>
void findBiggest(T a, T b) {
	T large = a;
	if (b > large)	// == -> >
		large = b;
	cout << "The larger of " << a << " " << b << " is " << large << endl;  // larger -> large
}

class BankAccount {
	friend ostream& operator<<(ostream&, const BankAccount&);

  private:
	string name;
	int amount;

  public:
	BankAccount(const int);
	BankAccount(const string&, const int);	// add string + int constructor
	bool operator>(const BankAccount&);

	// add friend function for << operator
	friend ostream& operator<<(ostream& out, const BankAccount& bh);
};

BankAccount::BankAccount(const string& name, const int amount) {
	this->name = name;	// add this-> for name and amount
	this->amount = amount;
}

ostream& operator<<(ostream& out, const BankAccount& bh) {
	out << "Name: " << bh.name << " Amount: " << bh.amount << endl;	 // add bh. for name and amount
	return out;														 // also fix << inside quotes
}

bool BankAccount::operator>(const BankAccount& bh) {
	bool flag = false;	// == -> =
	if (amount > bh.amount)
		flag = true;
	return flag;
}
int main() {
	BankAccount bAA("A", 800);
	BankAccount bAB("B", 120);
	BankAccount bAC("C", 500);
	findBiggest(bAA, bAB);
	findBiggest(bAB, bAC);
	findBiggest(bAC, bAA);
	findBiggest(bAA, bAB, bAC);
	return 0;
}
