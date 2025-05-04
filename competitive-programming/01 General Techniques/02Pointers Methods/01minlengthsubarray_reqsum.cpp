#include <iostream>

//To find the minimum length of subarray that exists such that sum(subarray) >= required
int find_minlength(int* arr, const int N, int reqiured);

int main()
{
    const int N = 8;
    int required = 5;
    int arr[N] = {1,3,2,5,1,1,2,3};
    std::cout << find_minlength(arr, N, required);
    return 0;
}

//In kadane's left index was updated implicitly, here we need an explicit pointer
//As the right index moves, update the sum and based on it's value update the left pointer (and the best answer)
int find_minlength(int* arr, const int N, int required)
{
    int left = 0;   //the explicit left pointer

    int minlength = INT_MAX;
    int current_sum = 0;
    for (int j = 0; j < N; ++j)
    {
        current_sum += arr[j];
        //Given the current sum we update the left pointer as long as the condition matches
        while (current_sum >= required)
        {
            minlength = std::min(minlength, j-left+1);
            //now move the left pointer but update current sum first

            current_sum -= arr[left];
            left++;
        }
    }
    return minlength;
}


