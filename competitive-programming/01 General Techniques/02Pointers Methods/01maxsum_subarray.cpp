#include <iostream>

int naive(int* arr, int N);
int from_left_end(int* arr, int N);
int kadanes(int* arr, int N);

int main() 
{
    const int N = 8;
    int arr[N] = {-1,2,4,-3,5,3,-6,2};

    std::cout << naive(arr, N) << std::endl;
    std::cout << from_left_end(arr, N) << std::endl;
    std::cout << kadanes(arr, N) << std::endl;
}

//O(N^3)
int naive(int* arr, int N)
{
    //int best = 0;
    int best = INT_MIN;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            //For values of ij we find the sum in i-j array and update the best value
            int sum = 0;
            for (int k = i; k <= j; ++k)
            {
                sum += arr[k];
            }
            //After finding the sum we update the best
            best = std::max(sum,best);
        }
    }
    return best;
}

//O(N)
//Now instead of declaring a subarray and iterating over it to find total sum
//we declare the left index of the subarray and go on increasing the right index accumulating sum and updating the best value at each point 

int from_left_end(int* arr, int N)
{
    int best = 0;
    for (int i = 0; i < N; ++i)
    {
        //For values of i we find the best sum that begins with index i
        int sum = 0;
        //The sum is cumulative rather than abstract
        for (int j = i; j < N; ++j)
        {
            sum += arr[j];
            best = std::max(best, sum);
        }
    }
    return best;
}

//Instead of waiting at left point while right index iterates, the catch is to update the left index -
//Because if the (latest) current sum is less than 0 then it might as well start from that point as left index, reset the sum as 0 and continue the right index as it as
//If no empty subarrays are allowed then check the sum against that recent element, update the sum to its value and continue
//When all the array is negative upper gives 0 while lower gives the highest value

//O(N)
int kadanes(int* arr, int N)
{
    int best = 0;
    int sum = 0;

    for (int j = 0; j < N; ++j)
    {
        sum += arr[j];

        //Check the sum against the appropriate
        // if (sum < 0)
        // {
        //     sum = 0;
        // }

        if (sum < arr[j])
        {
            sum = arr[j];
        };
        best = std::max(sum,best);
    }
    return best;
}

/*
Idea:
Increase the subarray space and if it violates the condition then decrease its area
*/

