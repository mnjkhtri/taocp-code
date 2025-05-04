#include <iostream>
using namespace std;
struct Records
{
    int Key;
};
void batchers_parallel(int, Records *);

int main()
{
    const int N = 17;
    Records Recs[1+N] = {0, 503, 87, 512, 61, 908, 170, 897, 275, 653, 426, 154, 509, 612, 677, 765, 703, 24};

    batchers_parallel(N, Recs);

    //first N must be greater than equal to 2.

    //just like the idea of shell, batchers made an algorithm to sort distinct elements
    //here he does by exchanging distant elements as in order of powers of 2
    //for eg if there are 17 elements, first sort the elements that are 16 unit apart which is 1-17
    //then do for 8 unit parts like 1-9, 2-10 ... 8-16, here 9-17 was supposed to be part, but since 9 is already used, 
    //we separate it for later to allow simultaneioty.

    for (int i = 1; i <= N; ++i)
    cout << R[i].Key << " ";
}

void batchers_parallel(int N, Records *Recs)
{
    //ceil(lgN) is the integer t such that 2^t>=N
    int t = 1;
    while (1 << t < N)
    {
        ++t;
    }
    int p = 1 << (t-1);

    //one iteration of this loop sorts the array in p orderednessc
    do
    {
        int q = 1<<(t-1);
        int r = 0;
        int d = p;
        while(1)
        {
            for (int i = 0; i <= N-d-1; ++i)
            {
                if ((i&p) != r)
                {
                    continue;
                }
                cout << i+1 << "+" << i+d+1 << " ";
                if (R[i+1].Key > R[i+d+1].Key)
                {
                    Records temp;
                    temp = R[i+1];
                    R[i+1] = R[i+d+1];
                    R[i+d+1] = temp;
                }
            }
            cout << " ... ";
            if (q == p)
            {break;}
            d = q-p;
            q = q/2;
            r = p;
        }
        cout << endl;
        p = p >> 1;
        cout << endl;
    } while (p > 0);
}