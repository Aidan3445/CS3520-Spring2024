#ifndef USER_HPP
#define USER_HPP

#include "wallet.hpp"
#include <string>
class User {
    private:
        // id of the user
        std::string id;

        // wallet for buying tickets and reserving spaces
        Wallet wallet;


};

#endif	// USER_HPP
