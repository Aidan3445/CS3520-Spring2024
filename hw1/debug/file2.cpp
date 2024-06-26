// Automatic dialing machine
// Delivers a sales message
/* Needs to print all possible combinations of areacode and exchangecode with the last 4 digits


Example : If areacode = 617, exchange = 424
Output :
"I am calling to tell you to buy a subscription to Dogs Monthly Magazine!"
617-424-0001
617-424-0002
617-424-0003
...
617-424-9998
617-424-9999
*/

// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments) at the end of file.

// use # for include statements
#include<iostream>
#include<limits>

// helper function to check if string is all digits
bool areDigits(const std::string &str)
{
    for (char c : str)
    {
        if (!std::isdigit(c))
            return false;
    }

    return true;
}


int main() {
    // use int instead of char for digits
    int digit1, digit2, digit3, digit4;
    // we are not using the namespace so we need to use std::string
    std::string areaCode, exchange;
    // standardize no spaces between operators
    std::cout<<"Hello, I am a telemarketing calling making program.\n";
    // loops to ensure three digits
    do {
        std::cout<<"Enter a three-digit area code ";
        // use cin>> for input
        std::cin>>areaCode;
    } while (areaCode.length() != 3 || !areDigits(areaCode));

    do {
        std::cout<<"Enter a three-digit exchange to call ";
        // use cin>> for input
        std::cin>>exchange;
    } while (exchange.length() != 3 || !areDigits(exchange));

    std::cout<<"I am calling to tell you to buy a subscription to Dogs Monthly!\n";
    for(digit1 = 0; digit1 <= 9; ++digit1){
        for(digit2 = 0; digit2 <= 9; ++digit2){
            for(digit3 = 0; digit3 <= 9; ++digit3) {
                for(digit4 = 0; digit4 <= 9; ++digit4) {
                    std::cout<<areaCode<<'-'<<exchange<<'-'<<digit1<<digit2<<digit3<<digit4<<std::endl;
                }
            }
        }
    }

    std::cout<< "\nCalls completed"<<std::endl;
    return 0;
}

// List of fixes:
// 1. Use int instead of char for digits
// 2. Use std:: (could use namespace std)
// 3. Standardize no spaces between operators in cout and cin
// 4. Use cin>> for input
// 5. Use helper function to check if string is all digits
// 6. Use # for include statements
// 7. Loops to ensure three digits
