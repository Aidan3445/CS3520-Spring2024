#include <cstring>
#include <iostream>
#include <memory>
using namespace std;
class MyString {
	// convert to unique_ptr of char[]
	std::unique_ptr<char[]> str;

  public:
	MyString() {  // Default Constructor
				  // following RAII to initialize the data in the constructor
		str = make_unique<char[]>(1);
		// use get() to get the raw pointer data
		str.get()[0] = '\0';
	};

	MyString(char* val) {  // Constructor with 1 arguments
		if (val == nullptr) {
			// following RAII to initialize the data in the constructor
			str = make_unique<char[]>(1);
			// use get() to get the raw pointer data
			str.get()[0] = '\0';
		} else {
			// swap for initialization of unique_ptr
			str = make_unique<char[]>(strlen(val) + 1);
			// use get() to get the raw pointer data
			strcpy(str.get(), val);
			// set the null terminator with the raw pointer data
			str.get()[strlen(val)] = '\0';
			cout << "The given string is: " << *this << endl;
		}
	}

	MyString(const MyString& source) {	// Copy Constructor
		str = make_unique<char[]>(strlen(source.str.get()) + 1);
		// use get() in this and source to get the raw pointer data
		strcpy(str.get(), source.str.get());
		str.get()[strlen(source.str.get())] = '\0';
	}

	MyString(MyString&& source) {  // Move Constructor
								   // use the built-in move function to move the unique_ptr
		str = std::move(source.str);
	}

	// can use the default destructor because the unique_ptr will handle the memory
	~MyString() = default;	// Destructor

	// override the << operator to print the string
	friend ostream& operator<<(ostream& os, const MyString& obj) {
		os << obj.str.get();
		return os;
	}
};

int main(void) {
	cout << "Start!" << endl;
	MyString a;
	MyString b {(char*)"Hello"};
	MyString c {a};
	MyString d {MyString {(char*)"World"}};
	cout << "Bye" << endl;
}
