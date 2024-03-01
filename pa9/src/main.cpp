#include <iomanip>
#include <iostream>
#include <string>
#include <map>
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
    cout << "\nAverage price for each destination:\n";
    for_each(prices.begin(), prices.end(), [](pair<string, map<string, double>> dest) {
            double sum = 0;
            for_each(dest.second.begin(), dest.second.end(), [&sum](pair<string, double> airline) {
                    sum += airline.second;
                    });
            cout << dest.first << " average: " << sum / dest.second.size() << endl;
            });

    // find the cheapest flight for each destination and the airline
    cout << "\nCheapest flight for each destination:\n";
    for_each(prices.begin(), prices.end(), [](pair<string, map<string, double>> dest) {
            auto cheapest = min_element(dest.second.begin(), dest.second.end(), 
                    [](pair<string, double> a, pair<string, double> b) {
                    return a.second < b.second;
                    });
            cout << dest.first << " cheapest flight: " << cheapest->first << " " << cheapest->second << endl;
            });

    return 0;
}
