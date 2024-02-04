#include <iostream>
#include "../include/reservationSystem.hpp"

using namespace std;

/* main function */
int main() {
    // create reservation system
    ReservationSystem res;

    cout << "Welcome to the Reservation System!" << endl;
    // login as passenger or employee
    while (true) {
        cout << "Are you a passenger or employee? (p/e/q to quit): ";
        char userType;
        cin >> userType;
        // convert to lowercase
        userType = tolower(userType);

        if (userType == 'p') {
            // login as passenger
            res.passengerLogin();
            break;
        } else if (userType == 'e') {
            // login as employee
            res.employeeLogin();
            break;
        } else if (userType == 'q') {
            // quit
            return 0;
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    }
    
    res.serveMenu();


    // logout message
    cout << "Thank you for using the Reservation System!" << endl;
    return 0;
}







