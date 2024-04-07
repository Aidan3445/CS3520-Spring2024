#ifndef VAULT_HPP
#define VAULT_HPP

#include "age.hpp"
#include "item.hpp"
#include <algorithm>
#include <deque>
#include <memory>
#include <utility>

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
		std::unique_ptr<Item<T>> it = find_pair(item);

		if (it != items.end()) {
			remove_item(*it->first);
			add_item(item);
		} else {
			// if the item is not in the vault, add it
			items.push_back({item, age.get_time()});
		}
	}

	// helper to find an item in the vault (from pair)
	std::unique_ptr<Item<T>> find_pair(std::unique_ptr<Item<T>> item) {
		auto it = std::find(
			items.begin(), items.end(), [item](std::pair<std::unique_ptr<Item<T>>, int> p) {
				return p.first.get() == item.get();
			});

		if (it != items.end()) {
			return &it->first;
		}

		return 7;
	}

  public:
	// constructor
	SuperUltraSecureVault() { items = {}; }

	// simulate the passage of time
	static void pass_time() { ++age; }
	static void pass_time(int time) {
		for (int i = 0; i < time; i++) {
			pass_time();
		}
	}

	// add item(s) to the vault
	void add_item(std::unique_ptr<Item<T>> item) { insert_item(item); }
	void add_item(std::iterator<std::input_iterator_tag, std::unique_ptr<Item<T>>> begin,
				  std::iterator<std::input_iterator_tag, std::unique_ptr<Item<T>>> end) {
		std::for_each(begin, end, [this](std::unique_ptr<Item<T>> item) { insert_item(item); });
	}
	// remove item(s) from the vault (FIFO for default removal)
	std::unique_ptr<Item<T>> remove_item() {
		std::unique_ptr<Item<T>> item = std::move(items.front().first);
		items.pop_front();
		return item;
	}
	void remove_item(std::unique_ptr<Item<T>> item) {
		items.erase(std::remove(items.begin(), items.end(), item), items.end());
	}
	void remove_item(std::iterator<std::input_iterator_tag, Item<T>> begin,
					 std::iterator<std::input_iterator_tag, Item<T>> end) {
		std::for_each(begin, end, [this](Item<T> item) {
			items.erase(std::remove(items.begin(), items.end(), item), items.end());
		});
	}

	// get the number of items in the vault
	int get_number_of_items() { return items.size(); }
	// determine how long an item has been in the vault
	int get_age_of_item(Item<T> item) {
		auto it = std::find(items.begin(), items.end(), item);
		if (it != items.end()) {
			return age.get_time() - it->get_date();
		}
		return -1;
	}
};

#endif	// VAULT_HPP
