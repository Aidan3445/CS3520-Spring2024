#include "../include/vault.hpp"
#include "test_objects.hpp"

int main() {
	// [Int Vault]
	std::cout << "[Int Vault]" << endl;

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
	std::cout << "Age of item with ID 3: " << vault.get_age_of_item(3) 
			  << "| Should be -1, since there is no item with an ID of 3" << std::endl;

	// get the age of re-inserted item
	std::cout << "Age of re-inserted item with ID 1: " << vault.get_age_of_item(1) << std::endl;

	// remove the remaining items
	vault.remove_item(vault.get_number_of_items());

	// try removing items even though the vault is empty
	vault.remove_item();



	// [String Vault]
	std::cout << "[String Vault]" << endl;

	// make a vault
	SuperUltraSecureVault<string> string_vault = SuperUltraSecureVault<string>();

	// create some items
	std::unique_ptr<Item<string>> str1 =
		std::make_unique<Item<string>>(Item<string>(
			"Important!!!", 1, 0, "Especially Important", "Liam"));
	std::unique_ptr<Item<string>> str2 =
		std::make_unique<Item<string>>(Item<string>(
			"Not that important", 2, 10, "Maybe Later", "Olivia"));
	
	// add them to the vault
	string_vault.pass_time(2);
	string_vault.add_item(std::move(str1));
	string_vault.pass_time(4);
	string_vault.add_item(std::move(str2));

	// make list of items to add
	std::vector<std::unique_ptr<Item<string>>> next_items_string;
	next_items_string.push_back(std::make_unique<Item<string>>(Item<string>("", 3, 0, "Empty", "Liam")));
	next_items_string.push_back(std::make_unique<Item<string>>(Item<string>("Olivia", 4, 35, "Name", "Olivia")));
	string_vault.add_item(next_items_string.begin(), next_items_string.end());

	// remove the first item from the vault
	string_vault.pass_time(3);
	std::unique_ptr<Item<string>> removed_str1 = string_vault.remove_item();

	// remove 0 items from the vault
	string_vault.pass_time(1);
	std::vector<std::unique_ptr<Item<string>>> no_removed_strs = string_vault.remove_item(0);

	// remove 2 items from the vault
	string_vault.pass_time(2);
	std::vector<std::unique_ptr<Item<string>>> removed_strs = string_vault.remove_item(2);

	// Update the last item in the vault
	string_vault.pass_time(1);
	std::unique_ptr<Item<string>> str_updated =
		std::make_unique<Item<string>>(Item<string>(
			"Olivia Olivia", 4, 10, "Full Name", "Olivia"));
	string_vault.add_item(std::move(str_updated));

	// remove the final item from the vault
	string_vault.pass_time(3);
	std::unique_ptr<Item<string>> last_removed_str = string_vault.remove_item();


	
	// [Book Vault]
	std::cout << "[Book Vault]" << endl;

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

	// get the age of an item that is not in the vault (to get a value of -1)
	std::cout << "Age of item with ID 10: " << book_vault.get_age_of_item(10) 
			  << "| Should be -1, since there is no item with an ID of 10" << std::endl;

	// remove the first item from the vault
	std::unique_ptr<Item<Book>> removed_book1 = book_vault.remove_item();

	// remove 2 items from the vault
	std::vector<std::unique_ptr<Item<Book>>> removed_books = book_vault.remove_item(2);



	// [AccountInfo Vault]
	std::cout << "[AccountInfo Vault]" << endl;

	// make a vault
	SuperUltraSecureVault<AccountInfo> login_vault = SuperUltraSecureVault<AccountInfo>();

	// create some items
	vector<std::unique_ptr<Item<AccountInfo>>> list_acc = vector<std::unique_ptr<Item<AccountInfo>>>();
	list_acc.push_back(std::make_unique<Item<AccountInfo>>(Item<AccountInfo>(
			AccountInfo("user", "unguessable", "my-site.com"), 1, 2, "User: My-Site", "User")));
	list_acc.push_back(std::make_unique<Item<AccountInfo>>(Item<AccountInfo>(
			AccountInfo("second", "really-first", "second.org"), 2, 400, "Second: Second.org", "Second")));
	list_acc.push_back(std::make_unique<Item<AccountInfo>>(Item<AccountInfo>(
			AccountInfo("third", "password", "third.org"), 3, 399, "Third: third.org", "Third")));
	
	vault.pass_time(2);
	
	// adds all items
	login_vault.add_item(list_acc.begin(), list_acc.end());

	// create single item
	std::unique_ptr<Item<AccountInfo>> acc1 =
		std::make_unique<Item<AccountInfo>>(Item<AccountInfo>(
			AccountInfo("DefinitelyMyLogin@c++.com", "Y0uCan9uessTh1s0ne", "Mail"), 20, 1, "Mail", "Noah"));
	std::unique_ptr<Item<AccountInfo>> acc2 =
		std::make_unique<Item<AccountInfo>>(Item<AccountInfo>(
			AccountInfo("SuperReal@c++.com", "TryA9ain1n0neH0UR", "Mail"), 24, 99, "Mail", "Aidan"));

	// add the items to the vault
	login_vault.add_item(std::move(acc1));
	vault.pass_time(4);
	login_vault.add_item(std::move(acc2));
	vault.pass_time(3);

	// get the age of an item with ID 20
	std::cout << "Age of item with ID 20: " << book_vault.get_age_of_item(20) << std::endl;

	// get the age of an item with ID 24
	std::cout << "Age of item with ID 24: " << book_vault.get_age_of_item(24) << std::endl;

	// get the age of an item with ID 3
	std::cout << "Age of item with ID 3: " << book_vault.get_age_of_item(3) << std::endl;

	// get the age of an item with ID -1
	std::cout << "Age of item with ID -1: " << book_vault.get_age_of_item(-1)
			  << "| Should be -1, since there is no item with an ID of 10" << std::endl;

	// remove all items from the vault
	std::vector<std::unique_ptr<Item<AccountInfo>>> removed_accs = login_vault.remove_item(5);

	// prints vault is empty 3 times, since there are no more items in the vault
	login_vault.remove_item(3);

	return 0;
}
