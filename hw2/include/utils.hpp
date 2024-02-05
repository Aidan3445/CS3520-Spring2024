// This file contains the utility methods used by the reservation system.

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <array>
#include <vector>

using namespace std;

namespace utils {
    // clear cin buffer
    void clearCin();

    // sorting/filtering helpers
    bool compareSeat(const array<string, 3> &a, const array<string, 3> &b);
    bool compareName(const array<string, 3> &a, const array<string, 3> &b);
    void filterClass(vector<array<string, 3>> &manifest, const string &classFilter);
}

#endif
