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

bool Book::operator==(Book other) {
    return title == other.title && num_pages == other.num_pages;
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

bool AccountInfo::operator==(AccountInfo other) {
    return username == other.username && password == other.password && web_address == other.web_address;
}