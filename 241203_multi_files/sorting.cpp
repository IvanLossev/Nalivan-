#include "sorting.hpp"

void task2::sorting::bubbleSort(int* arr, const int size){
    for(int i = 0; i < size - 1; i++){
        for(int j = 0; j < size - 1 - i; j++){
            if(arr[j] > arr[j + 1]){
                int _ = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = _;
            }
        }
    }
}