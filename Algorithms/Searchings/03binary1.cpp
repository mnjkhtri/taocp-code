#include <iostream>
using namespace std;
struct Records
{
    int Key;
};
int binary1(int, Records*, int);

int main()
{
    const int N = 16;
    Records Recs[N+1] = {0, 11, 87, 51, 61, 90, 170, 275, 353, 426, 554, 609, 612, 677, 690, 765, 806};
    int Km = Recs[7].Key;

    cout << binary1(N, Recs, Km);

}

int binary1(int N, Records* Recs, int Km)
{
    int l = 1; 
    int u = N;
    
    while (u >= l)
    {
        int i = (u+l)>>1;
        if (Recs[i].Key == Km)
        {
            return i;
        }
        else
        {
            if (Recs[i].Key > Km)
            {
                u = i+1;
            }
            else
            {
                l = i-1;
            }
        }
    }
}