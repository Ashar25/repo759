#include "convolution.h"
#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <new> 

using std::cout;
using std::chrono::high_resolution_clock;
using std::chrono::duration;


int main(int arg, char* argv[]) {
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    std::random_device rd;   
    std::mt19937 gen(rd());  
    std::uniform_real_distribution<> dis(-10, 10);   // I found this through ChatGPT
    std::uniform_real_distribution<> dism(-1, 1);   // I found this through ChatGPT
    size_t n = std::stoi(argv[1]); size_t m = std::stoi(argv[2]); 
    duration<double, std::milli> duration_sec;
    float *image = (float*)malloc(n*n * sizeof(float));
    float *mask = (float*)malloc(m*m * sizeof(float));
    float *output = (float*)calloc(n*n ,sizeof(float));  // Found this on through ChatGPT to allocate memory but also initialize it to zero
     // Question b (i)
    for (std::size_t i = 0; i < n*n; ++i) {
        image[i] = dis(gen);
    }
    //
    // Question b (ii)
    for (std::size_t i = 0; i < m*m; ++i) {
        mask[i] = dism(gen);
    }
    //
    // Question b (iii)
    start = high_resolution_clock::now();
    convolve(image, output, n,mask,m);
    end = high_resolution_clock::now();
    //


    // for (std::size_t i = 0; i < n*n; ++i) {
    //     cout << output[i] << " ";
    // }

    // Convert the calculated duration to a double using the standard library
    duration_sec = std::chrono::duration_cast<duration<double, std::milli> >(end - start);
    // // Question b (iv)
    // Durations are converted to milliseconds already thanks to std::chrono::duration_cast
    cout << "\n" << duration_sec.count()<<"ms\n";
    // Question b (v)
    std::cout << output[0] << " \n";
    // Question b (vi)
    std::cout << output[(n*n)-1] << " ";  // Found through Chatgpt
    // Question b (vii)
    delete[] image;
    delete[] mask;
    delete[] output;
}