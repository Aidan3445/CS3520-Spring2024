#include "../include/communityCenter.hpp"
#include "../include/colorCodes.hpp"
#include <fstream>
#include <string>

// helper to get the next field
std::string next(std::string& line) {
	std::string field = line.substr(0, line.find(';'));
	return field;
}
// helper to get the next element in a list
std::string nextEl(std::string& line) {
	std::string field = line.substr(0, line.find(','));
	return field;
}
// helper to shift the line
void shift(std::string& line) { line = line.substr(line.find(';') + 1); }
// helper to shift the line for elements
void shiftEl(std::string& line) { line = line.substr(line.find(',') + 1); }

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
			std::string name = next(line);
			shift(line);

			// extract start date
			unsigned int startMonth = std::stoi(nextEl(line));
			shiftEl(line);
			unsigned int startDay = std::stoi(nextEl(line));
			shiftEl(line);
			unsigned int startYear = std::stoi(line);
			shift(line);

			// extract start time
			unsigned int startHour = std::stoi(nextEl(line));
			shiftEl(line);
			unsigned int startMinute = std::stoi(line);
			DateTime start(startMonth, startDay, startYear, startHour, startMinute);
			shift(line);

			// extract end date
			unsigned int endMonth = std::stoi(nextEl(line));
			shiftEl(line);
			unsigned int endDay = std::stoi(nextEl(line));
			shiftEl(line);
			unsigned int endYear = std::stoi(line);
			shift(line);

			// extract end time
			unsigned int endHour = std::stoi(nextEl(line));
			shiftEl(line);
			unsigned int endMinute = std::stoi(line);
			DateTime end(endMonth, startDay, endYear, endHour, endMinute);
			shift(line);

			// extract style
			LayoutStyle layoutStyle = Event::stringToLayoutStyle(next(line));
			shift(line);

			// extract organizer ID and residency
			std::string organizerID = next(line);
			shift(line);
			ResidencyStatus residency = User::stringToResidencyStatus(next(line));
			shift(line);

			// extract guest list
			std::string guestList = next(line);
			std::vector<std::string> guests;
			std::string guest;
			std::stringstream ss(guestList);
			while (std::getline(ss, guest, ',')) {
				guests.push_back(guest);
			}
			shift(line);

			// extract non-resident flag
			std::string nonResidentTickets = next(line);
			bool openToNonResidents = "true" == nonResidentTickets;
			shift(line);

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

	// close the file
	calendarFile.close();
}

// Getters

// run the community center program
void CommunityCenter::run() {
	// print the welcome message
	std::cout << "Welcome to the Community Center!" << std::endl;

	this->manager.printCalendar();

	// run the main menu
	// this->mainMenu();
}
