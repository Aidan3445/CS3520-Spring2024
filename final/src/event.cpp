#include "../include/event.hpp"

// Constructor
Event::Event(DateTime start, DateTime end, LayoutStyle style, std::string organizerID) :
	style(style), organizerID(organizerID) {
	this->startTime = start;
	this->endTime = end;
}

// Getters
DateTime Event::getStartTime() const { return startTime; }
DateTime Event::getEndTime() const { return endTime; }
std::string Event::getOrganizerID() const { return organizerID; }
LayoutStyle Event::getStyle() const { return style; }

// Constructor for PublicEvent
PublicEvent::PublicEvent(DateTime start,
						 DateTime end,
						 LayoutStyle style,
						 std::string organizerID,
						 int ticketCost,
						 bool openToNonResidents) :
	Event(start, end, style, organizerID),
	ticketCost(ticketCost), openToNonResidents(openToNonResidents) {
	ticketCost = 0;
}

// Adds a ticket to this event to the given user
void PublicEvent::purchaseTicket(User user) {
	if (guestList.size() < MAX_GUESTS) {
		try {
			Wallet userWallet = user.myWallet();
			userWallet.removeMoney(ticketCost);
			guestList.push_back(user.myID());
			std::cout << "Ticket purchased successfully." << std::endl;
		} catch (std::runtime_error& e) { std::cout << e.what() << std::endl; }
	} else {
		std::cout << "Sorry, this event is full." << std::endl;
	}
}

// Getters
bool PublicEvent::isOpenToNonResidents() const { return openToNonResidents; }
int PublicEvent::getTicketCost() const { return ticketCost; }

// Is the user in the guest list?
bool PublicEvent::isUserInGuestList(const User& user) const {
	return std::find(guestList.begin(), guestList.end(), user.myID()) != guestList.end();
}
