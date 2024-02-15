// Program to read integers into a 3X3 matrix and display them
// Todo: Fix bugs and makesure program works as intended.
// for each bug fix, add a comments specifying what you fixed.


#include <iostream>
using namespace std;
void display(const int Matrix[3][3]); // matrix of ints and should be const and size is always 3

int main(void)
{
  const int size = 3; // can be const
  int Matrix[size][size]; // matrix should be 3 by 3 only
  cout << "Enter 9 elements of the matrix:" << endl; // use cout
  for (int i = 0; i < size; i++) // initialize i as int
  {
    int j = 0; // j can move into loop optionally
    for (; j < size; j++)
    {
      cout << "Enter element " << j + 1 << " of row " << i + 1 << ": "; // add prompt
      cin >> Matrix[i][j]; // swap i and j order
    }
  }
  display(Matrix); // no address of operator needed
  return 0;
}

void display(const int Matrix[3][3]) // add const and size for this method is always 3
{
  for (int i = 0; i < 3; i++) // ; 
  {
    for (int j = 0; j < 3; j++) // increment j
    {
      cout << Matrix[i][j] << ", ";
    }
    cout << endl; // add ;
  }
}
