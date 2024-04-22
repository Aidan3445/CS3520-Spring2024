#ifndef COMMUNITY_CENTER_HPP
#define COMMUNITY_CENTER_HPP

#include "facilityManager.hpp"
#include <fstream>

class CommunityCenter {
  private:
	// the facility manager for this community center
	FacilityManager manager;
	// the user who is currently logged in
	std::unique_ptr<User> currentUser;

	// login as a user
	void initUser();

	// main menu for the community center
	void mainMenu();

	// menu for buying a ticket
	void buyTicketMenu();

	// create an event using user input
	void createEventMenu();

	// the menu used for getting an event or ticket
	std::shared_ptr<Event> getEventMenu();

	// caneling an event
	void cancelEventMenu();
	void cancelEvent(const std::shared_ptr<Event>& event);
	void removeAllTicketsFrom(const std::shared_ptr<Event>& event);
	void cancelAllEventsBetween(const std::pair<DateTime, DateTime> interval);

	// canceling a ticket
	void cancelTicketMenu();

	// adds users from an event's waitlist to that event, if possible
	void addWaitlistToEvent(std::shared_ptr<Event>& event);

  public:
	// constructor
	//  reads files and initializes the facility manager
	CommunityCenter();

	// destructor
	//  writes files and cleans up
	~CommunityCenter();

	// run the community center
	void run();
};

#endif	// COMMUNITY_CENTER_HPP
