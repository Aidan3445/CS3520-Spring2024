#include "../include/dateTime.hpp"
#include "../include/facilityManager.hpp"
#include <memory>

int main() {
	DateTime d(4, 15, 2024, 14, 23);

	std::cout << d << std::endl;

	DateTime d2(4, 20, 2024, 20, 0);

	std::cout << d2 << std::endl;

	std::cout << d2.sameWeek(d) << std::endl;

	DateTime d3(4, 21, 2024, 20, 0);

	std::cout << d3 << std::endl;

	std::cout << d.sameWeek(d3) << std::endl;

	std::cout << (d3 <= d3) << std::endl;

	FacilityManager fm;

	auto e1 = std::make_unique<Event>(DateTime(4, 15, 2024, 10, 0),
									  DateTime(4, 15, 2024, 14, 0),
									  LayoutStyle::LECTURE,
									  "John Doe",
									  ResidencyStatus::RESIDENT);

	fm.addEvent(std::move(e1));

	fm.printCalendar();
}
