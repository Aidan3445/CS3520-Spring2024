#include <iomanip>
#include <iostream>
#include <string>
#include <map>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;



int main() {
    // create a map of prices for flights
    // destination -> airline -> price
    map<string, map<string, double>> prices;

    srand(time(nullptr));
    // fill the map with data
    array<string, 5> names = {"Bahamas", "Miami", "San Diego", "Grand Canyons", "Aruba"};
    array<string, 5> airlines = {"Delta", "American", "Southwest", "United", "JetBlue"};
    for_each(names.begin(), names.end(), [&prices, &airlines](string name) {
            for_each(airlines.begin(), airlines.end(), [&prices, &airlines, name](string airline) {
                    prices[name][airline] = rand() % 100000 / 100.0 + 100.0; // 100 - 1100
                    });
            });

    // print the map
    cout << fixed << setprecision(2) << left;
    cout << "\e[1m" << setw(15) << "Destination" << setw(10) << "Delta" << 
        setw(10) << "American" << setw(10) << "Southwest" << 
        setw(10) << "United" << setw(10) << "JetBlue\e[0m" << endl;
    for (auto& dest : prices) {
        cout << setw(15) << dest.first;
        for (auto& airline : dest.second) {
            cout << setw(10) << airline.second;
        }
        cout << endl;
    }

    // find the average price for each destination
    vector<pair<string, double>> averages;
    for_each(prices.begin(), prices.end(), [&averages](pair<string, map<string, double>> dest) {
            double sum = 0;
            for_each(dest.second.begin(), dest.second.end(), [&sum, &averages](pair<string, double> airline) {
                    sum += airline.second;
                    });
            averages.push_back(make_pair(dest.first, sum / dest.second.size()));
            });
    sort(averages.begin(), averages.end(), [](pair<string, double> a, pair<string, double> b) {
            return a.second < b.second;
            });
    cout << "\nAverage price for each destination:\n";
    for_each(averages.begin(), averages.end(), [](pair<string, double> dest) {
            cout << dest.first << " average price: " << dest.second << endl;
            });

    // find the cheapest flight for each destination and the airline
    vector<pair<string, pair<string, double>>> cheapest;
    for_each(prices.begin(), prices.end(), [&cheapest](pair<string, map<string, double>> dest) {
            auto min = min_element(dest.second.begin(), dest.second.end(), 
                    [](pair<string, double> a, pair<string, double> b) {
                    return a.second < b.second;
                    });
            cheapest.push_back(make_pair(dest.first, *min)); // not entirely sure why 
                                                             // this needs to be dereferenced
            });
    sort(cheapest.begin(), cheapest.end(), 
            [](pair<string, pair<string, double>> a, pair<string, pair<string, double>> b) {
            return a.second.second < b.second.second;
            });
    cout << "\nCheapest flight for each destination:\n";
    for_each(cheapest.begin(), cheapest.end(), [](pair<string, pair<string, double>> dest) {
            cout << dest.first << " cheapest flight: " << 
            dest.second.first << " " << dest.second.second << endl;
            });

    return 0;
}
