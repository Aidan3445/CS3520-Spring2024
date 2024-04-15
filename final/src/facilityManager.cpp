#include "../include/facilityManager.hpp"
#include <algorithm>

// add event to the calendar
// throws an error if the event can't be added for any reason below:
// - the event time is taken
// - this event will cause user to have more than the allowed number of hours in a week
//          - 24 hours/week for residents and non-residents
//          - 48 hours/week for the city
void FacilityManager::addEvent(std::unique_ptr<Event> newEvent) {
	// check if the event time is taken
	if (std::find_if(
			calendar.begin(), calendar.end(), [&newEvent](const std::unique_ptr<Event>& event) {
				// three cases for conflict of event times:
				// 1. new event starts during an existing event
				bool c1 = event.get()->getStartTime() <= newEvent.get()->getStartTime() &&
						  newEvent.get()->getStartTime() <= event.get()->getEndTime();
				// 2. new event stars before and ends after an existing event
				bool c2 = event.get()->getEndTime() >= newEvent.get()->getStartTime() &&
						  event.get()->getEndTime() <= newEvent.get()->getEndTime();
				// 3. new event ends during an existing event
				bool c3 = newEvent.get()->getEndTime() >= event.get()->getStartTime() &&
						  newEvent.get()->getEndTime() <= event.get()->getEndTime();

				return c1 || c2 || c3;
			}) != calendar.end()) {
		throw std::runtime_error("Event time is taken.");
	}

	// check if the user has more than the allowed number of hours in a week
	// 24 hours/week for residents and non-residents
	// 48 hours/week for the city
	std::string id = newEvent.get()->getOrganizer().first;

	int minutes;
	if (newEvent.get()->getOrganizer().second == ResidencyStatus::CITY) {
		minutes = 48 * 60;
	} else {
		minutes = 24 * 60;
	}

	std::for_each(calendar.begin(),
				  calendar.end(),
				  [&minutes, &id, &newEvent](const std::unique_ptr<Event>& event) {
					  if (event.get()->getOrganizer().first == id &&
						  event.get()->getStartTime().sameWeek(newEvent.get()->getStartTime())) {
						  DateTime start = event.get()->getStartTime();
						  DateTime diff = event.get()->getEndTime().sub(start.getMonth(), start.getDay(), start.getYear(), start.getHour(), start.getMin());
						  minutes -= diff.getHour() * 60;
						  minutes -= diff.getMin();
					  }
				  });

	if (minutes < 0) {
		throw std::runtime_error("You have more than allowed number of hours in a week");
	}

	// if all checks pass then add the event to the calendar
	calendar.insert(std::move(newEvent));
}

// remove event from the calendar
// throws an error only if the event cannot be found
void FacilityManager::removeEvent(const DateTime& startingFrom) {
	auto it = std::find_if(
		calendar.begin(), calendar.end(), [&startingFrom](const std::unique_ptr<Event>& event) {
			return event.get()->getStartTime() == startingFrom;
		});

	if (it == calendar.end()) {
		throw std::runtime_error("Event not found.");
	}

	calendar.erase(it);
}

// print the calendar
//
/*

Week: 4/14/2024 - 4/20/2024
--------------------------------
Monday 4/15/2024:
	Dodgeball Tournament: 10:00 - 14:00 (Tickets: $10, Organizer: John Doe)
	Yoga Class: 15:00 - 16:00 (Organizer: Jane Doe)
Thursday 4/18/2024:
	Chess Tournament: 12:00 - 16:00 (Tickets: $5, Organizer: John Doe)
--------------------------------

enter p to see the previous week, n to see the next week, or q to quit:
 * */
void FacilityManager::printCalendar() const {
	// if the calendar is empty, print a message and return
	if (calendar.empty()) {
		std::cout << "Calendar is empty" << std::endl;
		return;
	}

	// get the first day of the week for the first event
	DateTime firstDayOfWeek = (*calendar.begin())->getStartTime().getFirstDayOfWeek();
	auto firstEventOfWeekIt = calendar.begin();
	char input;

	// print loop
	do {
		// print the week
		std::cout << "Week: " << firstDayOfWeek << " - " << firstDayOfWeek.add(0, 6)
				  << std::endl;
		std::cout << "--------------------------------" << std::endl;
		auto currentEventIt = firstEventOfWeekIt;
		DateTime dayOfWeek = firstDayOfWeek.sub(0, 1);
		while (currentEventIt != calendar.end() &&
			   (*currentEventIt).get()->getStartTime().sameWeek(firstDayOfWeek)) {
			// if this day is different from the previous day, print the day
			if ((*currentEventIt).get()->getStartTime().getDay() != dayOfWeek.getDay()) {
				dayOfWeek = (*currentEventIt).get()->getStartTime();
				std::cout << dayOfWeek.getDayOfWeek() << ":" << std::endl;
			}

			std::cout << "    " << *currentEventIt->get() << std::endl;
			currentEventIt++;
		}
		std::cout << "--------------------------------" << std::endl << std::endl;

		// if iterator is the end of the calendar, break
		if (currentEventIt == calendar.end()) {
			std::cout << "End of calendar" << std::endl;
			break;
		}

		// validate user input
		do {
			std::cout << "enter n to see the next week or q to quit: ";
			std::cin >> input;
		} while (input != 'q' && input != 'n');

		// update the iterators
	} while (input != 'q');
}
// print the events
