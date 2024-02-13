// This file contains utility method implementations.

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <limits>
#include "../include/utils.hpp"

using namespace std;


namespace utils {
    // clear cin buffer
    void clearCin() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // sorting/filtering helpers
    bool compareSeat(const array<string, 3> &a, const array<string, 3> &b) {
        return a[0].compare(b[0]) < 0;
    }

    bool compareName(const array<string, 3> &a, const array<string, 3> &b) {
        string aName = a[2];
        string bName = b[2];

        // convert to lowercase
        for (char &c : aName) {
            c = tolower(c);
        }
        for (char &c : bName) {
            c = tolower(c);
        }

        return aName.compare(bName) < 0;
    }

    void filterClass(vector<array<string, 3>> &manifest, const string &classFilter) {
        for (unsigned int i = 0; i < manifest.size(); i++) {
            if (manifest[i][1] != classFilter) {
                manifest.erase(manifest.begin() + i);
                // decrement i to account for the removed element
                i--;
            }
        }
    }
}
