#include <iostream>

//To maximize (distance between index)*(min of value between them)
int max_water(int* arr, int N);

int main()
{   
    const int N = 5;
    int arr[N] = {1,8,16,16,5};
    std::cout << max_water(arr, N); 
    return 0;
}

int max_water(int* arr, int N)
{
    int left = 0;
    int right = N-1;

    int max_val = 0;
    int current;

    while (left < right)
    {
        current = std::min(arr[right],arr[left])*(right-left);
        std::cout << left << " " << right << std::endl;
        if (current > max_val)
        {
            max_val = current;
        }
        //Move the pointer whichever's value is less
        if (arr[left] > arr[right])
        {

            right--;
        }
        else
        {
            left++;
        }
    }
    return max_val;
}