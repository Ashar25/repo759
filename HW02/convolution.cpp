#include "convolution.h"
#include <iostream>


float fval(const float *image, std::size_t x, std::size_t y, std::size_t n){
    if ((x>=0 && x<n) && (y>=0 && y<n) ){
        return image[x*n+y];
    }
    if ((x>=0 && x<n) || (y>=0 && y<n) ){
        return 1.0f;
    }    
    return 0.0f;
}

// float fval(const float *image, std::size_t x, std::size_t y, std::size_t n){
//     if ((x<=0 || x>n) && (y<=0 || y>n) ){
//         return 0.0f;
//     }
//     if ((x>=0 && x<n) && (y>=0 && y<n) ){
//         return image[x*n+y];
//     }
//     return 1.0f;     
// }
void convolve(const float *image, float *output, std::size_t n, const float *mask, std::size_t m){
    for(std::size_t x = 0; x <n; x++){
        for(std::size_t y = 0; y < n; y++){
            for(std::size_t i = 0; i < m; i++){
                for(std::size_t j = 0; j < m; j++){
                    output[x*n+y] += mask[i*m+j]*fval(image,x+i-(m-1)/2,y+j-(n-1)/2,n);
                }
            }
        }    
    }
}
