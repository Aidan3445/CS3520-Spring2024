#include "test_objects.hpp"

// Book

Book::Book(const string& title, const int& num_pages) {
    this->title = title;
    this->num_pages = num_pages;
}

string Book::get_title() const {
    return title;
}

int Book::get_pages() const {
    return num_pages;
}

bool Book::operator==(const Book& other) const {
    return title == other.title && num_pages == other.num_pages;
}

bool Book::operator!=(const Book& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << "Title: " << book.title << ", Pages: " << book.num_pages;
    return os;
}

// AccountInfo

AccountInfo::AccountInfo(const string& username, const string& password, const string& web_address) {
    this->username = username;
    this->password = password;
    this->web_address = web_address;
}

string AccountInfo::get_username() const {
    return username;
}

string AccountInfo::get_password() const {
    return password;
}

string AccountInfo::get_web_address() const {
    return web_address;
}

bool AccountInfo::operator==(AccountInfo other) const {
    return username == other.username && password == other.password && web_address == other.web_address;
}

bool AccountInfo::operator!=(AccountInfo other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const AccountInfo& acc) {
    os << "Username: " << acc.username << ", Password: " << acc.password << ", Website: " << acc.web_address;
    return os;
}