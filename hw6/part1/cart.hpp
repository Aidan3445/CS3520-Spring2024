#include "gift.hpp"
#include "coupon.hpp"
#include "order.hpp"
#include <vector>
using namespace std;

/** 
 * Represents the shopping cart of a user.
 * It is used to store items the user may buy and 
 * will place the user's order.
 */
class Cart {
    private:
        vector<Gift> items;
        vector<Coupon> applied_coupons;
    public:
        /** Constructor */
        Cart();
        /** Calculates the pre-shipping price */
        double calculate_subtotal();
        /** Creates an order at each shop that that the Gifts in items belong */
        vector<Order> create_orders();
        /** Adds a Gift to this cart */
        void add_item(const Gift&);
        /** Adds a vector of Gift to this cart. Can be used to add all of the user's favorites with one method */
        void add_items(const vector<Gift>&);
        /** Removes an item from this cart */
        void remove_item(const Gift&);
        /** Applies a coupon to this cart */
        void apply_coupon(const Coupon&);
        /** Gets all items in this cart */
        vector<Gift> get_added_items();
};