#ifndef USER_HPP
#define USER_HPP

// Forward definition
class Event;

#include "wallet.hpp"
#include <string>
#include <vector>

/** Whether a user is a resident, non-resident, or the city */
enum ResidencyStatus {
    RESIDENT, NON_RESIDENT, CITY
};

class User {
    private:
        // id of the user
        std::string id;

        // wallet for buying tickets and reserving spaces
        Wallet wallet;

        // events scheduled by this user
        std::vector<Event> reservations;

        // events this user has tickets to
        std::vector<Event> tickets;

        // Whether this user is a resident, non-resident, or the city
        ResidencyStatus residencyStatus;
    public:
        /** Gettes */
        std::string myID();
        Wallet myWallet();
        ResidencyStatus myResidency();
        std::vector<Event> myEvents();
        std::vector<Event> myTickets();

        /** Adding events and tickets */
        void scheduleEvent(const Event& e); // throws error if event can't be scheduled
        void removeEvent(const Event& e);
        void addTicket(const Event& e);
};

#endif	// USER_HPP
