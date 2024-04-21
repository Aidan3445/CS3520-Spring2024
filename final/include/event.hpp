#ifndef EVENT_HPP
#define EVENT_HPP

#include "dateTime.hpp"
#include "user.hpp"
#include <algorithm>
#include <fstream>
#include <vector>

// Enum for the layout style of the event
enum LayoutStyle { MEETING, LECTURE, WEDDING, DANCE };

class Event {
  private:
	// name of the event
	std::string name;
	// Start time also acts as an ID for this Event
	DateTime startTime, endTime;
	// Layout style of the event
	const LayoutStyle style;
	// ID of the user who organized this event
	const std::string organizer;

  protected:
	// virtual helper for printing event details
	virtual std::string getDetails() const;

  public:
	// Constructor
	Event(std::string name,
		  DateTime startTime,
		  DateTime endTime,
		  LayoutStyle style,
		  std::string organizerID);

	// Destructor
	virtual ~Event() = default;

	// getters
	std::string getName() const;
	DateTime getStartTime() const;
	DateTime getEndTime() const;
	std::string getOrganizer() const;
	LayoutStyle getStyle() const;

	// is the user in the guest list?
	virtual bool isUserInGuestList(const std::string id) const;

	// operator overloads for comparison
	bool operator<(const Event& e) const;

	// write to file
	virtual void writeToFile(std::ofstream& file) const;

	// print the event
	friend std::ostream& operator<<(std::ostream& os, const Event& e);

	// convert a string to a layout style and vice versa
	static LayoutStyle stringToLayoutStyle(const std::string& style);
	static std::string layoutStyleToString(LayoutStyle style);

	double eventRate(const double& hourlyRate);
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

  protected:
	// helper for printing event details
	std::string getDetails() const override;

  public:
	// Constructor
	PublicEvent(std::string name,
				DateTime startTime,
				DateTime endTime,
				LayoutStyle style,
				std::string organizerID,
				int ticketCost,
				bool openToNonResidents = true);

	// additional constructor that sets guest list
	PublicEvent(std::string name,
				DateTime startTime,
				DateTime endTime,
				LayoutStyle style,
				std::string organizerID,
				int ticketCost,
				std::vector<std::string> guestList,
				bool openToNonResidents = true);


	// getters
	bool isOpenToNonResidents() const;
	int getTicketCost() const;

	// write to file
	void writeToFile(std::ofstream& file) const override;

	// add a ticket to this event for the given user
	void purchaseTicket(User& user);

	// is the user in the guest list?
	bool isUserInGuestList(const std::string id) const override;
};

// PrivateEvent is an alias for Event
typedef Event PrivateEvent;

// event comparator
struct EventComparator {
	bool operator()(const std::shared_ptr<Event>& e1, const std::shared_ptr<Event>& e2) const;
};

#endif
