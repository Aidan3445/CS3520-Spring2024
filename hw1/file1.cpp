/* Print the sum of products of odd and even numbers from 1 to 10
*  Print alternate characters from 'A' to 'Z' in the reverse order starting with 'Z'


*  Ouput of the program should look like:
    The value of limit is 10
    The Sum = 4785
    Z X V T R P N L J H F D B
*/

// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments) at the end of file.

#include <iostream>
using namespace std;

int main() {
  // values of limit, even_product, odd_product, sum were not initialized
  int limit = 10, even_product = 1, odd_product = 1, sum;
  char c;

  cout << "The value of limit is " << limit << endl;
  // i began incrementing from 0 instead of 1, 
  // which caused the product to be 0 for even numbers
  for (int i = 1; i <= limit; ++i) {
    // i % 2 == 0 checks if i is even, not i % 2 == 1
    if (i % 2 == 0) {
      even_product *= i;
    } else {
      odd_product *= i;
    }
  }
  sum = even_product + odd_product;
  cout << "The Sum = " << sum << "\n";

  for (c = 'Z'; c >= 'A'; c -= 2) {
    // this loop uses c rather than i
    cout << c << " ";
  }
  cout << endl;

  return 0;
}


// List of fixes:
// 1. values of limit, even_product, odd_product, sum were not initialized
// 2. i began incrementing from 0 instead of 1, which caused the product to be 0 for even numbers
// 3. i % 2 == 0 checks if i is even, not i % 2 == 1
// 4. for loop uses c rather than i
