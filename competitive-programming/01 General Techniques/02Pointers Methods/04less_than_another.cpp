#include <iostream>

//Return the number of smaller elements in array1 than the ith element in array2
void number_of_smaller(int* arr1, int* arr2, int *result, int N);

int main()
{
    const int N = 6;
    int arr2[N] = {1, 6, 9, 13, 18, 18};
    int arr1[N] = {2, 3, 8, 13, 15, 21} ;
    int result[N];
    number_of_smaller(arr1, arr2, result, N);
    for (int i = 0; i < N; ++i)
    {
        std::cout << result[i] << " ";
    }
    return 0;
}

void number_of_smaller(int* arr1, int* arr2, int *result, int N)
{
    int smaller_than_i = 0;
    int second_pointer = 0;
    for (int i = 0; i < N; ++i)
    {
        //For the ith element in array2 we fast run the second pointer
        while (second_pointer < N)
        {
            if (arr1[second_pointer] < arr2[i])
            {
                smaller_than_i += 1;
                second_pointer += 1;
            }
            else
            {
                break;
            }
        }
        result[i] = smaller_than_i;
    }
}