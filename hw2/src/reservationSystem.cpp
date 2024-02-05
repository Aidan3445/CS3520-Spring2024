// This file contains the ReservationSystem struct method implementations.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "../include/reservationSystem.hpp"
#include "../include/utils.hpp"

using namespace std;

// load flight data from file
void ReservationSystem::load() {
    // reset seat assignments
    for (unsigned int row = 0; row < flight.getRows(); row++) {
        for (unsigned int seat = 0; seat < flight.getSeatsPerRow(); seat++) {
            flight.assignSeat("", row, seat, false);
        }
    }

    // open file
    ifstream file;
    file.open("./data/flightData.txt");    

    // confirm file opened without error
    if (!file) {
        cout << "Error opening file. File not found." << endl;
        // logout user
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
            user.logout();
            return;
        }
        // add seat assignments
        flight.assignSeat(passengerName, seat, false);
    }
}

// save flight data to file
void ReservationSystem::save() {
    // open file
    ofstream file;
    file.open("./data/flightData.txt");

    // confirm file opened without error
    if (!file) {
        cout << "Error opening file. File not found." << endl;
        // logout user
        user.logout();
        return;
    }

    // write flight data
    // data is stored with the odd lines are passenger names and even lines are seat assignments
    string assignment;
    for (unsigned int row = 0; row < flight.getRows(); row++) {
        for (unsigned int seat = 0; seat < flight.getSeatsPerRow(); seat++) {
            assignment = flight.getSeatAssignment(row, seat);
            if (assignment != "") {
                file << assignment << endl;
                file << setw(2) << setfill('0') << row + 1 <<
                    flight.seatNumberToLetter(seat) << endl;
            }
        }
    }
}

// login as passenger
void ReservationSystem::passengerLogin() {
    // all user input for passenger name is assumed to be valid
    // so we don't need to check the input
    string passengerName;
    // get passenger name
    cout << "Please enter your name: ";
    // clear cin from previous input
    utils::clearCin();
    getline(cin, passengerName);

    // set user to passenger and update user name
    user.login(passengerName, passenger);
    // load flight data
    load();
}

// login as employee
void ReservationSystem::employeeLogin() {
    // clear cin from previous input
    utils::clearCin();

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
            user.logout();
            return;
        }

        // read employee data and check for match
        // employee ID and password are stored on the same line separated by a space
        string line;
        while (getline(file, line)) {
            if (line == employeeID + " " + employeePassword) {
                // match found
                user.login(employeeID, employee);
                // load flight data
                load();
                return;
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
            user.logout();
            return;
        } else {
            cout << "Invalid input." << endl;
        }
    }
}

// serve menu for logged in user
void ReservationSystem::serveMenu() {
    // serve menu based on user type
    while (true) {
        if (user.getStatus() == passenger) {
            passengerMenu();
        } else if (user.getStatus() == employee) {
            employeeMenu();
        } else {
            break;
        }
    }
}

// main menu for passengers
void ReservationSystem::passengerMenu() {
    // display menu options
    cout << "\nWelcome, " << user.getName() << "!" << endl;
    cout << "What would you like to do?" << endl;
    cout << "1. Seating Chart (1 or s)" << endl;
    cout << "2. Automatic Seat Assignment (2 or a)" << endl;
    cout << "3. Manual Seat Assignment (3 or m)" << endl;
    cout << "4. Update Reservation (4 or u)" << endl;
    cout << "5. Boarding Pass (5 or b)" << endl;
    cout << "6. Quit (6 or q)" << endl;

    // get user menu choice
    cout << "Please enter the number or letter of your choice: ";
    char choice;

    // note that the passanger's actions are automatically save to file
    // for any action that changes the seat assignments

    while (true) {
        cin >> choice;
        if (choice == '1' || choice == 's') {
            // display seating chart
            seatingChart();
            break;
        } else if (choice == '2' || choice == 'a') {
            // automatic seat assignment
            automaticSeatSelection(user.getName());
            // save updated flight data
            save();
            break;
        } else if (choice == '3' || choice == 'm') {
            // manual seat assignment
            manualSeatSelection(user.getName());
            // save updated flight data
            save();
            break;
        } else if (choice == '4' || choice == 'u') {
            // change or cancel reservation
            updateReservation(user.getName());
            // save updated flight data
            save();
            break;
        } else if (choice == '5' || choice == 'b') {
            // display boarding pass
            boardingPass(user.getName());
            break;
        } else if (choice == '6' || choice == 'q') {
            // quit
            user.logout();
            break;
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    }
}

// main menu for employees
void ReservationSystem::employeeMenu() {
    // display menu options
    cout << "\nWelcome, " << user.getName() << "!" << endl;
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

    // note that unlike the passanger, the employee's actions are not saved automatically
    // for the changes to be saved to file they must save their changes to file 
    // using option 4/v or saving on quit when prompted

    while (true) {
        cin >> choice;
        if (choice == '1' || choice == 's') {
            // display seating chart
            seatingChart();
            break;
        } else if (choice == '2' || choice == 'p') {
            // print passenger manifest
            passengerManifest();
            break;
        } else if (choice == '3' || choice == 'l') {
            if (!confirm("Are you sure you want to load previous seat assignment "
                        "and passenger manifest? This will delete any unsaved changes. (y/n): ")) {
                break;
            }
            // load previous seat assignment and passenger manifest
            load();
            seatingChart();
            cout << "Previous seat assignment and passenger manifest loaded." << endl;
            break;
        } else if (choice == '4' || choice == 'v') {
            // save current seat assignment and passenger manifest
            save();
            cout << "Current seat assignment and passenger manifest saved." << endl;
            break;
        } else if (choice == '5' || choice == 'r') {
            // re-assign or cancel a seat assignment
            updateReservation();
            break;
        } else if (choice == '6' || choice == 'q') {
            // prompt to save changes before quitting
            if (confirm("Would you like to save your changes before quitting? (y/n): ")) {
                save();
                cout << "Changes saved." << endl;
            }

            // quit
            user.logout();
            break;
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    }
}

// display the seating chart
void ReservationSystem::seatingChart() {
    cout << "Seating Chart" << endl;

    array<int, 2> aisles = flight.getAisles();
    
    for (unsigned int row = 0; row < flight.getRows(); row++) {
        for (unsigned int seat = 0; seat < flight.getSeatsPerRow(); seat++) {
            if (find(aisles.begin(), aisles.end(), seat) != aisles.end()) {
                // display row number in grey
                cout << "\e[1;30m" << setw(2) << row + 1 << "\e[0m ";
            }
            if (flight.getSeatAssignment(row, seat) != "") {
                // seat is taken, always red X
                cout << "\e[1;31mX\e[0m ";
            } else {
                // seat is available, seat letter in class color
                // first class green
                // business class yellow
                // economy class blue
                if (row < flight.getClassBounds()[0]) {
                    cout << "\e[1;32m" << flight.seatNumberToLetter(seat) << "\e[0m ";
                } else if (row < flight.getClassBounds()[1]) {
                    cout << "\e[1;33m" << flight.seatNumberToLetter(seat) << "\e[0m ";
                } else {
                    cout << "\e[1;34m" << flight.seatNumberToLetter(seat) << "\e[0m ";
                }
            }
        }
        cout << endl;
    }
}

// automatic seat selection via random number generator
void ReservationSystem::automaticSeatSelection(const string &passengerName) {
    // set seed 
    srand(time(nullptr));
    // get random number
    int beginAt = rand() % (flight.getRows() * flight.getSeatsPerRow());

    // to ensure efficient search and to avoid infinite loops
    // we will start at a random seat and walk through the seats
    // looping back to the beginning if necessary
    // we will stop when we find an empty seat or
    // if we return to the beginning without finding an empty seat

    // first check initial seat
    int row = beginAt / flight.getSeatsPerRow();
    int seat = beginAt % flight.getSeatsPerRow();

    if (flight.nextAvailableSeat(passengerName, row, flight.getRows(), seat) != "" ||
            flight.nextAvailableSeat(passengerName, 0, row, seat) != "") {
        return;
    }

    // no seats available
    cout << "No seats available." << endl;
}

// manual seat selection
void ReservationSystem::manualSeatSelection(const string &passengerName) {
    // display seating chart
    seatingChart();

    while (true) {
        // get user input for class
        char classChoice;
        cout << "Would you like a seat in first class or business class? "
            "(f/b/anthing else for economy): ";
        cin >> classChoice;
        classChoice = tolower(classChoice);

        // available seats
        vector<string> available;
        if (classChoice == 'f') {
            // get available seats in first class
            available = flight.availableSeats(0, flight.getClassBounds()[0]);
        } else if (classChoice == 'b') {
            // get available seats in business
            available = flight.availableSeats(
                    flight.getClassBounds()[0], flight.getClassBounds()[1]);
        } else {
            // get available seats in economy
            available = flight.availableSeats(flight.getClassBounds()[1], flight.getRows());
        }

        if (available.size() == 0) {
            // no seats available in the selected class
            cout << "No seats available in the selected class." << endl;
            continue;
        }

        // get user input for seat or automatic seat selection
        string seatChoice;
        utils::clearCin();
        while (available.size() > 0) {
            // display available seats
            cout << "Available seats: " << endl;
            for (unsigned int i = 0; i < available.size(); i++) {
                cout << available[i] << " ";
                if (i % 4 == 3 && i != available.size() - 1) {
                    cout << endl;
                }
            }
            cout << endl;

            cout << "Please select an open seat or press enter for automatic seat selection: "
                "(or enter 'c' to cancel) ";
            getline(cin, seatChoice);
            if (seatChoice == "") {
                flight.assignSeat(passengerName, available[0]);
                return;
            } else if (find(available.begin(), available.end(), seatChoice) != available.end()) {
                flight.assignSeat(passengerName, seatChoice);
                return;
            } else if (seatChoice == "c") {
                if (confirm("Are you sure you want to cancel the reservation? (y/n): ")) {
                    return;
                }
            } else {
                cout << "Seat " << seatChoice << " is not an available seat. "
                    "Please try again." << endl;
            }
        }
    }
}

// change reservation
// if a user has multiple reservations, they should be prompted to select one
void ReservationSystem::updateReservation(string passengerName) {
    // if name is not provided, ask
    if (passengerName == "") {
        cout << "Please enter the name of the passenger "
            "whose reservation you would like to update: ";
        utils::clearCin();
        while (true) {
            getline(cin, passengerName);
            if (passengerName != "") {
                break;
            } else {
                cout << "Invalid input. Please try again." << endl;
            }
        }
    }

    // get user's seat assignments
    vector<string> seats = flight.findSeats(passengerName);

    // take action based on number of reservations
    string changeSeat;
    if (seats.size() == 0) {
        // user has no reservations
        cout << "There are no reservations for " << passengerName << "." << endl;
        return;
    } else if (seats.size() == 1) {
        // user has one reservation
        changeSeat = seats[0];
    } else {
        // user has multiple reservations
        cout << "There are multiple reservations for " << passengerName << ":" << endl;
        for (unsigned int i = 0; i < seats.size(); i++) {
            cout << i + 1 << ". " << seats[i] << endl;
        }

        // get user choice
        while (true) {
            cout << "Please enter the reservation you would like to update: ";
            cin >> changeSeat;
            // check if choice is valid
            if (find(seats.begin(), seats.end(), changeSeat) != seats.end()) {
                break;
            } else {
                cout << "Invalid input. Please try again." << endl;
            }
        }
    }

    // get input to change or cancel reservation
    char choice;
    while (true) {
        cout << "Would you like to update or cancel the reservation " << changeSeat << 
            "? (u/c): ";
        cin >> choice;
        choice = tolower(choice);
        if (choice == 'u') {
            // make new reservation
            manualSeatSelection(passengerName);
            break;
        } else if (choice == 'c') {
            cout << "To confirm cancellation, please enter your seat assignment ('" << 
                changeSeat << "') again: ";
            cin >> changeSeat;
            if (flight.getSeatAssignment(changeSeat) == passengerName) {
            cout << "Reservation " << changeSeat << " for " << 
                passengerName << " has been cancelled." << endl;
            break;
            } else {
                cout << "Seat assignment does not match. Reservation not cancelled." << endl;
                return;
            }
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    }

    // cancel reservation
    flight.assignSeat("", changeSeat, false);
}

// display boarding pass
void ReservationSystem::boardingPass(const string &passengerName) {
    // get user's seat assignments
    vector<string> seats = flight.findSeats(passengerName);
    string displaySeat;

    // take action based on number of reservations
    if (seats.size() == 0) {
        // user has no reservations
        cout << "You have no reservations." << endl;
        return;
    } else if (seats.size() == 1) {
        // user has one reservation
        displaySeat = seats[0];
    } else {
        // user has multiple reservations
        cout << "You have multiple reservations:" << endl;
        for (unsigned int i = 0; i < seats.size(); i++) {
            cout << i + 1 << ". " << seats[i] << endl;
        }

        // get user choice
        while (true) {
            cout << "Please enter the reservation you would like to see the boarding pass for: ";
            cin >> displaySeat;
            // check if choice is valid
            if (find(seats.begin(), seats.end(), displaySeat) != seats.end()) {
                break;
            } else {
                cout << "Invalid input. Please try again." << endl;
            }
        }
    }

    // display boarding pass
    /*
       +-----------------------------------+ 
       |                                   |
       |  Flight: CS3520                   |
       |                                   |
       |  Name:  John Doe                  |
       |  Class: Business                  |
       |  Seat:  3A                        |
       |                                   |
       +-----------------------------------+
       */

    cout << "+-----------------------------------+" << endl;
    cout << "|                                   |" << endl;
    cout << "|  Flight: " << left << setw(25) << flight.getFlightNumber() << "|" << endl;
    cout << "|                                   |" << endl;
    cout << "|  Name:   " << setw(25) << user.getName().substr(0, 24) << "|" << endl;
    cout << "|  Class:  " << setw(25) << flight.seatToClass(displaySeat) << "|" << endl;
    cout << "|  Seat:   " << setw(25) << displaySeat << "|" << endl;
    cout << "|                                   |" << endl;
    cout << "+-----------------------------------+" << endl;
}



// display passenger manifest
void ReservationSystem::passengerManifest() {
    // display passenger manifest and store as a vector of strings
    vector<array<string, 3>> manifest;
    cout << "Passenger Manifest" << endl;
    for (unsigned int row = 0; row < flight.getRows(); row++) {
        for (unsigned int seat = 0; seat < flight.getSeatsPerRow(); seat++) {
            if (flight.getSeatAssignment(row, seat) != "") {
                array<string, 3> passengerInfo = {
                    to_string(row + 1) + flight.seatNumberToLetter(seat), 
                    flight.seatToClass(to_string(row + 1) + flight.seatNumberToLetter(seat)), 
                    flight.getSeatAssignment(row, seat)
                };

                cout << left << setw(5) << passengerInfo[0] << 
                    setw(10) << passengerInfo[1] << passengerInfo[2] << endl;
                manifest.push_back(passengerInfo);
            }
        }
    }

    // get user input to continue
    char choice;
    if (!confirm("Would you like to sort the passenger manifest? (y/n): ")) {
        return;
    }

    // get user input to sort by name seat or class,
    bool hasFiltered = false;
    while (true) {
        cout << "Would you like to sort by name or seat? (n/s): ";
        if (!hasFiltered) {
            cout << "or filter by class? (c): ";
        }
        cin >> choice;
        choice = tolower(choice);
        if (choice == 'n') {
            // sort by name
            sort(manifest.begin(), manifest.end(), utils::compareName);
            break;
        } else if (choice == 's') {
            // sort by seat
            sort(manifest.begin(), manifest.end(), utils::compareSeat);
            break;
        } else if (!hasFiltered && choice == 'c') {
            // get class to filter by
            char classFilter; 
            cout << "Please enter the class to filter by (f/b/e): ";
            cin >> classFilter;
            classFilter = tolower(classFilter);
            string classFilterString;
            if (classFilter == 'f') {
                classFilterString = "First";
            } else if (classFilter == 'b') {
                classFilterString = "Business";
            } else if (classFilter == 'e') {
                classFilterString = "Economy";
            } else {
                cout << "Invalid input. Please try again." << endl;
                continue;
            }
            // filter by class
            utils::filterClass(manifest, classFilterString);
            // don't break loop so they can sort the filtered list
            hasFiltered = true;
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    }

    // ascending or descending
    while (true) {
        cout << "Would you like to sort in ascending or descending order? (a/d): ";
        cin >> choice;
        choice = tolower(choice);
        if (choice == 'a') {
            // already ascending
            break;
        } else if (choice == 'd') {
            // descending
            reverse(manifest.begin(), manifest.end());
            break;
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    }

    // display sorted/filtered manifest
    cout << "Passenger Manifest:" << endl;
    for (auto &passenger : manifest) {
        cout << left << setw(5) << passenger[0] << 
            setw(10) << passenger[1] << passenger[2] << endl;
    }
}

// confirm user action
bool ReservationSystem::confirm(string message) {
    char choice;
    while (true) {
        cout << message;
        cin >> choice;
        choice = tolower(choice);
        if (choice == 'y') {
            return true;
        } else if (choice == 'n') {
            return false;
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    }
}


