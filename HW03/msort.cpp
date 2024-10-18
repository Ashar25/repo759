#include "msort.h"
#include <algorithm> 
#include <cstdlib>   
#include <omp.h>
// Helper function to merge two sorted subarrays
void merge(int* arr, int* temp, std::size_t left, std::size_t mid, std::size_t right) {
    std::size_t i = left;
    std::size_t j = mid;
    std::size_t k = left;

    // Merge the two halves into temp[]
    while (i < mid && j < right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // Copy remaining elements of left subarray if any
    while (i < mid) {
        temp[k++] = arr[i++];
    }

    // Copy remaining elements of right subarray if any
    while (j < right) {
        temp[k++] = arr[j++];
    }

    // Copy temp back to the original array
    for (std::size_t l = left; l < right; ++l) {
        arr[l] = temp[l];
    }
}


// Parallel merge sort using OpenMP tasks
void parallel_merge_sort(int* arr, int* temp, std::size_t left, std::size_t right, std::size_t threshold) {
    if (right - left <= threshold) {
       std::sort(arr+left, arr+right); 
        return;
    }

    std::size_t mid = left + (right - left) / 2;

    #pragma omp task shared(arr, temp) if (right - left > threshold)
    parallel_merge_sort(arr, temp, left, mid, threshold);

    #pragma omp task shared(arr, temp) if (right - left > threshold)
    parallel_merge_sort(arr, temp, mid, right, threshold);

    #pragma omp taskwait
    merge(arr, temp, left, mid, right);
}

void msort(int* arr, const std::size_t n, const std::size_t threshold) {
    // Temporary array for merging
    int* temp = new int[n];

    // Use parallel region to enable OpenMP tasks
    #pragma omp parallel
    {
        #pragma omp single
        {
            parallel_merge_sort(arr, temp, 0, n, threshold);
        }
    }

    delete[] temp;
}
