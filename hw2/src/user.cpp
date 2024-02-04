// Description: This file contains the User struct method implementations.

#include "../include/user.hpp"

// get user's name
string User::getName() {
    return name;
}

// get login status 
loginStatus User::getStatus() {
    return status;
}

// login user, set user's name and status
void User::login(const string &userName, const loginStatus &userStatus) {
    name = userName;
    status = userStatus;
}

// logout user, set user's name and status
void User::logout() {
    name = "";
    status = none;
}
