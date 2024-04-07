#include "../include/vault.hpp"

int main() {
	// make a vault
	SuperUltraSecureVault<int> vault = SuperUltraSecureVault<int>();

	// create some items
	std::unique_ptr<Item<int>> item1 =
		std::make_unique<Item<int>>(Item<int>(1, 1, 10, "One", "Aidan"));
	std::unique_ptr<Item<int>> item2 =
		std::make_unique<Item<int>>(Item<int>(2, 2, 20, "Two", "Noah"));

	// add the item to the vault
	vault.add_item(std::move(item1));

	// simulate the passage of time
	vault.pass_time(1);

	// add the second item to the vault
	vault.add_item(std::move(item2));

	// simulate the passage of time
	vault.pass_time(10);

	// add the third and fourth item to the vault
	std::vector<std::unique_ptr<Item<int>>> next_items;
	next_items.push_back(std::make_unique<Item<int>>(Item<int>(3, 3, 30, "Three", "Liam")));
	next_items.push_back(std::make_unique<Item<int>>(Item<int>(4, 4, 40, "Four", "Olivia")));
	vault.add_item(next_items.begin(), next_items.end());

	// get the age of an item with ID 2
	std::cout << "Age of item with ID 2: " << vault.get_age_of_item(2) << std::endl;

	// remove the first item from the vault
	std::unique_ptr<Item<int>> removed_item1 = vault.remove_item();

	// remove 2 items from the vault
	std::vector<std::unique_ptr<Item<int>>> removed_items = vault.remove_item(2);

	// simulate the passage of time
	vault.pass_time(5);

	// reinsert the first item
	vault.add_item(std::move(removed_item1));

	// get the age of an item no longer in the vault
	std::cout << "Age of item with ID 3: " << vault.get_age_of_item(3) << std::endl;

	// get the age of re-inserted item
	std::cout << "Age of re-inserted item with ID 1: " << vault.get_age_of_item(1) << std::endl;

	// remove the remaining items
	vault.remove_item(vault.get_number_of_items());

	// try removing items even though the vault is empty
	vault.remove_item();

	return 0;
}
