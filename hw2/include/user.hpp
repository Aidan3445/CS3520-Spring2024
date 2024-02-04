// This file contains the User struct, which represents a passenger or employee user.
// It also contains the loginStatus enum, which helps to track the login status of the user.

#include <string>
using namespace std;

#ifndef USER_HPP
#define USER_HPP

// track login status and user type
enum loginStatus {
    none,
    passenger,
    employee
};

// user representing passenger or employee
struct User {
    private:
        string name;
        loginStatus status;
    
    public:
        // get user's name
        string getName();

        // get user's login status
        loginStatus getStatus();

        // helper function to login user and set user info
        void login(const string &name, const loginStatus &status);

        // helper function to logout user and clear user info
        void logout();
};

#endif

