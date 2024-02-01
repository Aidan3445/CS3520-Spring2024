#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>

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


/* helper functions */
// convert seat letter to seat number and vice versa
int seatLetterToNumber(char seatLetter);
char seatNumberToLetter(int seatNumber);

// clear cin buffer
void clearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// debug method log current line
void logCurrentLine(int line) {
    cout << "Current line: " << line << endl;
}

/* global variables */
// flight info
const int rows = 12;
const int seatsPerRow = 6;

// the current user
User user;

// list of seat assignments
string seatAssignments[rows][seatsPerRow];


/* main function */
int main() {
    // load flight data
    load();

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

    // serve menu based on user type
    while (true) {
        if (user.status == passenger) {
            passengerMenu();
        } else if (user.status == employee) {
            employeeMenu();
        } else {
            break;
        }
    }

    // logout message
    cout << "Thank you for using the Reservation System!" << endl;
    return 0;
}


// convert a seat letter to a seat number
// because 'C' and 'G' are skipped, we need to offset the seat number
int seatLetterToNumber(char seatLetter) {
    // convert to uppercase
    seatLetter = toupper(seatLetter);

    // convert to seat number
    int seatNumber = seatLetter - 'A';
    // offset seat number
    if (seatNumber >= 2) {
        seatNumber--;
    }
    if (seatNumber >= 6) {
        seatNumber--;
    }

    return seatNumber;
}

// convert a seat number to a seat letter
// because 'C' and 'G' are skipped, we need to offset the seat number
char seatNumberToLetter(int seatNumber) {
    // offset seat number
    if (seatNumber >= 2) {
        seatNumber++;
    }
    if (seatNumber >= 6) {
        seatNumber++;
    }

    // convert to seat letter and return
    return seatNumber + 'A';
}

// load flight data from file
void load() {
    // open file
    ifstream file;
    file.open("./data/flightData.txt");    
    
    // confirm file opened without error
    if (!file) {
        cout << "Error opening file. File not found." << endl;
        // logout user
        user.status = none;
        return;
    }

    // read flight data
    // data is stored with the odd lines are passenger names and even lines are seat assignments
    // such that passenger on line n is assigned seat on line n+1
    string passengerName;
    string seat;

    // while there are lines left, get the passenger
    while (getline(file, passengerName)) {
        // get the seat assignment
        if (!getline(file, seat)) {
            cout << "Error reading file. No seat assignment found for " << passengerName << endl;
            // logout user
            user.status = none;
            return;
        }
        // add seat assignments
        seatAssignments[stoi(seat.substr(0, 2))][seatLetterToNumber(seat[2])] = passengerName;
    }
}


// save flight data to file
void save() {
    // open file
    ofstream file;
    file.open("./data/flightData.txt");

    // confirm file opened without error
    if (!file) {
        cout << "Error opening file. File not found." << endl;
        // logout user
        user.status = none;
        return;
    }

    // write flight data
    // data is stored with the odd lines are passenger names and even lines are seat assignments
    for (int row = 0; row < rows; row++) {
        for (int seat = 0; seat < seatsPerRow; seat++) {
            if (seatAssignments[row][seat] != "") {
                file << seatAssignments[row][seat] << endl;
                file << setw(2) << setfill('0') << row << seatNumberToLetter(seat) << endl;
            }
        }
    }
}


// login as passenger
User passengerLogin() {
    // all user input for passenger name is assumed to be valid
    // so we don't need to check the input
    User p;
    // set status to passenger
    p.status = passenger;
    // get passenger name
    cout << "Please enter your name: ";
    // clear cin from previous input
    clearCin();
    getline(cin, p.passengerName);
    return p;
}

// login as employee
User employeeLogin() {
    User e;
    // set status to employee
    e.status = employee;

    // clear cin from previous input
    clearCin();

    // use loop to allow multiple attempts
    // with a maximum of 3 attempts before quitting
    int attemptsRemaining = 3;
    while (attemptsRemaining > 0) {
        // get employee ID, ensure no spaces
        string employeeID;
        string employeePassword;
        while (true) {
            cout << "Please enter your employee ID: ";
            getline(cin, employeeID);
            if (employeeID.find(' ') != string::npos) {
                cout << "Employee ID cannot contain spaces." << endl;
            } else {
                break;
            }
        }

        // get employee password, ensure no spaces
        while (true) {
            cout << "Please enter your password: ";
            getline(cin, employeePassword);
            if (employeePassword.find(' ') != string::npos) {
                cout << "Password cannot contain spaces." << endl;
            } else {
                break;
            }
        }

        // check database for employee ID and password combination
        ifstream file;
        file.open("./data/employeeData.txt");

        // confirm file opened without error
        if (!file) {
            cout << "Error opening file. File not found." << endl;
            // logout user
           e.status = none;
            return e;
        }

        // read employee data and check for match
        // employee ID and password are stored on the same line separated by a space
        string line;
        while (getline(file, line)) {
            logCurrentLine(__LINE__);
            if (line == employeeID + " " + employeePassword) {
                // match found
                e.employeeID = employeeID;
                e.employeePassword = employeePassword;
                return e;
            }
        }

        // no match found
        cout << "Employee ID and password combination not found. " << 
            employeeID << " " << employeePassword << endl;            
        attemptsRemaining--;
    }

    // after three attempts, allow user to quitm try again, or continue as passenger
   char tryAgain;
    while (true) {
        cout << "Would you like to try again, login as a passenger, or quit? (t/p/q): ";
        cin >> tryAgain;
        tryAgain = tolower(tryAgain);
        if (tryAgain == 't') {
            // try again
            return employeeLogin();
        } else if (tryAgain == 'p') {
            // login as passenger
            return passengerLogin();
        } else if (tryAgain == 'q') {
            // quit
            e.status = none;
            return e;
        } else {
            cout << "Invalid input." << endl;
        }
    }
}


// main menu for passengers
void passengerMenu() {
    // display menu options
    cout << "\nWelcome, " << user.passengerName << "!" << endl;
    cout << "What would you like to do?" << endl;
    cout << "1. Seating Chart (1 or s)" << endl;
    cout << "2. Automatic Seat Assignment (2 or a)" << endl;
    cout << "3. Manual Seat Assignment (3 or m)" << endl;
    cout << "4. Change or Cancel Reservation (4 or c)" << endl;
    cout << "5. Boarding Pass (5 or b)" << endl;
    cout << "6. Quit (6 or q)" << endl;

    // get user menu choice
    cout << "Please enter the number or letter of your choice: ";
    char choice;
    while (true) {
        cin >> choice;
        if (choice == '1' || choice == 's') {
            // display seating chart
            seatingChart();
            break;
        } else if (choice == '2' || choice == 'a') {
            // automatic seat assignment
            //automaticSeatSelection();
            break;
        } else if (choice == '3' || choice == 'm') {
            // manual seat assignment
            //manualSeatSelection();
            break;
        } else if (choice == '4' || choice == 'c') {
            // change or cancel reservation
            //changeReservation();
            break;
        } else if (choice == '5' || choice == 'b') {
            // display boarding pass
            //boardingPass();
            break;
        } else if (choice == '6' || choice == 'q') {
            // quit
            user.status = none;
            break;
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    }
}

// main menu for employees
void employeeMenu() {
    // display menu options
    cout << "\nWelcome, " << user.employeeID << "!" << endl;
    cout << "What would you like to do?" << endl;
    cout << "1. Seating Chart (1 or s)" << endl;
    cout << "2. Print Passenger Manifest (2 or p)" << endl;
    cout << "3. Load Previous Seat Assignment and Passenger Manifest (3 or l)" << endl;
    cout << "4. Save Current Seat Assignment and Passenger Manifest (4 or v)" << endl;
    cout << "5. Re-assign or Cancel a Seat Assignment (5 or r)" << endl;
    cout << "6. Quit (6 or q)" << endl;

    // get user menu choice
    cout << "Please enter the number or letter of your choice: ";
    char choice;
    while (true) {
        cin >> choice;
        if (choice == '1' || choice == 's') {
            // display seating chart
            seatingChart();
            break;
        } else if (choice == '2' || choice == 'p') {
            // print passenger manifest
            //passengerManifest();
            break;
        } else if (choice == '3' || choice == 'l') {
            // load previous seat assignment and passenger manifest
            //load();
            break;
        } else if (choice == '4' || choice == 'v') {
            // save current seat assignment and passenger manifest
            //save();
            break;
        } else if (choice == '5' || choice == 'r') {
            // re-assign or cancel a seat assignment
            //changeReservation();
            break;
        } else if (choice == '6' || choice == 'q') {
            // quit
            user.status = none;
            break;
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    }
}


// display the seating chart
void seatingChart() {
    // display seating chart
    cout << "Seating Chart" << endl;
    for (int row = 0; row < rows; row++) {
        for (int seat = 0; seat < seatsPerRow; seat++) {
            if (seat == 2 || seat == 5) {
                // display row number in grey
                cout << "\033[1;30m" << setw(2) << row + 1 << "\033[0m ";
            }
            if (seatAssignments[row][seat] != "") {
                // seat is taken, always red X
                cout << "\033[1;31mX\033[0m ";
            } else {
                // seat is available, seat letter in class color
                // first class green
                // business class yellow
                // economy class blue
                if (row < 1) {
                    cout << "\033[1;32m" << seatNumberToLetter(seat) << "\033[0m ";
                } else if (row < 6) {
                    cout << "\033[1;33m" << seatNumberToLetter(seat) << "\033[0m ";
                } else {
                    cout << "\033[1;34m" << seatNumberToLetter(seat) << "\033[0m ";
                }

                //cout << "\033[1;32m" << seatNumberToLetter(seat) << "\033[0m ";
            }
        }
        cout << endl;
    }
}

