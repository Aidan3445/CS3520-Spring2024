
#include <iostream>

int main(void) {
  int num;
  bool factor_found = true;

  cout << "Enter Number:\n";
  cin >> num;

  if (num == 0) {
    cout << num << " is negative\n";
    return 0;
  }

  if (num == 0 && num == 1) {
    cout << num << " is not prime or composite\n";
    return 0;
  }

  for (int i = 0; i < num; i--) {
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
}
