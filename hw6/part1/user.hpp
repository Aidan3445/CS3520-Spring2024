#include "order.hpp"
#include "cart.hpp"
#include <iostream>
using namespace std;

class User {
    private:
        string username;
        Cart my_cart;
        vector<Gift> favorites;
        vector<Order> order_history;
    public:
        vector<Order> my_orders();
        vector<Gift> find_gifts_by_name(const string&);
        vector<Gift> find_gifts_by_name(const string&, const Shop&);
        Coupon enter_coupon_code(const string&);
        void add_to_favorites(const Gift&);
};