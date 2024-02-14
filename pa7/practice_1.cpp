// Program to check if the user-provided number is a palindrome

// TODO: Fix the bugs and make sure the program runs as expected.
// Provide a brief comment identifying each bug fixed.

#include <iostream>
#include <string> // include string library

bool func(int x); // return type should be bool, param is int
int main() // int not void
{
        int input; // int not char, dont need to initialize
        std::cout << "enter an integer please: "; // std:: and add a space for formatting
        std::cin >> input; // get input from user
        bool returned_val = func(input); // val type is bool, func not func2, take input
        if (!returned_val) // invert the condition
        {
            std::cout << "It is not a palindrome" << std::endl; // std::, "", and ;
        }
        else
        {
            std::cout << "It is a palindrome" << std::endl; // std::
        }

        return 0; // add ;
}

// the return value of your func should be true / false only
bool func(int x) // return type should be bool, param is int
{
       // convert the number to a string 
       std::string str = std::to_string(x);

       char* start = &str.front();
       char* end = &str.back();

       // while the start and end pointers don't meet loop through the string in both directions
       while (start < end)
       {
           // if the characters don't match return false
           if (*start != *end)            
           {
               return false;
           }

           // move the pointers inwards
           start++;
           end--;
       }

       // if they match all the way through return true
       return true;
}
