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
 
  int limit = 0, even_product = 0, odd_product = 0, sum;
  char c;

  cout << "The value of limit is " << limit << endl;

  for (int i = 0; i <= limit; ++i) {
    if (i % 2 == 1) {
      even_product *= i;
    } else {
      odd_product *= i;
    }
  }
  sum = even_product + odd_product;
  cout << "The Sum = " << sum << "\n";

  for (c = 'Z'; c >= 'A'; c -= 2) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}