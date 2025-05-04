#include <iostream>
using namespace std;
const int N = 16;
struct Records
{
    int Key;
};
int sequential1(int, Records*);

int main()
{
    Records Recs[1+N+1] = {0, 503, 87, 512, 061, 908, 170, 275, 653, 426, 154, 509, 612, 677, 90, 765, 703};
    Recs[N+1].Key = 509;
    cout << sequential1(N, Recs);

}

int sequential1(int N, Records* Recs)
{
    int i = 1;
    int K = Recs[N+1].Key;
    
    while (K != Recs[i].Key)
    {
        ++i;
    }
    if (i <= N)
    {
        return i;
    }
    else
    {
        cout << "not found";
        return 0;
    }
}