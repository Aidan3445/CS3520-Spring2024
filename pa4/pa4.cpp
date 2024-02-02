#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <array>

using namespace std;

// functions for reading and printing 2D vectors and 3D arrays
vector<vector<double>> read_2d_vector();
array<array<array< double, 3>, 3>, 3> read_3d_array();
void write_2d_vector(const vector<vector<double>> &vec);
void write_3d_array(const array<array<array<double, 3>, 3>, 3> );

int main() {
    vector<vector<double>> vec = read_2d_vector();
    write_2d_vector(vec);

    array<array<array<double, 3>, 3>, 3> arr3d = read_3d_array();
    write_3d_array(arr3d);
}

vector<string> readFile() {
    // list of numbers
    // we will store numbers in a string and then convert to double
    vector<string> numbers;

    // open the file
    ifstream file;
    file.open("input.txt");

    // make sure file is open
    if (!file.is_open()) {
        cout << "File not found" << endl;
        return numbers;
    }

    // read file line by line
    string line;
    while (getline(file, line)) {
        string number = "";
        for (int i = 0; i < line.size(); i++) {
            // if we hit a space, add to vector
            if (line[i] == ',') {
                // incase there are multiple commas in a row
                if (number != "") {
                    numbers.push_back(number);
                    number = "";
                }
            } else {
                // append to character string if not a space
                number += line[i];
            }
        }
        // add last number to vector if not empty
        if (number != "") {
            numbers.push_back(number);
        }
    }
    // close file
    file.close();

    return numbers;
}

/*
// numbers are separated by commas, rows by newlines
// 2D vector reading function
For each line in file:
    Read line
    For each number in line:
        Add number to vector
    Add vector to 2D vector
Return 2D vector
*/

vector<vector<double>> read_2d_vector() {
    // read the file
    vector<string> numbers = readFile();

    // 2D vector to store numbers
    vector<vector<double>> v;

    // iterate through numbers and add to 2D vector
    int rows = 9;
    int cols = 3;
    for (int i = 0; i < rows; i++) {
        vector<double> row;
        for (int j = 0; j < cols; j++) {
            if (i * cols + j >= numbers.size()) {
                row.push_back(0);
                continue;
            }
            row.push_back(stod(numbers[i * cols + j]));
        }
        v.push_back(row);
    }

    return v;
}


/*
For each column in 2D Vector
    Find the max number of characters in the column
For each row in 2D Vector
    For each column in 2D Vector
        Write the number to the file with the max width
    Write a newline in file
*/
void write_2d_vector(const vector<vector<double>> &vec) {
    // iterate through all numbers and count the max characters
    // in each column, use that for setting width when writing
    vector<int> max_chars;
    // iterate column first
    for (int col = 0; col < vec[0].size(); col++) {
        // save the max
        int max = 0;
        for (int row = 0; row < vec.size(); row++) {
            int num_chars = to_string(vec[row][col]).size();
            if (num_chars > max) {
                // update the max
                max = num_chars;
            }
        }
        max_chars.push_back(max);
    }

    // open the file
    ofstream file;
    file.open("2DVector.txt");

    // make sure file is open
    if (!file.is_open()) {
        cout << "File not found" << endl;
        return;
    }

    for (int row = 0; row < vec.size(); row++) {
        for (int col = 0; col < vec[row].size(); col++) {
            // left align with max width
            file << left << setw(max_chars[col]) << vec[row][col] << " ";
        }
        file << endl;
    }
} 


/*
// numbers are separated by commas, rows by newlines
// 3D vector reading function
// this method takes in an array and fills it with the numbers from the file
// rather than returning a 3D array
For each line in file:
    Read line
    For each number in line:
        Add number to array
*/
array<array<array<double, 3>, 3>, 3> read_3d_array() {

    array<array<array<double, 3>, 3>, 3> arr3d;

    // read the file
    vector<string> numbers = readFile();
    
    // iterate through numbers and add to 3D array
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (i * 9 + j * 3 + k >= numbers.size()) {
                    arr3d[i][j][k] = 0;
                    continue;
                }
                arr3d[i][j][k] = stod(numbers[i * 9 + j * 3 + k]);
            }
        }
    }

    return arr3d;
}


/*
For each column in 3D Array
    Find the max number of characters in the column
For each row in 3D Array
    For each column in 3D Array
        For each 3rd dimension in 3D Array
            Write the number to the file with the max width
        Write a newline in file
    Write a newline in file
 */
void write_3d_array(const array<array<array< double, 3>, 3>, 3> arr) {
    // iterate through all numbers and count the max characters
    // in each column, use that for setting width when writing
    vector<vector<int>> max_chars;
    for (int dim = 0; dim < 3; dim++) {
        vector<int> max_chars_dim;
        for (int col = 0; col < 3; col++) {
            // save the max
            int max = 0;
            for (int row = 0; row < 3; row++) {
                int num_chars = to_string(arr[row][col][dim]).size();
                if (num_chars > max) {
                    // update the max
                    max = num_chars;
                }
            }
            max_chars_dim.push_back(max);
        }
        max_chars.push_back(max_chars_dim);
    }

    // open the file
    ofstream file;
    file.open("3DArray.txt");

    // make sure file is open
    if (!file.is_open()) {
        cout << "File not found" << endl;
        return;
    }

    for (int dim = 0; dim < 3; dim++) {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                // left align with max width
                file << left << setw(max_chars[dim][col]) << arr[row][col][dim] << " ";
            }
            file << endl;
        }
        file << endl;
    }
}
