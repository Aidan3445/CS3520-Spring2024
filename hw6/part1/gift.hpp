#include <array>
#include <string>

class Shop;	 // forward declaration

// Gift classes are used to represent gifts that can be purchased from a shop
class Gift {
  private:
	// Member variables for the gift class
	const std::string name;
	const std::string description;
	const double price;
	const Shop* shop;

  public:
	// constructor
	Gift(std::string name, std::string description, double price, Shop* shop);
	// getters
	std::string get_name();
	std::string get_description();
	double get_price();
	Shop* get_shop();
};

// EGift class is a subclass of the Gift class
// this represents gifts that are electronic like a giftcard or a dowload
class EGift : public Gift {
  private:
	// Member variables for the EGift class
	std::string sctivation_code;
	std::string expiration_date;

  public:
	// constructor that will call base Gift class constructor
	EGift(std::string name,
		  std::string description,
		  double price,
		  Shop* shop,
		  std::string activation_code,
		  std::string expiration_date);
	// get code
	std::string get_activation_code();
	// check if expired
	bool is_expired();
};

// PhysicalGift class is a subclass of the Gift
// this represents gifts that are physical like a toy or a book
class PhysicalGift : public Gift {
  private:
	// Member variables for the PhysicalGift class
	double weight;
	std::array<double, 3> size;	 // {length, width, height}

  public:
	// constructor that will call base Gift class constructor
	PhysicalGift(std::string name,
				 std::string description,
				 double price,
				 Shop* shop,
				 double weight,
				 std::array<double, 3> size);
	// get weight
	double get_weight();
	// get size
	std::array<double, 3> get_size();
};
