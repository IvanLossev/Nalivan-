#include "output.hpp"
#include <iostream>

void task2::print(const char* const comment, int* arr, const int size){
    std::cout << comment;
    const char space = ' ';
    for(int i = 0; i < size; ++i){
        std::cout << arr[i] << space;
    }
    std::cout << std::endl;
}