#include <iostream>
using namespace std;
struct Records
{
    int Key;
};
void distribution_counting(Records *, int, int);
//This should be done for keys only in small range. 
//Taking the last digit from the old record so the keys are in the double digit range.
//The keys are from 1-100

int main()
{
    const int N = 16;
    const int M = 100;
    Records Recs[1+N+N] = {0, 50, 87, 51, 61, 90, 17, 89, 27, 63, 42, 15, 50, 62, 67, 75, 70};

    distribution_counting(Recs, N, M);
    //where does jth (starting from last to 1st) element belong? To C[K[j]]

    for (int i = 1+N; i <= N+N; ++i)
    {
        cout << Recs[i].Key << " ";
    }
}

void distribution_counting(Records *Recs, int N, int M)
{
    int C[1+M];
    //as before the count are to be incremented so lets initialize them to zero.
    for (int i = M; i >= 1; --i)
    {
        C[i] = 0;
    }
    //this loop runs over each element, as it encounters a key it increases the respective index of the count array.
    //here C[i] array has the number of keys that equal i
    for (int i = N; i >= 1; --i)
    {
        ++C[Recs[i].Key];
    }

    //this is a cumilative loop that adds the keys before of the given key
    //now the array will have the count of keys that are less than the given key but wrt to the keys not position.
    for (int i = 2; i <= M; ++i)
    {
        C[i] += C[i-1];
    }

    for (int i = N; i >= 1; --i)
    {
        int k = C[Recs[i].Key];
        Recs[N+k] = Recs[i];
        C[Recs[i].Key] = k-1;
    }
}