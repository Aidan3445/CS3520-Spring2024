// Find and replace a string in a paragraph
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;

// find all exact instances of in a paragraph
void findExact(string &paragraph, string &find) {
   int count = 0;
   int index = 0;
   string indices = "";
   while (index != -1) {
      index = paragraph.find(find, index);
      // check if found and update values
      if (index != -1) {
         count++;
         indices += to_string(index) + " ";
         index += find.length();
      }
   }
   cout << "The word \"" << find << "\" appears " << count << " times at the following indices: " << indices << endl;
}

// find exact instances of a series of words in a paragraph
void findWords(string &paragraph, string &words) {
   // last index of a space
   int start = 0;
   string word;
   for (int i = 0; i < words.length(); i++) {
      if (words[i] == ' ') {
         word = words.substr(start, i - start);
         findExact(paragraph, word);
         start = i + 1;
      }
   }

   // last word
   word = words.substr(start);
   findExact(paragraph, word);
}

// replace all exact instances of in a paragraph
string replaceExact(string &paragraph, string &find, string &replace) {
   string updated = paragraph;
   int index = 0;
   while (index != -1) {
      index = updated.find(find, index);
      if (index != -1) {
         updated.replace(index, find.length(), replace);
         index += replace.length();
      }
   }

   return updated;
}

// replace all exact instances of a series of words in a paragraph
string replaceWords(string &paragraph, string &find, string &replace) {
   string updated = paragraph;
   // last index of a space
   int start = 0;
   string word;
   for (int i = 0; i < find.length(); i++) {
      if (find[i] == ' ') {
         word = find.substr(start, i - start);
         // could remove duplicate code by passing in a reference to a function
         updated = replaceExact(updated, word, replace);
         start = i + 1;
      }
   }

   // last word
   word = find.substr(start);
   return replaceExact(updated, word, replace);
}


int main() {
   // get paragraph from user, ends with a newline
   string paragraph;
   cout << "Enter a paragraph of text: ";
   getline(cin, paragraph);
   cout << endl;

   // get word to find
   string findStr;
   cout << "Enter a word to find: ";
   getline(cin, findStr);

   // search type (words or sentences)
   bool searchWords = false;

   // check if the entered string is multiple words
   if (findStr.find(' ') != string::npos) {
      string findType;
      // loop until the user enters a valid input
      do {
         cout << "Find words or sentences? (w/s): ";
         getline(cin, findType);
      } while (findType != "w" && findType != "s" && findType != "W" && findType != "S");

      // set search type
      searchWords = findType == "w" || findType == "W";
   }
   cout << endl;

   // find according to the user's input
   searchWords ? findWords(paragraph, findStr) : findExact(paragraph, findStr);
   cout << endl;

   // get word to replace
   string replaceStr;
   cout << "Enter a word to replace: ";
   getline(cin, replaceStr);
   cout << endl;

   // replace according to the search type
   string replaced = searchWords ? replaceWords(paragraph, findStr, replaceStr) : replaceExact(paragraph, findStr, replaceStr);

   // print the updated paragraph
   cout << "Old: " << paragraph << endl;
   cout << "New: " << replaced << endl;

   return 0;
}
