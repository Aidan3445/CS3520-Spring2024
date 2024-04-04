#include <string>
#include <vector>

class Shop;	 // forward declaration
class Gift;	 // forward declaration

class Order {
  private:
	// Member variables for the Order class
	std::string date_placed;
	std::string shipping_details;
	Shop* shop;
	std::vector<Gift*> gifts;

  public:
	// constructor
	Order(std::string date_placed, std::string shipping_details, Shop* shop);
	// getters
	std::string get_date_placed();
	std::string get_shipping_details();
	Shop* get_shop();
	// calculate total price including shipping
	double calculate_total_price();
	// try to cancel the order and return success status
	bool cancel_order();
};
