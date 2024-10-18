#include "matmul.h"
#include <iostream>
#include <random>
#include <ctime>
#include <chrono>

using std::cout;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main(int arg, char* argv[]){
    size_t n = std::stoi(argv[1]); size_t t = std::stoi(argv[2]);
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    std::random_device rd;   
    std::mt19937 gen(rd());  
    std::uniform_real_distribution<> dis(-1, 1);   // I found this through ChatGPT
    duration<double, std::milli> duration_sec; 
    float *A = (float*)malloc(n*n * sizeof(float));
    float *B = (float*)malloc(n*n * sizeof(float));
    float *C = (float*)malloc(n*n * sizeof(float));
    omp_set_num_threads(t);
    for (std::size_t i = 0; i < n*n; ++i) {
        A[i] = dis(gen);
    }
    for (std::size_t i = 0; i < n*n; ++i) {
        B[i] = dis(gen);
    }

    for (std::size_t i = 0; i < n*n; ++i) {
        C[i] = 0;  // Reset matrix C to 0
    }

    
    start = high_resolution_clock::now();
    mmul(A, B, C,n);
    end = high_resolution_clock::now();
    duration_sec= std::chrono::duration_cast<duration<double, std::milli> >(end - start);
    // Durations are converted to milliseconds already thanks to std::chrono::duration_cast
    cout << C[0] << "\n";
    cout << C[(n*n)-1] << "\n";
    cout << duration_sec.count()<<" ms\n";
    
    free(A);
    free(B);
    free(C);
    return 0;
}