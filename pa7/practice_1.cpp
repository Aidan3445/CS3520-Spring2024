// Program to check if the user-provided number is a palindrome

// TODO: Fix the bugs and make sure the program runs as expected.
// Provide a brief comment identifying each bug fixed.

#include <iostream>

bool func(const int &n); // return type should be bool, param is int
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
bool func(const int &n) // return type should be bool, param is const &int only
{
        int given_number = n; // initialize given_number as int to n
        int temp = 0;
        while (given_number > 0) // use > instead of = and modify given_number
        {
                int remainder = given_number % 10; // use % instead of /, initialize remainder as int
                given_number /= 10; // use /= assignment
                temp = temp * 10 + remainder; // update temp value
        }

        if (n != temp) // invert the condition
        {
                return false;
        }
        else
        {
                return true;
        }
}
