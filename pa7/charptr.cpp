// This program should read any string (including spaces) from the user and print it using a character pointer
// The program is setup to use pointer offset notation to get each character of the string

// Number of bugs/errors : 8

#include <iostream> // fix indludes to iostream

using namespace std;

int main(void) // changed void to int
{
  char s[20];
  char* cPtr; // make pointer
  cin.getline(s, 20); // use getline to read string with spaces
  cPtr = s;
  while (*cPtr != '\0') // use dereference and remove -- and invert the condition
  {
    cout << *cPtr++; // use dereference  
  }
  cout << "\n";
  return 0;
}
