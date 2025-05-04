#include <iostream>
#include <utility>
#include <algorithm>

//Given an array find the pairs such that their sum = required
std::pair<int,int> find_pairs(int* arr, int N, int required);

int main()
{
    const int N = 8;
    int arr[N] = {1,3,2,5,1,1,3,1};

    int required = 7;

    std::pair<int,int> tmp = find_pairs(arr, N, required);
    std::cout << tmp.first << " " << tmp.second;
    return 0;

}

std::pair<int,int> find_pairs(int* arr, int N, int required)
{
    //Need to sort first
    std::sort(arr, arr+N);    

    //left and right pointers
    int left = 0;
    int right = N-1;

    while (left < right)
    {
        if (arr[left]+arr[right] == required)
        {
            return std::make_pair(left,right);
        }
        //If sum is less, then we need to increase the sum moving the left pointer
        if (arr[left]+arr[right] < required)
        {
            left++;
            //right--;
        }
        else
        {
            //left++;
            right--;
        }
    }
    return std::make_pair<int,int>(-1,-1);
}
