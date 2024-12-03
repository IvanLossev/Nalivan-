#include "output.hpp"
#include "sorting.hpp"

int main (){
    int arr[] = {4, 2, 6, 8, 1, 3, 0};
    const int size = sizeof(arr) / sizeof(arr[0]);

    task2::print("Массив для сортировки: ", arr, size);
    task2::sorting::bubbleSort(arr, size);
    task2::print("Отсортированный массив: ", arr, size);

    return 0;
}