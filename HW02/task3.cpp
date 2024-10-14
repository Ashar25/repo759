#include "matmul.h"
#include <iostream>
#include <random>
#include <ctime>
#include <chrono>

using std::cout;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

int main(){
    const unsigned int n = 1024;
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    std::random_device rd;   
    std::mt19937 gen(rd());  
    std::uniform_real_distribution<> dis(-1, 1);   // I found this through ChatGPT
    duration<double, std::milli> duration_sec1; 
    duration<double,std::milli> duration_sec2;
    duration<double,std::milli> duration_sec3;
    duration<double,std::milli> duration_sec4;
    // duration<double,std::milli> duration_sec4;
    double *A = (double*)malloc(n*n * sizeof(double));
    double *B = (double*)malloc(n*n * sizeof(double));
    double *C = (double*)malloc(n*n * sizeof(double));
    
    for (std::size_t i = 0; i < n*n; ++i) {
        A[i] = dis(gen);
    }
    for (std::size_t i = 0; i < n*n; ++i) {
        B[i] = dis(gen);
    }
    cout << n << "\n";

    for (std::size_t i = 0; i < n*n; ++i) {
        C[i] = 0;  // Reset matrix C to 0
    }

    start = high_resolution_clock::now();
    mmul1(A, B, C,n);
    end = high_resolution_clock::now();
    duration_sec1 = std::chrono::duration_cast<duration<double, std::milli> >(end - start);
    // Durations are converted to milliseconds already thanks to std::chrono::duration_cast
    cout << duration_sec1.count()<<" ms\n";
    cout << C[(n*n)-1]<<"\n";

    for (std::size_t i = 0; i < n*n; ++i) {
        C[i] = 0;  // Reset matrix C to 0
    }

    start = high_resolution_clock::now();
    mmul2(A, B, C,n);
    end = high_resolution_clock::now();
    duration_sec2 = std::chrono::duration_cast<duration<double, std::milli> >(end - start);
    // Durations are converted to milliseconds already thanks to std::chrono::duration_cast
    cout << duration_sec2.count()<<" ms\n";
    cout << C[(n*n)-1] << "\n";
    
    for (std::size_t i = 0; i < n*n; ++i) {
        C[i] = 0;  // Reset matrix C to 0
    }

    start = high_resolution_clock::now();
    mmul3(A, B, C,n);
    end = high_resolution_clock::now();
    duration_sec3 = std::chrono::duration_cast<duration<double, std::milli> >(end - start);
    // Durations are converted to milliseconds already thanks to std::chrono::duration_cast
    cout << duration_sec3.count()<<" ms\n";
    cout << C[(n*n)-1] << "\n";
	
	for (std::size_t i = 0; i < n*n; ++i) {
        C[i] = 0;  // Reset matrix C to 0
    }
	
	std::vector<double> vecA(A, A + n * n); // Copies data from A
    std::vector<double> vecB(B, B + n * n);
	// cout << "A is" <<A[0] << "\n";
	// cout << "vecA is" <<vecA[0] << "\n";  Just checking if vectors and the arrays are same.
	start = high_resolution_clock::now();
    mmul4(vecA, vecB, C,n);
    end = high_resolution_clock::now();
    duration_sec4 = std::chrono::duration_cast<duration<double, std::milli> >(end - start);
    // Durations are converted to milliseconds already thanks to std::chrono::duration_cast
    cout << duration_sec4.count()<<"ms\n";
    cout << C[(n*n)-1] << "\n";
	
    free(A);
    free(B);
    free(C);
    return 0;
}
