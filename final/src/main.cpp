#include "../include/dateTime.hpp"
#include "../include/facilityManager.hpp"
#include <memory>

int main() {
	FacilityManager fm;

	auto e1 = std::make_unique<Event>("AI Ethics",
									  DateTime(4, 15, 2024, 10, 0),
									  DateTime(4, 15, 2024, 14, 0),
									  LayoutStyle::LECTURE,
									  "John Doe",
									  ResidencyStatus::RESIDENT);

	auto e2 = std::make_unique<PublicEvent>("Dodgeball Tournament",
											DateTime(1, 1, 2024, 9, 30),
											DateTime(1, 1, 2024, 14, 0),
											LayoutStyle::DANCE,
											"Aidan Weinberg",
											ResidencyStatus::RESIDENT,
											5,
											true);

	auto e3 = std::make_unique<PublicEvent>("Model UN",
											DateTime(4, 15, 2024, 15, 30),
											DateTime(4, 15, 2024, 20, 0),
											LayoutStyle::MEETING,
											"Jeanie Barr",
											ResidencyStatus::NON_RESIDENT,
											150,
											false);

	auto e4 = std::make_unique<Event>("Mushroom Convention",
									  DateTime(1, 6, 2024, 9, 30),
									  DateTime(1, 6, 2024, 14, 0),
									  LayoutStyle::DANCE,
									  "Noah Young",
									  ResidencyStatus::RESIDENT);

	try {
		fm.addEvent(std::move(e1));
		fm.addEvent(std::move(e2));
		fm.addEvent(std::move(e3));
		fm.addEvent(std::move(e4));
	} catch (std::runtime_error& e) {
		std::cout << "\033[41m" << e.what() << "\033[0m" << std::endl;
	}

	fm.printCalendar();
}
