#include "../include/communityCenter.hpp"
#include "../include/facilityManager.hpp"
#include <memory>

int main() {
	CommunityCenter cc;

	cc.run();
	return 0;
}

int testFM() {
	FacilityManager fm;

	auto e1 = std::make_shared<PrivateEvent>("AI Ethics",
											 DateTime(4, 15, 2024, 10, 0),
											 DateTime(4, 15, 2024, 14, 0),
											 LayoutStyle::LECTURE,
											 "John Doe",
											 ResidencyStatus::RESIDENT);

	auto e2 = std::make_shared<PublicEvent>("Dodgeball Tournament",
											DateTime(1, 1, 2024, 9, 30),
											DateTime(1, 1, 2024, 14, 0),
											LayoutStyle::DANCE,
											"Aidan Weinberg",
											ResidencyStatus::RESIDENT,
											5,
											true);

	auto e3 = std::make_shared<PublicEvent>("Model UN Day 1",
											DateTime(4, 15, 2024, 15, 30),
											DateTime(4, 15, 2024, 20, 0),
											LayoutStyle::MEETING,
											"Jeanie Barr",
											ResidencyStatus::NON_RESIDENT,
											150,
											false);

	auto e4 = std::make_shared<PrivateEvent>("Mushroom Convention",
											 DateTime(1, 6, 2024, 9, 30),
											 DateTime(1, 6, 2024, 14, 0),
											 LayoutStyle::DANCE,
											 "Noah Young",
											 ResidencyStatus::RESIDENT);

	auto e5 = std::make_shared<PublicEvent>("Model UN Day 2",
											DateTime(4, 16, 2024, 15, 30),
											DateTime(4, 16, 2024, 20, 0),
											LayoutStyle::MEETING,
											"Jeanie Barr",
											ResidencyStatus::NON_RESIDENT,
											150,
											false);

	try {
		fm.addEvent(e1);
		fm.addEvent(e2);
		fm.addEvent(e3);
		fm.addEvent(e4);
		fm.addEvent(e5);
	} catch (std::runtime_error& e) {
		std::cout << "\033[41m" << e.what() << "\033[0m" << std::endl;
	}

	fm.printCalendar();

	fm.printUserEvents("Jeanie Barr");

	try {
		fm.removeEvent(e5.get()->getStartTime());
	} catch (std::runtime_error& e) {
		std::cout << "\033[41m" << e.what() << "\033[0m" << std::endl;
	}

	User u1("Aidan Weinberg", ResidencyStatus::RESIDENT, 200);
	e3.get()->purchaseTicket(u1);
	fm.printUserTickets(u1.myID());
	e5.get()->purchaseTicket(u1);


	fm.printCalendar();

	return 0;
}
