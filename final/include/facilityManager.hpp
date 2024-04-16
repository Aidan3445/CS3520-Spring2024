#ifndef FACILITY_M_HPP
#define FACILITY_M_HPP

#include "event.hpp"
#include <memory>
#include <set>

class FacilityManager {
  private:
	// the calendar of events
	std::set<std::unique_ptr<Event>, EventComparator> calendar;
	// get events and tickets for a user
	std::vector<std::unique_ptr<Event>> getUserEvents(std::string userID);
	std::vector<std::unique_ptr<Event>> getUserTickets(std::string userID);

  public:
	// uses default constructor
	FacilityManager() = default;

	// add an event to the calendar
	void addEvent(std::unique_ptr<Event> newEvent);	 // throws error if event cannot be added
	// remove an event from the calendar
	void removeEvent(const DateTime& startingFrom);	 // throws error if event not found
	// printing information
	void printCalendar() const;
	void printCalendar(const DateTime& startingFrom) const;
	void printUserEvents(const User& user);
	void printUserTickets(const User& user);
};

#endif	// FACILITY_M_HPP
