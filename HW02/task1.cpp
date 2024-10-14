// main.cpp

#include "scan.h"
#include <iostream>
#include <random>
#include <ctime>
#include <chrono>


using std::cout;
using std::chrono::high_resolution_clock;
using std::chrono::duration;


int main(int argc, char* argv[]) {
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    std::random_device rd;   
    std::mt19937 gen(rd());  
    std::uniform_real_distribution<> dis(-1, 1);   // I found this through ChatGPT
    size_t n = std::stoi(argv[1]);
    duration<double, std::milli> duration_sec;
    float *arr = (float*)malloc(n * sizeof(float));
    float *output = (float*)malloc(n * sizeof(float));

    // Question b (i)
    for (std::size_t i = 0; i < n; ++i) {
        arr[i] = dis(gen);
    }
    //

    // Q b (ii,iii)
    start = high_resolution_clock::now();
    scan(arr, output, n);
    end = high_resolution_clock::now();
    //

    // Convert the calculated duration to a double using the standard library
    duration_sec = std::chrono::duration_cast<duration<double, std::milli> >(end - start);
    
    // Durations are converted to milliseconds already thanks to std::chrono::duration_cast
    cout  << duration_sec.count()<<"\n";


    // std::cout << "Generated array of random floats:" << std::endl;
    // for (std::size_t i = 0; i < n; i++) {
    //     std::cout << output[i] << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "Input array: ";
    // for (std::size_t i = 0; i < n; i++) {
    //     std::cout << arr[i] << " ";
    // }
    // std::cout << std::endl;


    // Q b (iv,v,vi)
    std::cout << output[0] << " \n";
    std::cout << output[n-1] << " ";  // Found through Chatgpt
    free(arr); free(output);
    //
    return 0;
}
