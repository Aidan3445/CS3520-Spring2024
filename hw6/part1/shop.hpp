#include "coupon.hpp"
#include "gift.hpp"
#include "order.hpp"
#include <map>
#include <string>
#include <vector>

// Shop class is used to represent a shop that sells gifts
class Shop {
  private:
	// Member variables for the Shop class
	std::string name;
	std::map<std::unique_ptr<Gift>, uint> stock;
	std::vector<std::string> coupon_codes;

	// remove item from the stock
	// this is called upon order confirmation
	void remove_stock(std::unique_ptr<Gift> gift);
	bool has_gift(std::unique_ptr<Gift> gift);

  public:
	// constructor
	Shop(std::string name);
	// getters
	std::string get_name();
	std::vector<std::unique_ptr<Gift>> get_items();
	// get the stock of a gift
	uint get_stock(std::unique_ptr<Gift> gift);
	// add gift to stock
	void add_stock(std::unique_ptr<Gift> gift, uint quantity);
	// test a coupon code
	Coupon* test_coupon(std::string code);
	// confirm an order
	bool confirm_order(std::unique_ptr<Order> order);
};

// DigitalShop class is a subclass of the Shop
// this represents shops that sell digital gifts only
class DigitalShop : public Shop {
  private:
	// Member variables for the DigitalShop class
	std::string website;

  public:
	// constructor that will call base Shop class constructor
	DigitalShop(std::string name, std::string website);
	// getters
	std::string get_website();
};

// PhysicalShop class is a subclass of the Shop
// this represents shops that sell physical gifts only
class PhysicalShop : public Shop {
  private:
	// Member variables for the PhysicalShop class
	std::string address;

  public:
	// constructor that will call base Shop class constructor
	PhysicalShop(std::string name, std::string address);
	// getters
	std::string get_address();
};
