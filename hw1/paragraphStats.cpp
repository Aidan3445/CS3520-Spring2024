// Analyze a paragraph of text and print out statistics
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;

// struct to hold statistics about a paragraph
struct ParagraphStats {
   int words = 0;
   int vowels = 0;
   int consonants = 0;
   int oneVowelPunc = 0;
   int threePlusVowels = 0;
   int shorterCpuWords = 0;
   int shorterUserWords = 0;

   // strings to hold the vowels and punctuation
   string vowelChars = "aeiouAEIOU";
   string consonantChars = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";
   string punctuationChars = ".,;:!?\"";
};


// function to format and print the paragraph and basic stats
ParagraphStats parseParagraph(string &paragraph, int maxLineLength) {
   int lineLength;
   char current;
   int lastSpace;

   ParagraphStats stats;
   int wordVowelCount = 0;
   bool hasPunc = false;

   // loop through each character in the paragraph
   for (int i = 0; i < paragraph.length(); i++) {
      current = paragraph[i];

      // if the line length is greater than the max line length
      if (lineLength > maxLineLength) {
         // insert a newline
         paragraph.replace(lastSpace, 1, "\n");
         // reset the line length
         lineLength = 0;
      }

      // check if the current character is a space update the index
      // also increment the number of words
      if (current == ' ' || i == paragraph.length() - 1) {
         lastSpace = i;
         stats.words++;

         // check if the previous word had 3 or more vowels
         if (wordVowelCount >= 3) {
            stats.threePlusVowels++;
         }
         // check if the previous word had 1 vowel and punctuation
         else if (wordVowelCount == 1 && hasPunc) {
            stats.oneVowelPunc++;
         }

         // reset the word vowel count and punctuation flag
         wordVowelCount = 0;
         hasPunc = false;
      }
      // if the current character is a vowel increment the number of vowels
      // also increment the number of word vowels
      else if(stats.vowelChars.find(current) != string::npos) {
         stats.vowels++;
         wordVowelCount++;
      }
      // if the current character is a punctuation increment the number of punctuation
      else if(stats.punctuationChars.find(current) != string::npos) {
         hasPunc = true;
      }
      // if the current character is a consonant increment the number of consonants
      else if (stats.consonantChars.find(current) != string::npos){
         stats.consonants++;
      }

      // increment the line length
      lineLength++;
   }

   // print the paragraph
   cout << paragraph << endl;
   cout << endl;

   // print the stats
   cout << setw(12) << "Stat" << setw(10) << "Value" << endl;
   cout << "-------------------------" << endl;
   cout << setw(12) << "Words" << setw(10) << stats.words << endl;
   cout << setw(12) << "Vowels" << setw(10) << stats.vowels << endl;
   cout << setw(12) << "Consonants" << setw(10) << stats.consonants << endl;
   cout << setw(12) << "1 Vowel Punc" << setw(10) << stats.oneVowelPunc << endl;
   cout << setw(12) << "3+ Vowels" << setw(10) << stats.threePlusVowels << endl;
   cout << endl;

   return stats;
}


// helper function to check if string is all digits
bool areDigits(const std::string &str)
{
   for (char c : str)
   {
      if (!std::isdigit(c))
         return false;
   }

   // clear the buffer
   std::cin.ignore(std::numeric_limits<int>::max(), '\n');
   return true;
}

ParagraphStats parseWordLength(string &paragraph, ParagraphStats &stats) {
   string userInput;
   // get a number from the user
   // check if the number is a digit and is greater than 0
   do {
      cout << "Enter a (positive) number ";
      cin >> userInput;
   } while (!areDigits(userInput)|| stoi(userInput) <= 0);
   int userLen = stoi(userInput);

   // generate a random number between 6 and 10
   int computerLen;
   srand(time(NULL));
   computerLen = rand() % 5 + 6;

   cout << "You chose " << userLen << " and the computer chose " << computerLen << endl;
   cout << endl;

   // loop through each word in the paragraph
   int wordLengthWithPunc = 0;
   int wordLengthNoPunc = 0;
   for (int i = 0; i < paragraph.length(); i++) {
      // check if the current character is a space
      if (paragraph[i] == ' ' || paragraph[i] == '\n' || i == paragraph.length() - 1) {
         // check if the word length is shorter than the shorter number
         if (wordLengthNoPunc <= userLen) {
            stats.shorterUserWords++;
         }
         // check if the word length is longer than the longer number
         if (wordLengthWithPunc <= computerLen) {
            stats.shorterCpuWords++;
         }

         // reset the word length
         wordLengthWithPunc = 0;
         wordLengthNoPunc = 0;
      }
      // check if the current character is a punctuation
      // increment the word length with punctuation
      else if (stats.punctuationChars.find(paragraph[i]) != string::npos) {
         wordLengthWithPunc++;
      }
      // increment both word lengths
      else {
         wordLengthWithPunc++;
         wordLengthNoPunc++;
      }
   }

   // print the stats
   cout << "Words at least User Len(" << userLen << ") chars long -- ignoring punctiation: " << stats.shorterUserWords << endl;
   cout << "Words at least CPU Len(" << computerLen << ") chars long -- with punctuation: " << stats.shorterCpuWords << endl;

   return stats;
}


int main() {
   // get paragraph of text, a paragraph ends with a newline
   string paragraph;
   cout << "Enter a paragraph of text: ";
   getline(cin, paragraph);

   cout << endl;
   // print formatted paragraph
   ParagraphStats stats = parseParagraph(paragraph, 80);
   parseWordLength(paragraph, stats);

   return 0;
}
