#include <iostream>
using namespace std;
struct Records
{
    int Key;
    int Link;   //the records must contain a link
};
void list_insertion(int, Records *);

int main()
{
    const int N = 16;
    // we need the first 0th record to hold the address to begin the sorted list
    Records Recs[1+N] = {{0, 0}, {503, 0}, {87, 0}, {512, 0}, {61, 0}, {908, 0}, {170, 0}, {897, 0}, {275, 0}, {653, 0},
                     {426, 0}, {154, 0}, {509, 0}, {612, 0}, {677, 0}, {765, 0}, {703,0}};

    list_insertion(N, Recs);

    int p = Recs[0].Link;
    while (p > 0)
    {
        cout << Recs[p].Key << " ";
        p = Recs[p].Link;
    }
}

void list_insertion(int N, Records *Recs)
{  
    //the first element is inserted into the list.
    Recs[0].Link = N;
    Recs[N].Link = 0;

    //we insert each record from the last.
    for (int i = N-1; i >= 1; --i)
    {
        int Km = Recs[i].Key;

        int q = 0;
        int p = Recs[q].Link;

        while (p > 0)
        {
            if (Recs[p].Key >= Km)
            {
                break;
            }
            else
            {
                q = p;
                p = Recs[q].Link;
            }
        }
        Recs[q].Link = i;
        Recs[i].Link = p;
    }



}