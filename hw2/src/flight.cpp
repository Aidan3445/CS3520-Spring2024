// This file contains the Flight struct method implementations.

#include "../include/flight.hpp"
#include <iostream>

using namespace std;

// get flight number
string Flight::getFlightNumber() {
    return flightNumber;
}

// get number of rows
int Flight::getRows() {
    return rows;
}

// get number of seats per row
int Flight::getSeatsPerRow() {
    return seatsPerRow;
}

// get aisle locations as indeces of seat numbers that are left of the aisle
array<int, 2> Flight::getAisles() {
    return aisles;
}

// get class bounds as indeces of row numbers that are the start of a new class
array<int, 2> Flight::getClassBounds() {
    return classBounds;
}

// get name assigned to seat by row and seat number
string Flight::getSeatAssignment(const int row, const int seat) {
    return seatAssignments[row][seat];
}

// get name assigned to seat by seat string
string Flight::getSeatAssignment(const string &seat) {
    // get row and seat number
    int row = stoi(seat) - 1;
    int seatNumber = seatLetterToNumber(seat.back());

    // get seat assignment
    return getSeatAssignment(row, seatNumber);
}

// assign seat to passenger by row and seat number
void Flight::assignSeat(const string &passengerName, const int row, const int seat) {
    // assign seat
    seatAssignments[row][seat] = passengerName;
}

// assign seat to passenger by seat string
void Flight::assignSeat(const string &passengerName, const string &seat) {
    // get row and seat number
    int row = stoi(seat) - 1;
    int seatNumber = seatLetterToNumber(seat.back());

    // assign seat
    assignSeat(passengerName, row, seatNumber);
}

// assign first open seat to passenger in a given range
string Flight::nextAvailableSeat(const string &passengerName, 
        const int startRow, const int endRow, int startSeat) {
    // find first available seat in the specified rows
    for (int row = startRow; row < endRow; row++) {
        for (int seat = startSeat; seat < seatsPerRow; seat++) {
            if (getSeatAssignment(row, seat) == "") {
                // seat is empty, assign it
                assignSeat(passengerName, row, seat);
                cout << "Seat " << row + 1 << seatNumberToLetter(seat) 
                    << " has been assigned to " << passengerName << endl;
                return to_string(row + 1) + seatNumberToLetter(seat);
            }
        }
        // reset startSeat to 0 after first iteration
        startSeat = 0;
    }
    return "";
}

// find seat assignment
vector<string> Flight::findSeats(const string &passengerName) {
    vector<string> seats;
    for (int row = 0; row < rows; row++) {
        for (int seat = 0; seat < seatsPerRow; seat++) {
            if (getSeatAssignment(row, seat) == passengerName) {
                seats.push_back(to_string(row + 1) + seatNumberToLetter(seat));
            }
        }
    }
    return seats;
}

/*** Helper Functions ***/
// convert a seat letter to a seat number
// because 'C' and 'G' are skipped, we need to offset the seat number
int Flight::seatLetterToNumber(char seatLetter) {
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
char Flight::seatNumberToLetter(int seatNumber) {
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

// convert a row number to a class
string Flight::seatToClass(string seat) {
    if ((stoi(seat) - 1) < classBounds[0]) {
        return "First";
    } else if ((stoi(seat) - 1) < classBounds[1]) {
        return "Business";
    } else {
        return "Economy";
    }
}
