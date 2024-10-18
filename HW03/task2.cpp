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
    size_t n = std::stoi(argv[1]); size_t t = std::stoi(argv[2]);
    size_t m = 3; 
    duration<double, std::milli> duration_sec;
    float *image = (float*)malloc(n*n * sizeof(float));
    float *mask = (float*)malloc(m*m * sizeof(float));
    float *output = (float*)calloc(n*n ,sizeof(float));  // Found this on through ChatGPT to allocate memory but also initialize it to zero
    for (std::size_t i = 0; i < n*n; ++i) {
        image[i] = dis(gen);
    }
    for (std::size_t i = 0; i < m*m; ++i) {
        mask[i] = dism(gen);
    }
    omp_set_num_threads(t);
    start = high_resolution_clock::now();
    convolve(image, output, n,mask,m);
    end = high_resolution_clock::now();

    // Convert the calculated duration to a double using the standard library
    duration_sec = std::chrono::duration_cast<duration<double, std::milli> >(end - start);
    std::cout << output[0] << " \n";
    std::cout << output[(n*n)-1] << " ";  // Found through Chatgpt
    cout << "\n" << duration_sec.count()<<"ms\n";


    free(image);
    free(mask);
    free(output);
}
