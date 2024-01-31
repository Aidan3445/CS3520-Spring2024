#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

/* type definitions */
// track login status and user type
enum loginStatus {
    none,
    passenger,
    employee
};

// user representing passenger or employee
// TODO: separate passenger and employee into two structs of same type
struct User {
    string passengerName;
    string employeeID;
    string employeePassword;
    loginStatus status;
};


/* function prototypes */
// load and save flight data
void load();
void save();

// login as passenger or employee
User passengerLogin();
User employeeLogin();

// main menu for passenger or employee
void passengerMenu();
void employeeMenu();

// display the seating chart
void seatingChart();

/* passenger functions */
// seat selection
void automaticSeatSelection();
void manualSeatSelection();

// change own reservation
void changeReservation();

// display boarding pass
void boardingPass();


/* employee functions */
// display passenger manifest
void passengerManifest();

// change passanger reservation
void changeReservation(string &passengerName);


/* global variables */
// flight info
int rows = 12;
int seatsPerRow = 6;

// the current user
User user;

// list of passangers and seat assignments
vector<string> passengerList;
// 2D array of seat assignments
string seatAssignments[12][6];


/* main function */
int main() {
    // load flight data
    load();

    cout << "Welcome to the Reservation System!" << endl;
    // login as passenger or employee
    while (true) {
        cout << "Are you a passenger or employee? (p/e): or q to quit " << endl;
        char userType;
        cin >> userType;
        // convert to lowercase
        userType = tolower(userType);

        if (userType == 'p') {
            // login as passenger
            user = passengerLogin();
            break;
        } else if (userType == 'e') {
            // login as employee
            user = employeeLogin();
            break;
        } else if (userType == 'q') {
            // quit
            return 0;
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    }

    while (true) {
        // serve menu based on user type
        if (user.status == passenger) {
            passengerMenu();
        } else if (user.status == employee) {
            employeeMenu();
        }
    }

    // logout message
    cout << "Thank you for using the Reservation System!" << endl;
    return 0;
}

