#include "../include/facilityManager.hpp"
#include "../include/utility.hpp"

// get events for a user
std::set<std::shared_ptr<Event>, EventComparator>
	FacilityManager::getUserEvents(const std::string& userID) {
	std::set<std::shared_ptr<Event>, EventComparator> userEvents;

	// iterate through the calendar and add the events to the userEvents set
	std::for_each(calendar.begin(),
				  calendar.end(),
				  [&userEvents, &userID](const std::shared_ptr<Event>& event) {
					  if (event.get()->getOrganizer() == userID) {
						  userEvents.insert(event);
					  }
				  });

	return userEvents;
}

// get tickets for a user
std::set<std::shared_ptr<Event>, EventComparator>
	FacilityManager::getUserTickets(const std::string& userID) {
	std::set<std::shared_ptr<Event>, EventComparator> userTickets;

	// iterate through the calendar and add the events to the userTickets set
	std::for_each(calendar.begin(),
				  calendar.end(),
				  [&userTickets, &userID](const std::shared_ptr<Event>& event) {
					  int count = event.get()->userInGuestListCount(userID);
					  for (int i = 0; i < count; i++) {
						  if (i == 0) {
							  userTickets.insert(event);
						  } else {
							  // Makes a temp copy of the event with a different name to show that
							  // you have multiple tickets
							  Event getEvent = *event.get();
							  userTickets.insert(std::shared_ptr<Event>(
								  new Event(getEvent.getName() + std::to_string(i + 1),
											getEvent.getStartTime(),
											getEvent.getEndTime(),
											getEvent.getStyle(),
											getEvent.getOrganizer())));
						  }
					  }
				  });

	return userTickets;
}

// get all events
std::set<std::shared_ptr<Event>, EventComparator>& FacilityManager::getCalendar() {
	return calendar;
}

// get single event from the calendar
std::shared_ptr<Event> FacilityManager::getEvent(const DateTime& startingFrom) {
	auto it = std::find_if(
		calendar.begin(), calendar.end(), [&startingFrom](const std::shared_ptr<Event>& event) {
			return event.get()->getStartTime() == startingFrom;
		});

	if (it == calendar.end()) {
		throw std::runtime_error("Event not found.");
	}
	return *it;
}

// add event to the calendar
// throws an error if the event can't be added for any reason below:
// - the event time is taken
// - this event will cause user to have more than the allowed number of hours in a week
//          - 24 hours/week for residents and non-residents
//          - 48 hours/week for the city
void FacilityManager::addEvent(const std::shared_ptr<Event>& newEvent, const int& hourlyLimit) {
	// check if the event time is taken
	if (std::find_if(
			calendar.begin(), calendar.end(), [&newEvent](const std::shared_ptr<Event>& event) {
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
	std::string id = newEvent.get()->getOrganizer();

	int minutes = 60 * hourlyLimit;

	std::for_each(calendar.begin(),
				  calendar.end(),
				  [&minutes, &id, &newEvent](const std::shared_ptr<Event>& event) {
					  if (event.get()->getOrganizer() == id &&
						  event.get()->getStartTime().sameWeek(newEvent.get()->getStartTime())) {
						  DateTime start = event.get()->getStartTime();
						  DateTime diff = event.get()->getEndTime().sub(start.getMonth(),
																		start.getDay(),
																		start.getYear(),
																		start.getHour(),
																		start.getMin());
						  minutes -= diff.getHour() * 60;
						  minutes -= diff.getMin();
					  }
				  });

	if (minutes < 0) {
		throw std::runtime_error("You have more than allowed number of hours in a week");
	}

	// if all checks pass then add the event to the calendar
	calendar.insert(newEvent);
}

// remove event from the calendar
// throws an error only if the event cannot be found
void FacilityManager::removeEvent(const DateTime& startingFrom) {
	auto it = std::find_if(
		calendar.begin(), calendar.end(), [&startingFrom](const std::shared_ptr<Event>& event) {
			return event.get()->getStartTime() == startingFrom;
		});

	if (it == calendar.end()) {
		throw std::runtime_error("Event not found.");
	}

	calendar.erase(it);
}

// helper to print events in a set
void printEvents(const std::set<std::shared_ptr<Event>, EventComparator>& events) {
	// if the events is empty, print a message and return
	if (events.empty()) {
		std::cout << ERROR << "Calendar is empty" << RESET << std::endl;
		return;
	}

	// get the first day of the week for the first event
	DateTime firstDayOfWeek = (*events.begin())->getStartTime().getFirstDayOfWeek();
	auto firstEventOfWeekIt = events.begin();
	char input;

	// print loop
	do {
		// print the week
		std::cout << "Week: " << firstDayOfWeek.getDate() << " - "
				  << firstDayOfWeek.add(0, 6).getDate() << std::endl;
		std::cout << "--------------------------------" << std::endl;
		auto currentEventIt = firstEventOfWeekIt;
		DateTime dayOfWeek = firstDayOfWeek.sub(0, 1);
		while (currentEventIt != events.end() &&
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

		// if iterator is the end of the events, break
		if (currentEventIt == events.end()) {
			std::cout << CLEAR_LINE << ERROR << "End of calendar" << RESET << std::endl
					  << std::endl;
			break;
		}

		// validate user input
		do {
			std::cout << "Would you like to see next week" << std::endl;
			std::cout << HEADER << "   [n]" << RESET << "  Next week" << std::endl;
			std::cout << HEADER << "   [e]" << RESET << "  Exit" << std::endl;
			std::cin >> input;
			std::cin.ignore();
			// delete line
			std::cout << CLEAR_LINE;
		} while (input != 'e' && input != 'n');

		// update the iterators
		if (input == 'n') {
			firstDayOfWeek = (*currentEventIt)->getStartTime().getFirstDayOfWeek();
			firstEventOfWeekIt = currentEventIt;
		}
	} while (input != 'e');
}

// print the calendar
void FacilityManager::printCalendar() const {
	std::cout << HEADER << "Events Calendar" << RESET << std::endl;
	printEvents(calendar);
}

// print the events for a user
void FacilityManager::printUserEvents(const std::string& id) {
	std::cout << HEADER << "Events organized by " << id << RESET << std::endl;
	std::set<std::shared_ptr<Event>, EventComparator> userEvents = getUserEvents(id);
	printEvents(userEvents);
}

// print the tickets for a user
void FacilityManager::printUserTickets(const std::string& id) {
	std::cout << HEADER << "Tickets purchased by " << id << RESET << std::endl;
	std::set<std::shared_ptr<Event>, EventComparator> userTickets = getUserTickets(id);
	printEvents(userTickets);
}

std::set<std::shared_ptr<Event>>
	FacilityManager::getAllEventsBetween(std::pair<DateTime, DateTime> interval) {
	std::set<std::shared_ptr<Event>> events;
	for_each(calendar.begin(), calendar.end(), [&events, &interval](std::shared_ptr<Event> e) {
		if ((e.get()->getStartTime() <= interval.first &&
			 interval.first <= e.get()->getStartTime()) ||
			(e.get()->getStartTime() <= interval.second &&
			 interval.second <= e.get()->getStartTime()) ||
			(interval.first <= e.get()->getStartTime() &&
			 e.get()->getStartTime() <= interval.second)) {
			events.insert(e);
		}
	});
	return events;
}
