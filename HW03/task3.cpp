#include "msort.h"
#include <iostream>
#include <cstdlib>   // For rand, srand
#include <ctime>     // For time, clock_t
#include <chrono> 
#include <random>   // For high-resolution timing

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::cout;
int main(int argc, char* argv[]) {
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    std::random_device rd;   
    std::mt19937 gen(rd());  
    std::uniform_int_distribution<> dis(-1000, 1000);   // I found this through ChatGPT
    std::size_t n = std::stoul(argv[1]);        // Array size
    int t = std::stoi(argv[2]);                 // Number of threads
    std::size_t threshold = std::stoul(argv[3]); 
    int *arr = (int*)malloc(n * sizeof(int));
    // Check if the required number of arguments are provided
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <n> <t> <ts>" << std::endl;
        return 1;
    }

    // Set the number of threads in OpenMP
    omp_set_num_threads(t);
   
    for (std::size_t i = 0; i < n; ++i) {
        arr[i] = dis(gen); // Random number between -1000 and 1000
    }

    start = high_resolution_clock::now();

    msort(arr, n, threshold);

    end = high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << arr[0] << std::endl;
    std::cout << arr[n-1] << std::endl;       // Last element of the sorted array
    std::cout << duration.count() << std::endl; // Time taken in milliseconds

    return 0;
}
