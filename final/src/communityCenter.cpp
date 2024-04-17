#include "../include/communityCenter.hpp"
#include "../include/utility.hpp"
#include <fstream>
#include <string>
#include <regex>
#include "communityCenter.hpp"

// helper for updating user text file
void updateUserfile(const User &user);

// Constructor
CommunityCenter::CommunityCenter() {
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
			ResidencyStatus residency = User::stringToResidencyStatus(util::next(line));
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
				event = std::make_shared<PublicEvent>(name,
													  start,
													  end,
													  layoutStyle,
													  organizerID,
													  residency,
													  cost,
													  guests,
													  openToNonResidents);
			} catch (std::exception&) {
				// create a private event
				event =
					std::make_shared<Event>(name, start, end, layoutStyle, organizerID, residency);
			}

			// add the event to the manager
			this->manager.addEvent(event);
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

	login();

	// run the main menu
	this->mainMenu();
}

void CommunityCenter::login() {
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
				ResidencyStatus residency = User::stringToResidencyStatus(util::next(line, ' '));
				
				this->currentUser = std::unique_ptr<User>(new User(name, residency, balance));
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
						<< "type [r] for Resident\n"
						<< "type [n] for Non-Resident" << std::endl;
				std::cin >> selected;
				std::cin.ignore();
			}
			ResidencyStatus residency = selected == 'r' ? ResidencyStatus::RESIDENT : ResidencyStatus::NON_RESIDENT;
			this->currentUser = std::unique_ptr<User>(new User(username, residency, 0));
		}

	} catch (std::exception& e) { std::cout << ERROR << e.what() << RESET << std::endl; }
	
}

void CommunityCenter::mainMenu() {
	bool running = true;
	while (running) {
		std::cout << "What would you like to do?\n"
				<< "   [v]  View Calendar\n"
				<< "   [b]  Buy Ticket\n"
				<< "   [s]  Schedule Event\n"
				<< "   [q]  Quit" << std::endl;
		std::string input;
		getline(std::cin, input);
		char chosen = input[0];

		switch (chosen) {
			case 'v':
				this->manager.printCalendar();
				break;
			case 'b':
				buyTicketMenu();
				break;
			case 's':
				createEventMenu();
				break;
			case 'q':
				std::cout << "Quitting now" << std::endl;
				running = false;
				break;
			default:
				std::cout << "Invalid Input" << std::endl;
		}
	}
}

void CommunityCenter::buyTicketMenu() {

}

void CommunityCenter::createEventMenu() {
	try {
    	DateTime startTime = DateTime::readDateTime("start");
		DateTime endTime = DateTime::readDateTime("end");
	}
	catch(std::exception& e) {
		// Does nothing, since user exited
		return;
	}
}

void updateUserfile(const User &user)
{
    const char* inFileName = "./data/users.txt";
	const char* outileName = "./data/temp-users.txt";

	// write events to file
	std::ifstream usersFileInput(inFileName);
	if (!usersFileInput.is_open()) {
		std::cout << ERROR << "Could not open users file: ./data/users.txt" << RESET
				  << std::endl;
		return;
	}

	std::ofstream usersFileOutput(outileName);
	if (!usersFileInput.is_open()) {
		std::cout << ERROR << "Could not open users file: ./data/users.txt" << RESET
				  << std::endl;
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
			}
			else {
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