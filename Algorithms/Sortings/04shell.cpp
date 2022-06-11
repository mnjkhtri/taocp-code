#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
struct Records
{
    int Key;
};
void shell(int, Records *, int*);

int counter =0;

int main()
{
    const int N = 10000;
    Records Recs[1+N]; // = {0, 13, 7, 8, 1, 2, 3,5, 6, 343};
    for(int i=1; i<=N; ++i)
        Recs[i].Key = i;
    random_shuffle(Recs+1, Recs+N+1);

    int H[100] = {0, 1};
    for (int i = 1; i <= 25; ++i)
    {
        H[i+1] = pow(4,i)+3*pow(2,(i-1))+1;
    }
    //int H[100] = {0, 1, 3, 7, 15, 31, 62, 125, 250, 500, 1000, 2000, 4000, 8000, 16000};
    //sedwick series is 1, 5, 19, 41, 109, 209, ... with O(N^{4/3})
    //for less any is better that ends with 1
    //2^{s+1}-1 gives O(N^{3/2})
    //h(s) = 3h(s-1)+1 is just better
    //lets sharp the blade before hitting the wood
    //we sort the elements in certain gap sequence which ends with 1
    shell(N, Recs, H);

    //for (int i = 1; i <= N; ++i)
    //cout << Recs[i].Key << " ";

    cout << endl << counter << endl;
}

void shell(int N, Records *Recs, int* H)
{
    // to find the term of gap sequence
    int t = 0;
    do 
    {
        ++t;
    }
    while(H[t] <= N >> 1);
    //cout << N;

    for (int k = t; k >= 1; --k)
    {
        int h = H[k];
        //leaving h elements aheads as they will be considered first element of their respective lists that are h apart
        for (int i = h+1; i <= N; ++i)
        {
            int Km = Recs[i].Key;
            Records Rm = Recs[i];
            int j;
            for (j = i-h; j >= 1; j-=h)
            {   
                ++counter;
                //the given key is still grater than being checked key
                //this if condition implies that we have not found the position yet,
                if (Recs[j].Key <= Km)
                {
                    break;
                }
                else
                {
                    Recs[j+h] = Recs[j];
                }
            }
            Recs[j+h] = Rm;
        }
        cout << endl;
    }
}