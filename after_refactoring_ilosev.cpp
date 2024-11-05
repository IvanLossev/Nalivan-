#include <cmath>   
#include <iostream>


int main()
{
    const int size = 20;
    int massive[size];


    for (int i = 0; i < size; i++)
    {
        massive[i] = rand() % size;
        std::cout << massive[i] << " ";
    }

    std::cout << "\n";

    for (int i = 0; i < size / 2; i++)
    {
        std::swap(massive[i], massive[size - 1 - i]);
    }

    for (int i = 0; i < size; i++)
    {
        std::cout << massive[i] << " ";
    }

    return 0;
}
