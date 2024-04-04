#include <iostream>
using namespace std;

/** A coupon that reduces the total price of an order. */
class Coupon {
    private:
        string expiration_date;
        double percent_multiplier;
    public:
        /** Constructor */
        Coupon(string expiration_date, double percent_multiplier);
        /** Applies the given coupon onto a cost to create a post coupon cost */
        double apply_coupon(const double&);
};