#include "../include/event.hpp"
#include "../include/utility.hpp"

// Constructor
Event::Event(
	std::string name, DateTime start, DateTime end, LayoutStyle style, std::string organizerID) :
	name(name),
	startTime(start), endTime(end), style(style), organizer(organizerID) {
	// ensure time is before end time and within 9:00-21:00
	if (start >= end) {
		throw std::invalid_argument("Start time must be before end time");
	}
	if (start.getHour() < 9 || start.getHour() >= 21) {
		throw std::invalid_argument("Start time must be between 9:00 and 21:00");
	}
	if (end.getHour() <= 9 || end.getHour() > 21) {
		throw std::invalid_argument("End time must be between 9:00 and 21:00. is" +
									std::to_string(end.getHour()));
	}
}

// get details of the event
std::string Event::getDetails() const {
	std::stringstream ss;
	ss << EVENT_NAME << getName() << RESET << ": " << getStartTime().getTime() << " - "
	   << getEndTime().getTime() << " (Organizer: " << USER << getOrganizer() << RESET << ")";
	return ss.str();
}

// Getters
std::string Event::getName() const { return name; }
DateTime Event::getStartTime() const { return startTime; }
DateTime Event::getEndTime() const { return endTime; }
std::string Event::getOrganizer() const { return organizer; }
LayoutStyle Event::getStyle() const { return style; }

// write to file
// helper for writing to file
void writeCommonData(std::ofstream& file, const Event* e) {
	file << e->getName() << ";";
	DateTime date = e->getStartTime();
	file << date.getMonth() << "," << date.getDay() << "," << date.getYear() << ";";
	file << date.getHour() << "," << date.getMin() << ";";
	date = e->getEndTime();
	file << date.getMonth() << "," << date.getDay() << "," << date.getYear() << ";";
	file << date.getHour() << "," << date.getMin() << ";";
	file << Event::layoutStyleToString(e->getStyle()) << ";";
	file << e->getOrganizer();
}

void Event::writeToFile(std::ofstream& file) const {
	writeCommonData(file, this);
	// empty guest list, open to non-residents, ticket cost
	file << ";;;";
}

// private events dont have a guest list of ticket purchases
bool Event::isUserInGuestList(const std::string id) const { return false; }

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
						 int ticketCost,
						 bool openToNonResidents) :
	Event(name, start, end, style, organizerID),
	ticketCost(ticketCost), openToNonResidents(openToNonResidents) {
	ticketCost = 0;
}

// additional constructor that sets guest list
PublicEvent::PublicEvent(std::string name,
						 DateTime start,
						 DateTime end,
						 LayoutStyle style,
						 std::string organizerID,
						 int ticketCost,
						 std::vector<std::string> guestList,
						 bool openToNonResidents) :
	Event(name, start, end, style, organizerID),
	ticketCost(ticketCost), openToNonResidents(openToNonResidents), guestList(guestList) {}

// Adds a ticket to this event to the given user
void PublicEvent::purchaseTicket(User& user) {
	if (guestList.size() < MAX_GUESTS) {
		try {
			std::shared_ptr<Wallet> userWallet = user.myWallet();
			userWallet.get()->withdraw(ticketCost);
			guestList.push_back(user.myID());
			std::cout << USER << user.myID() << RESET << " has purchased a ticket to " << EVENT_NAME
					  << getName() << RESET << std::endl;
			std::cout << "Remaining balance: " << DOLLARS << userWallet.get()->getBalance() << RESET
					  << std::endl
					  << std::endl;
		} catch (std::runtime_error& e) {
			std::cout << ERROR << e.what() << RESET << " - Ticket cost: " << DOLLARS << ticketCost
					  << RESET << ", Balance: " << DOLLARS << user.myWallet().get()->getBalance()
					  << RESET << std::endl
					  << std::endl;
		}
	} else {
		std::cout << ERROR << "Event is full" << RESET << std::endl;
	}
}

// Getters
bool PublicEvent::isOpenToNonResidents() const { return openToNonResidents; }
int PublicEvent::getTicketCost() const { return ticketCost; }

// write to file
void PublicEvent::writeToFile(std::ofstream& file) const {
	// write the event details
	writeCommonData(file, this);
	file << ";";

	// write additional public event details
	std::for_each(guestList.begin(), guestList.end(), [&file](const std::string& guest) {
		file << guest << ",";
	});
	file << ";";
	file << (openToNonResidents ? "true" : "false") << ";";
	file << ticketCost;
}

// Is the user in the guest list?
bool PublicEvent::isUserInGuestList(const std::string id) const {
	return std::find(guestList.begin(), guestList.end(), id) != guestList.end();
}

// override the getDetails method
// Dodgeball Tournament: 10:00 - 14:00 (Tickets: $10, Organizer: John Doe)
std::string PublicEvent::getDetails() const {
	std::stringstream ss;
	ss << EVENT_NAME << getName() << RESET << ": " << getStartTime().getTime() << " - "
	   << getEndTime().getTime() << " (Ticket: " << DOLLARS << ticketCost << RESET
	   << ", Organizer: " << USER << getOrganizer() << RESET << ")";
	return ss.str();
}

// event compator
bool EventComparator::operator()(const std::shared_ptr<Event>& e1,
								 const std::shared_ptr<Event>& e2) const {
	return e1.get()->getStartTime() < e2.get()->getStartTime();
}

// convert a string to a layout style
LayoutStyle Event::stringToLayoutStyle(const std::string& style) {
	if (style == "MEETING") {
		return LayoutStyle::MEETING;
	} else if (style == "DANCE") {
		return LayoutStyle::DANCE;
	} else if (style == "LECTURE") {
		return LayoutStyle::LECTURE;
	} else if (style == "WEDDING") {
		return LayoutStyle::WEDDING;
	} else {
		throw std::invalid_argument("Invalid layout style");
	}
}

// convert a layout style to a string
std::string Event::layoutStyleToString(LayoutStyle style) {
	switch (style) {
		case LayoutStyle::MEETING: return "MEETING";
		case LayoutStyle::DANCE: return "DANCE";
		case LayoutStyle::LECTURE: return "LECTURE";
		case LayoutStyle::WEDDING: return "WEDDING";
		default: throw std::invalid_argument("Invalid layout style");
	}
}

double Event::eventRate(const double& hourlyRate) {
	int duration =
		(endTime.getHour() - startTime.getHour()) * 60 + endTime.getMin() - startTime.getMin();
	return duration / 60 * hourlyRate;
}