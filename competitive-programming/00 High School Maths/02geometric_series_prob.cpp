#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <string>

//P(smallR hitting) = a/b
//P(Zanoes hitting) = c/d
//P(smallR hitting first) = ?

/*P(small R winning) = a/b + (1-a/b)(1-c/d)a/b + (1-a/b)(1-c/d)(1-a/b)(1-c/d)a/b
    = a/b [1 + (1-a/b)(1-c/d) + ((1-a/b)(1-c/d))^2 + cube + quad + ...]
    = a/b (converging geomteric series with common diff (1-a/b)(1-c/d))
*/


int main()
{
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;

    double common_diff = (1.0-(double)a/b)*(1.0-(double)c/d);

    double prob = (double)a/b;
    prob /= 1-common_diff;

    std::cout << std::setprecision(20) << prob;
}

