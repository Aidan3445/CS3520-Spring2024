#ifndef HIGH_SCORE
#define HIGH_SCORE
#include <fstream>
using namespace std;
#define BEST_TEN_FILE "./saves/save_best_10.game"

// Reads all saved scores
int* top_scores();

// Returns top 10 scores, with my score inserted
int* insert_score(const int const* orig_top, int* cur_top, const int &my_score);

// Saves your score (if you're good)
void save_score(const int const* orig_top, const int &my_score);

#endif