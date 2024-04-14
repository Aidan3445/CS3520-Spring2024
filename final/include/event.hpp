#ifndef EVENT_HPP
#define EVENT_HPP

#include "dateTime.hpp"
#include "user.hpp"
#include <vector>

// Enum for the layout style of the event
enum LayoutStyle { MEETING, LECTURE, WEDDING, DANCE };

class Event {
  private:
	// Start time also acts as an ID for this Event
	DateTime startTime, endTime;
	// Layout style of the event
	const LayoutStyle style;
	// ID of the user who organized this event
	const std::string organizerID;

  public:
	// Constructor
	Event(DateTime startTime, DateTime endTime, LayoutStyle style, std::string organizerID);

	// getters
	DateTime getStartTime() const;
	DateTime getEndTime() const;
	std::string getOrganizerID() const;
	LayoutStyle getStyle() const;
};

class PublicEvent : public Event {
  private:
	// list of guests who purchased tickets
	std::vector<std::string> guestList;
	// can non-residents attend this event?
	const bool openToNonResidents;
	// cost of a ticket
	const int ticketCost;

	// static variable for max number of guests
	static const int MAX_GUESTS = 25;

  public:
	PublicEvent(DateTime startTime,
				DateTime endTime,
				LayoutStyle style,
				std::string organizerID,
				int ticketCost,
				bool openToNonResidents = true);
	/** Adds a ticket to this event to the given user */
	void purchaseTicket(User user);

	// getters
	bool isOpenToNonResidents() const;
	int getTicketCost() const;

	// is the user in the guest list?
	bool isUserInGuestList(const User& user) const;
};

// PrivateEvent is an alias for Event
typedef Event PrivateEvent;

#endif
