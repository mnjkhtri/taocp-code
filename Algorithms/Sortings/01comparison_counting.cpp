#include <iostream>
using namespace std;
struct Records
{
    int Key;
};
void comparison_counting(int, Records*);
//Dear future me,

//The COUNT of keys that are less than or equal to a given key corresponds to the position of that key.

//For the smallest key; COUNT = 0. 
//For the largest key; COUNT = N-1.

int main()
{
    const int N = 16;
    Records Recs[1+N+N] = {0, 503, 87, 512, 61, 908, 170, 170, 275, 653, 426, 154, 509, 612, 677, 765, 703};

    comparison_counting(N, Recs);

    for (int i = 1+N; i <= N+N; ++i)
    {
        cout << Recs[i].Key << " ";
    }

}

void comparison_counting(int N, Records *Recs)
{
    int C[1+N];
    //The COUNT are to be incremented so let's initialize them to zeros.
    for (int i = N; i >= 1; --i)
    {
        C[i] = 1;
    }

    //The counting loop goes for N-1 elements except one as the one will eventually gets its value.
    for (int i = N; i >= 2; --i)
    {
        //The hold key is compared with every key ahead of itself.
        for (int j = i-1; j >= 1; --j)
        {
            if (Recs[i].Key < Recs[j].Key)
                ++C[j];
            else
                ++C[i];
        }
    }

    for (int i = N; i >= 1; --i)
    {
        Recs[N+C[i]] = Recs[i];
    }
}