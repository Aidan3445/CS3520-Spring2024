// This file represents the reservation system, an interface for employees and passengers to interact with the flight data.

#ifndef RESERVATIONSYSTEM_HPP
#define RESERVATIONSYSTEM_HPP

#include "flight.hpp"
#include "user.hpp"

struct ReservationSystem {
    private:
        // flight data
        Flight flight;
        // user data
        User user;

        // load and save flight data from a file
        void load();
        void save();

        // display the seating chart
        void seatingChart();

        // seat selection
        void automaticSeatSelection(const string &passengerName);
        void manualSeatSelection(const string &passengerName);

        // change own reservation
        void updateReservation(string passengerName = "");

        // display boarding pass
        void boardingPass(const string &passengerName);

        // display passenger manifest
        void passengerManifest();

        // user confirmation
        bool confirm(const string message = "Are you sure? (y/n): ");

    public:
        // login as passenger or employee
        void passengerLogin();
        void employeeLogin();

        // serve menu for logged in user
        void serveMenu();

        // main menu for passenger or employee
        void passengerMenu();
        void employeeMenu();
};

#endif
