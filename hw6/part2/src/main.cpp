#include "../include/vault.hpp"
#include "test_objects.hpp"

int main() {
	// [Int Vault]

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



	// [Book Vault]

	// make a vault
	SuperUltraSecureVault<Book> book_vault = SuperUltraSecureVault<Book>();

	// create some items
	std::unique_ptr<Item<Book>> book1 =
		std::make_unique<Item<Book>>(Item<Book>(
			Book("The Hitchhiker's Guide to the Galaxy", 224), 1, 15, "HGttG", "Amazon"));
	std::unique_ptr<Item<Book>> book2 =
		std::make_unique<Item<Book>>(Item<Book>(
			Book("Harry Potter and the Sorcerer's Stone", 198), 2, 23, "HP1", "Barnes & Noble"));
	std::unique_ptr<Item<Book>> book3 =
		std::make_unique<Item<Book>>(Item<Book>(
			Book("How to Program 2-day", 98), 3, 96, "P2D", "Campus Shop"));

	// add the item to the vault
	book_vault.add_item(std::move(book1));

	// simulate the passage of time
	book_vault.pass_time(20);

	// add the second item to the vault
	book_vault.add_item(std::move(book2));

	// simulate the passage of time
	book_vault.pass_time(12);

	// Add another book
	book_vault.add_item(std::move(book3));

	// get the age of an item with ID 1
	std::cout << "Age of item with ID 1: " << book_vault.get_age_of_item(1) << std::endl;

	// remove the first item from the vault
	std::unique_ptr<Item<Book>> removed_book1 = book_vault.remove_item();

	// remove 2 items from the vault
	std::vector<std::unique_ptr<Item<Book>>> removed_books = book_vault.remove_item(2);



	// [AccountInfo Vault]

	// make a vault
	SuperUltraSecureVault<AccountInfo> login_vault = SuperUltraSecureVault<AccountInfo>();

	// create some items
	vector<std::unique_ptr<Item<AccountInfo>>> list_acc =
		{ 
			std::make_unique<Item<AccountInfo>>(Item<AccountInfo>(
			AccountInfo("user", "unguessable", "my-site.com"), 1, 2, "User: My-Site", "User")), 

			std::make_unique<Item<AccountInfo>>(Item<AccountInfo>(
			AccountInfo("second", "really-first", "second.org"), 2, 400, "Second: Second.org", "Second")), 

			std::make_unique<Item<AccountInfo>>(Item<AccountInfo>(
			AccountInfo("third", "password", "third.org"), 2, 400, "Third: third.org", "Third")) 
		};
	
	vault.pass_time(2);
	
	// adds all items
	login_vault.add_item(list_acc.begin(), list_acc.end());

	return 0;
}
