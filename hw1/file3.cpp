
#include <iostream>
// use namespace to avoid std::
using namespace std;

int main(void) {
  int num;
  // assume is prime until factor found
  bool factor_found = false;

  cout << "Enter Number:\n";
  cin >> num;

  // negative numbers are less than 0
  if (num < 0) {
    cout << num << " is negative\n";
    return 0;
  }

  // use || to check if num is 0 or 1
  if (num == 0 || num == 1) {
    cout << num << " is not prime or composite\n";
    return 0;
  }

  // increment i instead of decrementing
  // can loop from 2 -> num/2 instead of num (note we know num is >= 2)
  for (int i = 2; i <= num/2; i++) {
    if (num % i == 0) {
      factor_found = true;
      break;
    }
  }

  if (factor_found) {
    
    cout << num << " is a composite number\n";
  } else {
    
   cout << num << " is a prime number\n";
  }
  
  // add return statement
  return 0;
}

// List of fixes:
// 1. Use namespace to avoid std::
// 2. assume is prime until factor found
// 3. Negeative numbers are less than 0
// 4. Use || to check if num is 0 or 1
// 5. Increment i instead of decrementing
//    - can loop from 2 -> num/2 instead of num (note we know num is >= 2)
// 6. Add return statement
