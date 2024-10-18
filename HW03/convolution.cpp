#include "convolution.h"
#include <iostream>
#include <omp.h>

float fval(const float *image, std::size_t x, std::size_t y, std::size_t n){
    if ((x>=0 && x<n) && (y>=0 && y<n) ){
        return image[x*n+y];
    }
    if ((x>=0 && x<n) || (y>=0 && y<n) ){
        return 1.0f;
    }    
    return 0.0f;
}


void convolve(const float *image, float *output, std::size_t n, const float *mask, std::size_t m){
    #pragma omp parallel for 
    for(int x = 0; x <n; x++){
        for(int y = 0; y < n; y++){
            for(int i = 0; i < m; i++){
                for(size_t j = 0; j < m; j++){
                    output[x*n+y] += mask[i*m+j]*fval(image,x+i-(m-1)/2,y+j-(n-1)/2,n);
                }
            }
        }    
    }
}


