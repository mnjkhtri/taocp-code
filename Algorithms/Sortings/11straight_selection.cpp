#include <iostream>
using namespace std;
struct Records
{
    int Key;
};
void straight_selection(int, Records *);

int main()
{
    const int N = 16;
    Records Recs[1+N] = {0, 503, 87, 512, 61, 908, 170, 897, 275, 653, 426, 154, 509, 612, 677, 765, 703};
    straight_selection(N, Recs);

    for (int i = 1; i <= N; ++i)
        cout << Recs[i].Key << " ";
}

void straight_selection(int N, Records *Recs)
{
    //for every element from last, we find maximum in the array left to them;
    for (int i = N; i >= 2; --i)
    {
        //considering the selected element as maximum s and we check with others, if maximum is found we replace it.
        int k = i;
        int M = Recs[k].Key;

        //checking maximum left to the selected array
        for (int j = i-1; j>= 1; --j)
        {
            if (Recs[j].Key > M)
            {
                k = j;
                M = Recs[j].Key;
            }
        }
        Records temp;
        temp = Recs[i];
        Recs[i] = Recs[k];
        Recs[k] = temp;
    }
}