#include <iostream>
using namespace std;
struct Records
{
    int Key;
    int Link;   //the records must contain a link
};
void multiple_list_insertion(int, Records *, int, int);

int main()
{    //lets assume that the keys range is from 0 to 2^9
    const int N = 16;
    const int H = 32;
    Records Recs[1+N+H] = {{0, 0}, {503, 0}, {87, 0}, {512, 0}, {61, 0}, {908, 0}, {170, 0}, {897, 0}, {275, 0}, {653, 0},
                     {426, 0}, {154, 0}, {509, 0}, {612, 0}, {677, 0}, {765, 0}, {703,0}};

    //H must be power of 2
    int E = 10;
    //so the record will be in the buckets (0 to 2^10)/16 ie (0 to 2^E)/H
    //1st bucket: 0 - 63
    //2nd bucket: 64 - ...
    multiple_list_insertion(N, Recs, H, E);

    for (int i = N+1; i <= N+H; ++i)
    {
        int p = Recs[i].Link;
        while (p > 0)
        {
            cout << Recs[p].Key << " ";
            p = Recs[p].Link;
        }
    }
}
void multiple_list_insertion(int N, Records *Recs, int H, int E)
{
    for (int i = N+1; i <= N+H; ++i)
    {
        Recs[i].Link = 0;
    }
    for (int i = N; i >= 1; --i)
    {
        int Km = Recs[i].Key;
        int q = N+1+(N*Km >> E);
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