#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>

//f(some input from number line) = true if the ropes can be broken down into k pieces of that number
//one rope can have at most int(length of rope/that number) pieces of that length
//So total = S int(rope i/that number)
//Hence good is total >= k
long long n, k;
std::vector<double> lengths;

bool good(double mid)
{
    long long total = 0;
    for (long long i = 0; i < n; ++i)
    {
        total += int(lengths[i]/mid);
    }
    if (total >= k) return true; else return false;
}

int main()
{
    std::cin >> n >> k;
    lengths.resize(n);
    for (long long i = 0; i < n; ++i)
    {
        std::cin >> lengths[i];
    }

    double left = 0;  
    //Since each rope is under 1e7, no rope can have piece of 1e8
    double right = 1e8;

    for (int t = 0; t < 100; ++t)
    {
        double mid = (left+right)/2;
        if (good(mid))
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }

    //Need to do this else does not accept
    std::cout << std::setprecision(10) << left << std::endl;
}