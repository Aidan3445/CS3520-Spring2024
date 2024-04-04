#include "order.hpp"
#include "cart.hpp"
#include <string>
using namespace std;

/**
 * Represents a user's account in our gift system.
 */
class User {
    private:
        string username;
        Cart my_cart;
        vector<Gift> favorites;
        vector<Order> order_history;
    public:
        /** Constructor */
        User(string username);
        /** Gets the orders from the order history. */
        vector<Order> my_orders();
        /** Searches for a gift in all shops by name */
        vector<Gift> find_gifts_by_name(const string&);
        /** Searches for a gift in the given shop by name */
        vector<Gift> find_gifts_by_name(const string&, const Shop&);
        /** Adds a coupon */
        Coupon enter_coupon_code(const string&);
        /** Adds a Gift to favorites */
        void add_to_favorites(const Gift&);
};