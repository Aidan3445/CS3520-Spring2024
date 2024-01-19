// Fig. 5.6: fig05_06.cpp
// Compound interest calculations with for.
#include <iostream>
#include <iomanip>
#include <cmath> // standard math library
using namespace std;


double investment(double principal, double rate, int years) {
   // double principal: initial amount before interest
   // double rate: annual interest rate
   // int years: number of years invested

   double amount;
  
   // calculate amount on deposit for each of ten years
   for ( unsigned int year = 1; year <= years; ++year ) 
   {
      // calculate new amount for specified year
      amount = principal * pow( 1.0 + rate, year );
   } // end for 

   return amount;
}


int main()
{
   double monaLisaValue = 860000000;
   int monaLisaYear = 1626;
   int currentYear = 2024;
   int investmentAmount = 11;

   // display the value of the Mona Lisa painting in 2024
   cout << "The Mona Lisa painting is worth $" << monaLisaValue << " in " << currentYear << endl;
   
   // calcuate the value of an $11 investment at the bank with 5% in 1626
   double bankInvestment = investment(investmentAmount, 0.05, currentYear - monaLisaYear);
   cout << "An $11 investment at the bank with 5% in 1626 is worth $" << bankInvestment << " in " << currentYear << endl;

   // calculate the value of an $11 investment into NYSE with 10.17% in 1626
   double nyseInvestment = investment(investmentAmount, 0.1017, currentYear - monaLisaYear);
   cout << "An $11 investment into NYSE with 10.17% in 1626 is worth $" << nyseInvestment << " in " << currentYear << endl;
   cout << endl;

   // display headers
   cout << "Investment" << setw(30) << "Value Today" << endl;

   // set floating-point number format
   cout << fixed << setprecision(2);

   // display amounts
   cout << setw(10) << "None" << setw(30) << monaLisaValue << endl;
   cout << setw(10) << "Bank" << setw(30) << bankInvestment << endl;
   cout << setw(10) << "NYSE" << setw(30) << nyseInvestment << endl;
   
   for (float rate = 2; rate <= 12; rate += 0.5) {
      cout << setw(10) << rate << setw(30) << investment(investmentAmount, rate / 100, currentYear - monaLisaYear) << endl;
   }
}


/**************************************************************************
 * (C) Copyright 1992-2014 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
