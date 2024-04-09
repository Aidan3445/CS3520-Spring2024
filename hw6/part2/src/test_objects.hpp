
#ifndef TEST_OBJS
#define TEST_OBJS
#include <ostream>
using namespace std;

/** Represents a Book with a title and number of pages. */
class Book {
    private:
        string title;
        int num_pages;
    public:
        /** Constructs a book */
        Book(const string& title, const int& num_pages);
        /** Gets the title of this book */
        string get_title() const;
        /** Gets the number of pages in this book */
        int get_pages() const;
        /** Checks equality */
        bool operator==(const Book& other) const;
        /** Checks not equal */
        bool operator!=(const Book& other) const;
        /** Prints this object */
        friend std::ostream& operator<<(std::ostream& os, const Book& book);
};

/** Represents a login as it could be stored in a password manager. */
class AccountInfo {
    private:
        string username;
        string password;
        string web_address;
    public:
        /** Constructs a login */
        AccountInfo(const string& username, const string& password, const string& web_address);
        /** Gets the username of the login */
        string get_username() const;
        /** Gets the password of the login*/
        string get_password() const;
        /** Gets the web address of the associated website for this login */
        string get_web_address() const;
        /** Checks equality */
        bool operator==(AccountInfo other) const;
        /** Checks not equal */
        bool operator!=(AccountInfo other) const;
        /** Prints this object */
        friend std::ostream& operator<<(std::ostream& os, const AccountInfo& acc);
};

#endif