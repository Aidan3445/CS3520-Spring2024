#ifndef FACILITY_M_HPP
#define FACILITY_M_HPP

#include "event.hpp"
#include <memory>

class FacilityManager {
    private:
        std::vector<std::unique_ptr<Event>> calendar;
    public:
        void addEvent(std::unique_ptr<Event> e); // throws error if event cannot be added
        void removeEvent(const DateTime& startingFrom); // throws error if event not found
        void printCalendar() const;
        void printCalendar(const DateTime& startingFrom) const;
        void printUserEvents(const User& user);
        void printUserTickets(const User& user);
};

#endif // FACILITY_M_HPP