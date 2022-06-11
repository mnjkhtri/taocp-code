#include <iostream>
#include <algorithm>
#include <time.h>
#include <chrono>

using namespace std;
using namespace std::chrono;
struct Records
{
    int Key;
};
void straight_insertion(int, Records *);

int main()
{
    //const int N = 16;
    //Records Recs[1+N] = {0, 503, 87, 512, 061, 908, 170, 897, 275, 653, 426, 154, 509, 612, 677, 765, 703};
    
    const int N = 10000;
    Records Recs[1+N];
    for (int i = 1; i <= N; ++i)
    {
        Recs[i].Key = i;
    }
    random_shuffle(Recs+1, Recs+N+1);

    straight_insertion(N, Recs);

    //for (int i = 1; i <= N; ++i)
        //cout << Recs[i].Key << " ";
}

void straight_insertion(int N, Records *Recs)
{
    
    auto start = chrono::high_resolution_clock::now();
    //auto start = steady_clock::now();

    //The first record is already supposed to be sorted then for second to last record we put them in position
    for (int i = 2; i <= N; ++i)
    {
        //since involves shifting the records lets save them
        int Km = Recs[i].Key;
        Records Rm = Recs[i];

        //now for every before elements, we check one by one, if its greater we shift that record one bit and 
        //finally as the sitatuion is violted we insert to its right.
        int j;
        for (j = i-1; j >= 1; --j)
        {
            //the given key is still grater than being checked key
            //this if condition implies that we have not found the position yet,
                if (Recs[j].Key <= Km)
                {
                    break;
                }
                else
                {
                    Recs[j+1] = Recs[j];
                }
        }
        Recs[j+1] = Rm;
    }
    //auto end = steady_clock::now();
    auto end = chrono::high_resolution_clock::now();
    
    auto duration = duration_cast<microseconds>(end - start);
    cout << duration.count() << endl;


}