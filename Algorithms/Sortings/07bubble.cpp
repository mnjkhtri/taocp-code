#include <iostream>
using namespace std;
const int N = 16;
struct Records
{
    int Key;
};
void bubble(int, Records *);

int main()
{
    Records Recs[N+1] = {0, 503, 87, 512, 61, 908, 170, 897, 275, 653, 426, 154, 509, 612, 677, 765, 703};

    bubble(N, Recs);

    for (int i = 1; i <= N; ++i)
        cout << Recs[i].Key << " ";
}
void bubble(int N, Records *Recs)
{
    int B = N;
    do
    {
    int t = 0;
        for (int i = 1; i <= B-1; ++i)
        {
            if  (Recs[i].Key > Recs[i+1].Key)
            {
                Records temp;
                temp = Recs[i];
                Recs[i] = Recs[i+1];
                Recs[i+1] = temp;
                t = i;
            }
        }
    B = t;
    } while (B > 0);
    
}