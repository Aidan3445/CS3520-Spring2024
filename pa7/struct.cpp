// This program includes a struct called car that is used to store information
// about a given car The program should ask the user for information about their
// car and initialize a car structure with the given information The program
// should also print the information using a pointer to the initialized struct
// The information printed using the struct and the pointer should be the same

#include <iostream> // dont need string
using namespace std; // use std for cin, cout, and endl

struct car {
  char *name;
  int modelYear;
  float speed;
};

int main(void) {
  // use better variable names
  char name[20];
  int year;
  float speed;

  struct car c;
  car *cPtr = &c;

  cout << "What is your favorite car's name: "; // fix formatting
  cin >> name;
  c.name = name; // c.name

  cout << "When was it launched: "; // fix formatting
  cin >> year; // cin
  c.modelYear = year;

  cout << "How much speed does it give: "; // fix formatting
  cin >> speed; // use >> operator
  c.speed = speed;

  cout << "Car's name is" << c.name << ", and should be the same as " // fix formatting
       << cPtr->name << ".\n"; // use -> operator

  cout << "Car's model year is " << c.modelYear // object is called c also fix formatting
       << ", and should be the same as " << cPtr->modelYear << ".\n"; // reference is cPtr
  cout << "Car's speed is " << c.speed << ", and should be the same as " << cPtr->speed // get from cPtr
       << ".\n";
}
