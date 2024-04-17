#include "../include/communityCenter.hpp"
#include "../include/utility.hpp"
#include <utility>

// helper for updating user text file
void updateUserfile(const User& user);

// Constructor
CommunityCenter::CommunityCenter() {
	this->currentUser = nullptr;
	initUser();


	std::cout << "Welcome " << currentUser->myID() << std::endl;

	// read events from file and store in events in manager
	std::ifstream calendarFile("./data/calendar.txt");
	if (!calendarFile.is_open()) {
		throw std::runtime_error("Could not open calendar file: ./data/calendar.txt");
	}

	// read file anc catch any errors
	try {
		// first line holds the format of the file, print and ignore
		std::string line;
		std::getline(calendarFile, line);

		// read the events from the file until the end
		while (std::getline(calendarFile, line)) {
			// extract event name
			std::string name = util::next(line);
			util::shift(line);

			// extract start date
			unsigned int startMonth = std::stoi(util::nextEl(line));
			util::shiftEl(line);
			unsigned int startDay = std::stoi(util::nextEl(line));
			util::shiftEl(line);
			unsigned int startYear = std::stoi(line);
			util::shift(line);

			// extract start time
			unsigned int startHour = std::stoi(util::nextEl(line));
			util::shiftEl(line);
			unsigned int startMinute = std::stoi(line);
			DateTime start(startMonth, startDay, startYear, startHour, startMinute);
			util::shift(line);

			// extract end date
			unsigned int endMonth = std::stoi(util::nextEl(line));
			util::shiftEl(line);
			unsigned int endDay = std::stoi(util::nextEl(line));
			util::shiftEl(line);
			unsigned int endYear = std::stoi(line);
			util::shift(line);

			// extract end time
			unsigned int endHour = std::stoi(util::nextEl(line));
			util::shiftEl(line);
			unsigned int endMinute = std::stoi(line);
			DateTime end(endMonth, startDay, endYear, endHour, endMinute);
			util::shift(line);

			// extract style
			LayoutStyle layoutStyle = Event::stringToLayoutStyle(util::next(line));
			util::shift(line);

			// extract organizer ID and residency
			std::string organizerID = util::next(line);
			util::shift(line);

			// extract guest list
			std::string guestList = util::next(line);
			std::vector<std::string> guests;
			std::string guest;
			std::stringstream ss(guestList);
			while (std::getline(ss, guest, ',')) {
				guests.push_back(guest);
			}
			util::shift(line);

			// extract non-resident flag
			std::string nonResidentTickets = util::next(line);
			bool openToNonResidents = "true" == nonResidentTickets;
			util::shift(line);

			// the ticket cost is the field we use to determine if the event is public or private
			// if the conversion fails, the event is private
			std::shared_ptr<Event> event;
			try {
				// extract ticket cost
				int cost = std::stoi(line);

				// create a public event
				event = std::make_shared<PublicEvent>(
					name, start, end, layoutStyle, organizerID, cost, guests, openToNonResidents);
			} catch (std::exception&) {
				// create a private event
				event = std::make_shared<Event>(name, start, end, layoutStyle, organizerID);
			}

			// add the event to the manager
			this->manager.addEvent(event, currentUser.get()->hourLimit());
		}

	} catch (std::exception& e) { std::cout << ERROR << e.what() << RESET << std::endl; }

	// close the file
	calendarFile.close();
}

// Destructor
CommunityCenter::~CommunityCenter() {
	// write events to file
	std::ofstream calendarFile("./data/calendar.txt");
	if (!calendarFile.is_open()) {
		std::cout << ERROR << "Could not open calendar file: ./data/calendar.txt" << RESET
				  << std::endl;
		return;
	}

	// write the format of the file
	calendarFile << "Name;Start Date;Start Time;End Date;End Time;Style;Organizer ID;Organizer "
					"Residency;Guest List;Open to Non-Residents;Ticket Cost";

	// write each event to the file
	for (const std::shared_ptr<Event>& event : this->manager.getCalendar()) {
		calendarFile << "\n";
		// write the event to the file
		event.get()->writeToFile(calendarFile);
	}

	updateUserfile(*currentUser.get());

	// close the file
	calendarFile.close();
}

// Getters

// run the community center program
void CommunityCenter::run() {
	// print the welcome message
	std::cout << "Welcome to the Community Center!" << std::endl;

	// run the main menu
	this->mainMenu();
}

void CommunityCenter::initUser() {
	std::string username = " ";
	while (username.find(" ") != -1) {
		std::cout << "What's your username? (no spaces allowed)" << std::endl;
		std::cin >> username;
		std::cin.ignore();
	}

	// read users from file
	std::ifstream usersFile("./data/users.txt");
	if (!usersFile.is_open()) {
		throw std::runtime_error("Could not open users file: ./data/users.txt");
	}

	// read file anc catch any errors
	try {
		// first line holds the format of the file, print and ignore
		std::string line;
		std::getline(usersFile, line);

		// read the events from the file until the end
		while (std::getline(usersFile, line)) {
			// extract user name
			std::string name = util::next(line, ' ');
			util::shift(line, ' ');

			if (name.compare(username) == 0) {
				// extract balance
				unsigned int balance = std::stoi(util::next(line, ' '));
				util::shift(line, ' ');
				std::string residency = util::next(line, ' ');

				std::cout << "Welcome back " << username << std::endl;
				std::cout << "Your current balance is " << balance << std::endl;
				std::cout << name << " is a " << residency << std::endl;

				if (residency.compare("CITY") == 0) {
					this->currentUser = std::unique_ptr<User>(new City(username, balance));
				} else if (residency.compare("RESIDENT") == 0) {
					this->currentUser = std::unique_ptr<User>(new Resident(username, balance));
				} else if (residency.compare("NON_RESIDENT") == 0) {
					this->currentUser = std::unique_ptr<User>(new NonResident(username, balance));
				} else {
					throw std::runtime_error("Invalid residency status");
				}

				std::cout << "Your hourly rate is " << currentUser->hourlyRate() << std::endl;

				break;
			}
		}

		// close the file
		usersFile.close();

		if (this->currentUser.get() == NULL) {
			// No user was found, so creating new user
			std::cout << "Username not found, please add yourself to the system" << std::endl;

			char selected;
			while (selected != 'r' && selected != 'n') {
				std::cout << "What is your Residency Status?\n"
						  << HEADER << "   [r]" << RESET << "  for Resident\n"
						  << HEADER << "   [n]" << RESET << "  for Non-Resident" << std::endl;
				std::cin >> selected;
				std::cin.ignore();
			}
			if (selected == 'r') {
				this->currentUser = std::unique_ptr<User>(new Resident(username, 0));
			} else {
				this->currentUser = std::unique_ptr<User>(new NonResident(username, 0));
			}
		}

	} catch (std::exception& e) { std::cout << ERROR << e.what() << RESET << std::endl; }
}

void CommunityCenter::mainMenu() {
	bool running = true;
	while (running) {
		std::cout << "What would you like to do?\n"
				  << HEADER << "   [v]" << RESET << "  View Calendar\n"
				  << HEADER << "   [b]" << RESET << "  Buy Ticket\n"
				  << HEADER << "   [s]" << RESET << "  Schedule Event\n"
				  << HEADER << "   [w]" << RESET << "  Access Wallet\n"
				  << HEADER << "   [q]" << RESET << "  Quit" << std::endl;
		std::string input;
		getline(std::cin, input);
		char chosen = input[0];

		switch (chosen) {
			case 'v': this->manager.printCalendar(); break;
			case 'b': buyTicketMenu(); break;
			case 's': createEventMenu(); break;
			case 'w': currentUser->myWallet()->menu(); break;
			case 'q':
				std::cout << "Quitting now" << std::endl;
				running = false;
				break;
			default: std::cout << "Invalid Input" << std::endl;
		}
	}
}

void CommunityCenter::buyTicketMenu() {
	std::cout << HEADER << "Buying Ticket" << RESET << std::endl;
	DateTime eventTime;

	std::cout << "Enter the start and end time of the event you would like to purchase a ticket for"
			  << std::endl;

	std::pair<DateTime, DateTime> eventTimes = DateTime::readEventTimes();
}

void CommunityCenter::createEventMenu() {
	try {
		std::cout << HEADER << "Creating Event" << RESET << std::endl;
		char inputChar;

		// get event name
		std::string name;
		std::cout << "What is the name of the event?" << std::endl;
		std::getline(std::cin, name);

		// get event style
		LayoutStyle style;
		do {
			std::cout << "Select a layout style for the event:" << std::endl;
			std::cout << HEADER << "   [m]" << RESET << "  Meeting" << std::endl;
			std::cout << HEADER << "   [l]" << RESET << "  Lecture" << std::endl;
			std::cout << HEADER << "   [w]" << RESET << "  Wedding" << std::endl;
			std::cout << HEADER << "   [d]" << RESET << "  Dance" << std::endl;
			std::cin >> inputChar;
			std::cin.ignore();
		} while (inputChar != 'm' && inputChar != 'l' && inputChar != 'w' && inputChar != 'd');

		// get event public/private
		bool isPublic = false;
		do {
			std::cout << "What is the style of the event?\n"
					  << HEADER << "   [p]" << RESET << "  Public\n"
					  << HEADER << "   [r]" << RESET << "  Private" << std::endl;
			std::cin >> inputChar;
			std::cin.ignore();
		} while (inputChar != 'p' && inputChar != 'r');
		isPublic = inputChar == 'p';

		// if public event get more info
		unsigned int cost;
		bool openToNonResidents;
		if (isPublic) {
			// get event cost
			std::cout << "What is the cost of the event?" << std::endl;
			std::cin >> cost;
			std::cin.ignore();

			// get event guest list
			std::string guestList;
			std::cout << "Who is on the guest list? (comma separated)" << std::endl;
			std::getline(std::cin, guestList);

			// get event non-resident flag
			do {
				std::cout << "Is the event open to non-residents?\n"
						  << HEADER << "   [y]" << RESET << "  Yes\n"
						  << HEADER << "   [n]" << RESET << "  No" << std::endl;
				std::cin >> inputChar;
			} while (inputChar != 'y' && inputChar != 'n');

			openToNonResidents = inputChar == 'y';
		}

		// get event times
		std::pair<DateTime, DateTime> eventTimes = DateTime::readEventTimes();
		DateTime startTime = eventTimes.first;
		DateTime endTime = eventTimes.second;

		std::cout << "Event times: " << startTime << " - " << endTime << std::endl;

		// create event
		std::shared_ptr<Event> event;
		if (isPublic) {
			event = std::make_shared<PublicEvent>(
				name, startTime, endTime, style, currentUser->myID(), cost, openToNonResidents);
		} else {
			event = std::make_shared<Event>(name, startTime, endTime, style, currentUser->myID());
		}

		// print out event confirmation
		std::cout << "Confirm Event Details:" << std::endl << *event << std::endl;
		do {
			std::cout << "Does this look right?\n"
					  << HEADER << "   [y]" << RESET << "  Yes\n"
					  << HEADER << "   [n]" << RESET << "  No" << std::endl;
			std::cin >> inputChar;
		} while (inputChar != 'y' && inputChar != 'n');

		if (inputChar == 'n') {
			throw;
		}

		// get money from user
		int duration =
			(endTime.getHour() - startTime.getHour()) * 60 + endTime.getMin() - startTime.getMin();
		double eventRate = duration / 60 * currentUser->hourlyRate();

		// withdraw money from user
		try {
			currentUser->myWallet()->withdraw(eventRate);
		} catch (std::exception& e) {
			std::cout << ERROR << e.what() << RESET << std::endl;
			throw;
		}

		// add event to manager
		try {
			this->manager.addEvent(event, currentUser->hourLimit());
		} catch (std::exception& e) {
			std::cout << ERROR << e.what() << RESET << std::endl;

			// refund user
			std::cout << "Refunding" << std::endl;
			currentUser->myWallet()->deposit(eventRate);
			throw;
		}

	} catch (std::exception& e) {
		std::cout << ERROR << "Event creation cancelled" << RESET << std::endl;
		return;
	}
}

void updateUserfile(const User& user) {
	const char* inFileName = "./data/users.txt";
	const char* outileName = "./data/temp-users.txt";

	// write events to file
	std::ifstream usersFileInput(inFileName);
	if (!usersFileInput.is_open()) {
		std::cout << ERROR << "Could not open users file: ./data/users.txt" << RESET << std::endl;
		return;
	}

	std::ofstream usersFileOutput(outileName);
	if (!usersFileInput.is_open()) {
		std::cout << ERROR << "Could not open users file: ./data/users.txt" << RESET << std::endl;
		return;
	}

	try {
		// first line holds the format of the file, print and ignore
		std::string line;
		std::getline(usersFileInput, line);
		usersFileOutput << line;
		bool userNotFound = true;

		// read the events from the file until the end
		while (std::getline(usersFileInput, line)) {
			usersFileOutput << "\n";

			// extract user name
			std::string name = util::next(line, ' ');

			if (name.compare(user.myID()) == 0) {
				user.writeToFile(usersFileOutput);
				userNotFound = false;
			} else {
				usersFileOutput << line;
			}
		}

		if (userNotFound) {
			usersFileOutput << "\n";
			user.writeToFile(usersFileOutput);
		}

		// close the files
		usersFileInput.close();
		usersFileOutput.close();

		int fail = remove(inFileName);
		if (fail != 0) {
			throw std::runtime_error("Couldn't remove old users file");
		}
		fail = rename(outileName, inFileName);
		if (fail != 0) {
			throw std::runtime_error("Couldn't rename new users file");
		}
	} catch (std::exception& e) { std::cout << ERROR << e.what() << RESET << std::endl; }
}
