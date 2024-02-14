// Program to read 3-dimensional matrix and display the elements as N^3 matrix
// TODO
// take the SIZE of the matrix as input from the user
// initize matrix using update_3d method (see comments below)
// display method must not be able to modify array elements (update the code as needed)
// display method must use a single loop/iterator to print the entire array with addresses
// display cannot use nested loops
//

#include <iostream>
#include <cstdlib>

void update_3d(double*** Matrix_3d, int size);
void display_1d(double*** const Matrix_3d, int size) ;

int main(void)
{
    // take the SIZE of the matrix as input from the user
    int size;
    std::cout << "Enter the size of the matrix: ";
    std::cin >> size;

	// prompt the user to initialize the matrix accordingly
	double*** Matrix_3d = new double**[size]; // triple pointer for 3D array of any size
    for (int i = 0; i < size; i++) {
        Matrix_3d[i] = new double*[size]; // initialize the 2nd dimension pointers
        for (int j = 0; j < size; j++) {
            Matrix_3d[i][j] = new double[size]; // initialize the 3rd dimension pointers
        }
    }
	// initialize the array to non-zero values (use scanf or random numbers generator)
	update_3d(Matrix_3d, size);
	// display the values
	display_1d(Matrix_3d, size);
	return 0;
}

void update_3d(double*** matrix, int size)
{
    std::srand(time(nullptr)); // set seed

    std::cout << "Entering N^3 (" << size * size * size << 
        ") elements of the matrix:" << std::endl;
	int i = 0;
	for (; i < size; i++)
	{
		int j = 0;
		for (; j < size; j++)
		{
			int k = 0;
			for (; k < size; k++)
			{
				matrix[i][j][k] = rand() % 100; // random number between 0 and 99
            }
		}
	}
}

// update as needed. 1 'for' loop only with 1 iterator to print all values with addresses
// must not be able to update the array.
// Share any observations:
// I initially tried to use *(*(*matrix + i)) to access the elements of the 3D array
// but i was hitting garbage values at the end of each dim so i changed it to matrix[d1][d2][d3]
void display_1d(double*** const matrix, int size) {
	
	int i;
    for (i = 0; i < size * size * size; i++) {
        int d1 = i / (size * size); 
        int d2 = (i % (size * size)) / size;
        int d3 = (i % (size * size)) % size;

        std::cout << "Address: " << &matrix[d1][d2][d3] << 
            " Value: " << matrix[d1][d2][d3] << std::endl;
    }
}
