// This file contains the Flight struct, which represents a passanger flight.

#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include <string>
#include <array>
#include <vector>

using namespace std;

struct Flight {
    private:
        // flight details
        const string flightNumber = "CS 3520";
        static const int rows = 12;
        static const int seatsPerRow = 6;
        const array<int, 2> aisles = {2, 5};
        const array<int, 2> classBounds = {1, 4};

        // passenger details
        string seatAssignments[rows][seatsPerRow];

    public:
        // get name assigned to seat by seat string or row and seat number
        string getSeatAssignment(const string &seat);
        string getSeatAssignment(const int row, const int seat);

        // find seat assignment(s) for passenger
        vector<string> findSeats(const string &passengerName);

        // assign seat to passenger by seat string or row and seat number
        void assignSeat(const string &passengerName, const string &seat);
        void assignSeat(const string &passengerName, const int row, const int seat);

        // assign seat to passenger
        // start at a given row (and optional seat) and walk through the plane
        // to find the first available seat, assigning it to the passenger
        string nextAvailableSeat(const string &passengerName, 
                const int startRow, const int endRow, int startSeat = 0);
        

        // get flight number
        string getFlightNumber();

        // get number of rows
        int getRows();

        // get number of seats per row
        int getSeatsPerRow();

        // get aisle locations as indeces of seat numbers that are left of the aisle
        array<int, 2> getAisles();

        // get class bounds as indeces of row numbers that are the start of a new class
        array<int, 2> getClassBounds();

        // convert seat letter to seat number and vice versa
        int seatLetterToNumber(char seatLetter);
        char seatNumberToLetter(const int seatNumber);
        // get seat class
        string seatToClass(const string seat);

};

#endif
