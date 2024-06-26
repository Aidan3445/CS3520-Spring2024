#ifndef FACILITY_M_HPP
#define FACILITY_M_HPP

#include "event.hpp"
#include <memory>
#include <set>
#include <algorithm>

class FacilityManager {
  private:
	// the calendar of events
	std::set<std::shared_ptr<Event>, EventComparator> calendar;
	// get events and tickets for a user
	std::set<std::shared_ptr<Event>, EventComparator> getUserEvents(const std::string& userID);
	std::set<std::shared_ptr<Event>, EventComparator> getUserTickets(const std::string& userID);

  public:
	// uses default constructor
	FacilityManager() = default;

	// get all events
	std::set<std::shared_ptr<Event>, EventComparator>& getCalendar();
	std::set<std::shared_ptr<Event>> getAllEventsBetween(std::pair<DateTime, DateTime> interval);

	// get single event from the calendar
	std::shared_ptr<Event> getEvent(const DateTime& startingFrom);

	// add an event to the calendar
	void addEvent(const std::shared_ptr<Event>& newEvent,
				  const int& hourlyLimit);	// throws error if event cannot be added
	// remove an event from the calendar
	void removeEvent(const DateTime& startingFrom);	 // throws error if event not found
	// printing information
	void printCalendar() const;
	void printUserEvents(const std::string& id);
	void printUserTickets(const std::string& id);
};

#endif	// FACILITY_M_HPP
