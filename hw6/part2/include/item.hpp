#ifndef ITEM_HPP
#define ITEM_HPP

#include <ostream>
template<typename T>
class Item {
  private:
	// Member variables for the Item class
	T value;
	int id;
	int price;
	std::string name;
	std::string owner;

  public:
	// constructor
	Item(T value, int id, int price, std::string name, std::string owner) :
		value(value), id(id), price(price), name(name), owner(owner) {}
	// destructor
	~Item() = default;
	// copy constructor
	Item(const Item<T>& item) :
		value(item.value), id(item.id), price(item.price), name(item.name), owner(item.owner) {}
	// copy assignment operator
	Item<T>& operator=(const Item<T>& item) {
		if (this != &item) {
			value = item.value;
			id = item.id;
			price = item.price;
			name = item.name;
			owner = item.owner;
		}
		return *this;
	}

	// getters
	T get_value() const { return value; }
	int get_id() const { return id; }
	int get_price() const { return price; }
	std::string get_name() const { return name; }
	std::string get_owner() const { return owner; }

	// operator overloading
	bool operator==(const Item<T>* item) const { return this->id == item->id; }
	bool operator!=(const Item<T>* item) const { return this->id != item->id; }

	// friend function to overload the << operator
	friend std::ostream& operator<<(std::ostream& os, const Item<T>* item) {
		os << item->value << ":\n"
		   << "  ID: " << item->id << "\n"
		   << "  Price: " << item->price << "\n"
		   << "  Name: " << item->name << "\n"
		   << "  Owner: " << item->owner;
		return os;
	}
};

#endif	// ITEM_HPP
