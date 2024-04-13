#ifndef COMMUNITY_CENTER_HPP
#define COMMUNITY_CENTER_HPP

#include "facilityManager.hpp"
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

	// create an event
	void createEvent();

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
