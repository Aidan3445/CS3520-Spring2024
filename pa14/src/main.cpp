// Fig. 24.11: ThreadedFibonacci.cpp
// Fibonacci calculations performed in separate threads
#include <ctime>
#include <future>
#include <iomanip>
#include <iostream>

using namespace std;

// class to represent the results
class ThreadData {
  public:
	clock_t startTime;	// time thread starts processing time_t endTime;
	clock_t endTime;	// time thread finishes processing
};						// end class ThreadData

unsigned long long int fibonacci(unsigned int n);  // function prototype
ThreadData startFibonacci(unsigned int n);		   // function prototype

int main() {
	int a, b, c;
	cout << "Enter 3 numbers: ";
	cin >> a >> b >> c;

	cout << fixed << setprecision(6);
	cout << "Calculating fibonacci(" << a << ") and fibonacci(" << b << ") and fibonacci(" << c
		 << ") in separate threads" << endl;
	cout << "Starting thread to calculate fibonacci(" << a << ")" << endl;
	auto futureResult1 = async(launch::async, startFibonacci, a);
	cout << "Starting thread to calculate fibonacci(" << b << ")" << endl;
	auto futureResult2 = async(launch::async, startFibonacci, b);
	cout << "Starting thread to calculate fibonacci(" << c << ")" << endl;
	auto futureResult3 = async(launch::async, startFibonacci, c);

	// wait for results from each thread
	ThreadData result1 = futureResult1.get();
	ThreadData result2 = futureResult2.get();
	ThreadData result3 = futureResult3.get();
	// determine time that first thread started
	time_t startTime =
		(result1.startTime < result2.startTime) ? result1.startTime : result2.startTime;
	startTime = (startTime < result3.startTime) ? startTime : result3.startTime;
	// determine time that last thread terminated
	time_t endTime = (result1.endTime > result2.endTime) ? result1.endTime : result2.endTime;
	endTime = (endTime > result3.endTime) ? endTime : result3.endTime;
	// display total time for calculations
	cout << "Total calculation time: " << difftime(endTime, startTime) / CLOCKS_PER_SEC
		 << " seconds" << endl;


	cout << endl
		 << endl
		 << endl
		 << "Now calculating fibonacci(" << a << ") and fibonacci(" << b << ") and fibonacci(" << c
		 << ") in the main thread" << endl;

	startTime = clock();
	auto fibonacciValue1 = startFibonacci(a);
	auto fibonacciValue2 = startFibonacci(b);
	auto fibonacciValue3 = startFibonacci(c);

	cout << "Total calculation time: " << difftime(clock(), startTime) / CLOCKS_PER_SEC
		 << " seconds" << endl;


}  // end main

// executes function fibonacci asynchronously
ThreadData startFibonacci(unsigned int n) {
	// create a ThreadData object to store times
	ThreadData result = {0, 0};
	cout << "Calculating fibonacci(" << n << ")" << endl;
	result.startTime = clock();	 // time before calculation
	auto fibonacciValue = fibonacci(n);
	result.endTime = clock();  // time after calculation
	// display fibonacci calculation result and total calculation time
	cout << "fibonacci(" << n << ") = " << fibonacciValue << endl;
	cout << "Calculation time = " << difftime(result.endTime, result.startTime) / CLOCKS_PER_SEC
		 << " seconds" << endl
		 << endl;
	return result;
}  // end function startFibonacci

// Recursively calculates fibonacci numbers
unsigned long long int fibonacci(unsigned int n) {
	// base case
	if (0 == n || 1 == n) {
		return n;
	}		// end if
	else {	// recursive step
		return fibonacci(n - 1) + fibonacci(n - 2);
	}  // end else
}  // end function fibonacci
