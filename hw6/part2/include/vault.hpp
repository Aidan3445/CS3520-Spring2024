#ifndef VAULT_HPP
#define VAULT_HPP

#include "age.hpp"
#include "item.hpp"
#include <algorithm>
#include <deque>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

template<typename T>
class SuperUltraSecureVault {
  private:
	// internal time/age of the vault
	static Age age;

	// super ultra secure items (you can see them but you can't touch them)
	// pair of item and date added to the vault
	std::deque<std::pair<std::unique_ptr<Item<T>>, int>> items;

	// helper for inserting/updating items
	void insert_item(std::unique_ptr<Item<T>> item) {
		// if the item is already in the vault, remove it and add it again with the updated date
		auto item_pair = find_pair(item.get()->get_id());

		if (item_pair.first) {
			// remove the item from the vault
			std::remove_if(items.begin(), items.end(),
							[&item_pair](const auto& pair) {
								return pair.first.get() == item_pair.first.get();
							});
			items.pop_back(); // Now empty because remove_if will remove 1 element
			// re-insert the item to the vault
			insert_item(std::move(item));
		} else {
			// if the item is not in the vault, add it
			items.push_back({std::move(item), age.get_time()});
		}
	}

	// helper to find an item-date pair in the vault
	std::pair<std::unique_ptr<Item<T>>, int> find_pair(int item_id) {
		auto it = std::find_if(items.begin(), items.end(), [&](const auto& pair) {
			return pair.first->get_id() == item_id;
		});

		if (it != items.end()) {
			// return the pair
			return {std::move(it->first), it->second};
		}

		return {nullptr, -1};
	}

  public:
	// simulate the passage of time
	static void pass_time() { ++age; }
	static void pass_time(int time) {
		for (int i = 0; i < time; i++) {
			pass_time();
		}
	}

	// add item(s) to the vault
	void add_item(std::unique_ptr<Item<T>> item) {
		// print the item addition
		std::cout << "\033[0;32mAdding item - " << item.get() << std::endl;
		// insert the item to the vault
		insert_item(std::move(item));
		// print the current time and number of items in the vault
		std::cout << "\033[0;33mTime: " << age.get_time() << " Number of items: " << items.size()
				  << std::endl
				  << "\033[0m";
	}
	template<typename InputIt>
	void add_item(InputIt begin, InputIt end) {
		// add each item in the range
		for (auto it = begin; it != end; ++it) {
			add_item(std::move(*it));
		}
	}

	// remove item(s) from the vault (FIFO for default removal)
	std::unique_ptr<Item<T>> remove_item() {
		if (!items.empty()) {
			// move the unique pointer of the item
			auto item = std::move(items.front().first);
			// print the item removal
			std::cout << "\033[0;31mRemoving item - " << item.get() << std::endl;
			// remove the item from the vault
			items.pop_front();
			// print the current time and number of items in the vault
			std::cout << "\033[0;33mTime: " << age.get_time()
					  << " Number of items: " << items.size() << std::endl
					  << "\033[0m";
			// return the item
			return item;
		}

		// if the vault is empty, return nullptr
		std::cout << "\033[0;91mVault is empty\033[0m" << std::endl;
		return nullptr;
	}

	std::vector<std::unique_ptr<Item<T>>> remove_item(int count) {
		// create a vector to store the removed items
		std::vector<std::unique_ptr<Item<T>>> removed_items;

		while (count-- > 0) {
			// remove the specified number of items
			removed_items.push_back(remove_item());
		}

		return removed_items;
	}

	// get the number of items in the vault
	int get_number_of_items() const { return items.size(); }

	// determine how long an item has been in the vault
	int get_age_of_item(int item_id) const {
		// we cant use find_pair here because we don't want to change the items deque
		auto it = std::find_if(items.begin(), items.end(), [&](const auto& pair) {
			return pair.first->get_id() == item_id;
		});

		if (it != items.end()) {
			return age.get_time() - it->second;
		}

		return -1;
	}

	void print_items() {
		for (const auto& item : items) {
			std::cout << item.first.get() << std::endl
					  << "  Age: " << age.get_time() - item.second << std::endl;
		}
	}
};

// Static member initialization
template<typename T>
Age SuperUltraSecureVault<T>::age;
#endif	// VAULT_HPP
