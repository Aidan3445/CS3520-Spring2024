#include "../include/event.hpp"
#include <memory>
#include <sstream>

// Constructor
Event::Event(std::string name,
			 DateTime start,
			 DateTime end,
			 LayoutStyle style,
			 std::string organizerID,
			 ResidencyStatus organizerResidency) :
	style(style),
	organizer(std::make_pair(organizerID, organizerResidency)) {
	this->name = name;
	this->startTime = start;
	this->endTime = end;
}

// get details of the event
std::string Event::getDetails() const {
	std::stringstream ss;
	ss << name << ": \033[33m" << startTime.getTime() << " - " << endTime.getTime()
	   << "\033[0m (Organizer: \033[36m" << organizer.first << "\033[0m)";
	return ss.str();
}

// Getters
std::string Event::getName() const { return name; }
DateTime Event::getStartTime() const { return startTime; }
DateTime Event::getEndTime() const { return endTime; }
std::pair<std::string, ResidencyStatus> Event::getOrganizer() const { return organizer; }
LayoutStyle Event::getStyle() const { return style; }

// Print the event
std::ostream& operator<<(std::ostream& os, const Event& e) {
	os << e.getDetails();
	return os;
}

// operator overloads for comparison
bool Event::operator<(const Event& e) const { return startTime < e.startTime; }

// Constructor for PublicEvent
PublicEvent::PublicEvent(std::string name,
						 DateTime start,
						 DateTime end,
						 LayoutStyle style,
						 std::string organizerID,
						 ResidencyStatus residencyStatus,
						 int ticketCost,
						 bool openToNonResidents) :
	Event(name, start, end, style, organizerID, residencyStatus),
	ticketCost(ticketCost), openToNonResidents(openToNonResidents) {
	ticketCost = 0;
}

// Adds a ticket to this event to the given user
void PublicEvent::purchaseTicket(User user) {
	if (guestList.size() < MAX_GUESTS) {
		try {
			std::shared_ptr<Wallet> userWallet = user.myWallet();
			userWallet.get()->withdraw(ticketCost);
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

// override the getDetails method
// Dodgeball Tournament: 10:00 - 14:00 (Tickets: $10, Organizer: John Doe)
std::string PublicEvent::getDetails() const {
	std::stringstream ss;
	ss << getName() << ": \033[33m" << getStartTime().getTime() << " - " << getEndTime().getTime()
	   << "\033[0m (Ticket: \033[32m$" << ticketCost << "\033[0m, Organizer: \033[36m"
	   << getOrganizer().first << "\033[0m)";
	return ss.str();
}

// event compator
bool EventComparator::operator()(const std::unique_ptr<Event>& e1,
								 const std::unique_ptr<Event>& e2) const {
	return e1.get()->getStartTime() < e2.get()->getStartTime();
}
