// This program allocated memory for an NxM integer array dynamicaly
// The program then prints the 2D array in a matrix form using a combination of * and [] operators
// Note: You can't use ** or [][] for printing the values (use a combination of * and [] only.

// Number of bugs/errors : 6

#include <iomanip>
#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	int N = 3, M = 5;
	int i, j;
	int **d_array = (int **)malloc(N * sizeof(int)); // Allocating memory for 2D array (N rows)
	for (i = 0; i < N; i++)
		d_array[i] = (int *)malloc(M * sizeof(int *)); // Allocating memory for each row with M columns)
	// Initializing 2D array using [ ][ ] notation
	printf("Initializing array values!\n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			(*(d_array + i))[j] = i * M + j; // use mix of * and [] to access array elements
                                             // innitialize the array with values from 0 to N*M-1
		}
	}
	// Accessing 2D array using a combination of * and [] notation
	printf("\n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++) // use M as boundry for full row
		{
			cout << left << setw(3) << *(d_array[i] + j); // set width for formatting
		}
		cout << "\n";
	}

	// Deallocating 2D array
	for (i = 0; i < N; i++) { // add brackets for loop body
		free(*(d_array + i)); // free each row with dereference
    }
	free(d_array);
}
