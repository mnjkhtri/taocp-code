#include <iostream>

//Given an array where each element is either true or false on some condition such that all trues are followed by falses, BS finds the last true element in the array 
int binary_search(int* arr, int N);

int main()
{
    const int N = 10;
    // int arr[N] {19, 29, 21, 42, 23, 9, 1, 6, 2, 1};
    int arr[N] {1, 2, 3, 4, 3, 9, 1, 6, 2, 1};

    std::cout << binary_search(arr, N);
}

// There must be at least one true, else the return is the first element

int binary_search(int* arr, int N)
{
    int current = 0;
    int gap = N/2;
    while (gap >= 1)
    {
        //while the condition is true
        while (arr[current+gap] > 10) current += gap;
        gap /= 2;
    }
    return current;
}

//Actually search can be performed even without concern to any N, meaning that searching space could be infinite
    /*
    Infinite space: should be at least one false so the loop does not go forever; gap = some value which puts into false region
    Finite space: limits as while (current+gap < N; order matters) current += gap; gap could be simply half of that space length
    */