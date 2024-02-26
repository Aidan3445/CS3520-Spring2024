#include "high_score.hpp"

// Reads all saved scores
int* top_scores() {
    ifstream file;
    file.open(BEST_TEN_FILE);
    if (!file) {
        throw "No file found";
        return nullptr;
    }
    int *topTen = new int[10];
    string line;
    int index = 0;
    while (getline(file, line) && index < 10) {
        if (line.compare("") == 0) {
            topTen[index] = 0;
        }
        else {
            topTen[index] = stoi(line);
        }
        index++;
    }
    while (index < 10) {
        topTen[index] = 0;
        index++;
    }
    file.close();
    return topTen;
}

// Places top 10 scores in cur_top array, with my score inserted
int* insert_score(const int const* orig_top, int* cur_top, const int &my_score) {
    for (int i = 0; i < 10; i++) {
        cur_top[i] = orig_top[i];
        if (my_score > orig_top[i]) {
            for (int j = 9; j >= i; j--) {
                cur_top[j+1] = orig_top[j];
            }
            cur_top[i] = my_score;
            break;
        }
    }
    return cur_top;
}

// Saves your score (if you're good)
void save_score(const int const* orig_top, const int &my_score) {
    ofstream file;
    file.open(BEST_TEN_FILE);
    if (!file) {
        throw "No file found";
        return;
    }
    int *newScores = new int[10];
    insert_score(orig_top, newScores, my_score);
    for (int i = 0; i < 10; i++) {
        file << newScores[i] << endl;
    }
    delete[] newScores;
    file.close();
}