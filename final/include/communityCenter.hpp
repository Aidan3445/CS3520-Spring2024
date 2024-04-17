#ifndef COMMUNITY_CENTER_HPP
#define COMMUNITY_CENTER_HPP

#include "facilityManager.hpp"
#include <unordered_map>
#include <algorithm>
class CommunityCenter {
  private:
	// the facility manager for this community center
	FacilityManager manager;
	// the user who is currently logged in
	std::unique_ptr<User> currentUser;

	// login as a user
	void login();

	// main menu for the community center
	void mainMenu();

	// menu for buying a ticket
	void buyTicketMenu();

	// create an event using user input
    void createEventMenu();

    void readDateTime(bool confirmed, DateTime &example, unsigned int &month, unsigned int &day, unsigned int &year, unsigned int &hour, unsigned int &min, DateTime &startTime, bool &retFlag);

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
