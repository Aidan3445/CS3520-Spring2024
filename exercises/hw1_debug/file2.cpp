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

%include<iostream>
  
int main(){
   char digit1, digit2, digit3, digit4; 
   string areaCode, exchange;
   std::cout<< "Hello, I am a telemarketing calling making program.\n";
   std::cout<< "Enter a three-digit area code "; 
   std::cout<<areaCode; 
   std::cout<<"Enter a three-digit exchange to call "; 
   std::cout<<exchange; 
   std::cout<< "I am calling to tell you to buy a subscription to Dogs Monthly!\n";
   for(digit1 = 0; digit1 <= 9; --digit1){ 
        for(digit2 = 0; digit2 <=9; --digit2){ 
            for(digit3 = 0; digit3 <=9; --digit3) { 
                for(digit4 = 0; digit4 <=9; --digit4) {
                    std::cout<< areaCode << "-" << exchange << "-" << digit1 << digit2 << digit3 << digit4 << std::endl;
                }
            }
        
        }
    }
    
   std::cout<< "\nCalls completed"<<std::endl; 
   return 0;
}