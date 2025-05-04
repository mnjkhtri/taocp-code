#include <iostream>
using namespace std;
struct Records
{
    int Key;
};
void twoway_merge(int, Records *);

int main()
{
    //we merge the uneven lists as well, if there are 4 elements on the left and one on the right we merge them as well, 
    //eg in third group
    //32 223 275 653  - 353 they are merged in this way.

    const int N = 21;
    //careful when putting the total value of array elements
    Records Recs[1+N<<1] = {0, 12, 503, 87, 512, 61, 908, 170, 897, 275, 32, 353, 223, 653, 426, 154, 509, 612, 677, 765, 703, 99};

    //s = 0 we will find in later part of the array, which will be if ceil(lgN) is odd
    twoway_merge(N, Recs);
    for (int i = 1; i <= N; ++i)
        cout << Recs[i].Key << " ";
        cout << endl;

    for (int i = N+1; i <= 2*N; ++i)
        cout << Recs[i].Key << " ";
        cout << endl;
}

void twoway_merge(int N, Records *Recs)
{
    int s = 0;  //s is same: the direction of shifting the array
    int p = 1; //Here p represents the size of ascending runs to be merged on the current pass so lets start with 1
    int i, j, k, l;


    while(1)
    {

        //i will point to the first element of array to shift, j to the last,
        //k and l point just a unit shift to the vacant place to shift.
        if (s == 0)
        {
            i = 1; j = N; k = N; l = (N << 1) + 1;
        }
        else
        {
            i = N+1; j = N << 1; k = 0; l = N + 1;
        }

        int d = 1;

        //p and q will keep track of unmerged items in the current run
        int q = p;
        int r = p;

        while(1)
        {
            //if less then lets transmit j,
            if (Recs[j].Key < Recs[i].Key)
            {
                //first get the appropriate value of k;
                k+=d;
                //now put on the place
                Recs[k] = Recs[j];
                --j;    //now point j to the good value
                --r;    //as we put one value from right we decerase r by 1.
                
                //are there still elements left on the right side of the array. if yes continue else proceed.
                if(r > 0) {continue;}


                ContinueTransmit:
                //now lets transmit the left part of the array unit we have nothing to pass.
                do
                {
                    k += d;
                    
                    //means the place we want to insert is already oocupies so lets change areas. so jump off bitch.
                    if (k == l)
                    {
                        goto SwitchAreas;
                    }
                    Recs[k] = Recs[i];
                    ++i;
                    --q;

                } while (q > 0);

            }
            else
            {
                //as j was not greater we shift the left elements
                k += d;
                Recs[k] = Recs[i];
                ++i;
                --q;

                if (q > 0) {continue;}

                do
                {
                    k += d;
                    

                    //occupied so lets jump to changing areas.
                    if (k == l)
                    {
                        goto SwitchAreas;
                    }
                    Recs[k] = Recs[j];
                    --j;
                    --r;

                } while (r > 0);
                
            }

            //Change the sides here.

            q = p;  //q and p will retain their values because we are changing sides and not areas
            r = p;

            //change the direction of transfer,
            d = -d;
            int temp; temp = k; k = l; l = temp;

            //if the list if smaller or equal to the value of p we just paste them as it is, no point in merging by comparison.
            
            //here if we cannot find lists greater than p, like in grp 4: here last elements 653, 353, 275, 223, 32 are just pasted from the right because the size is 5 (which do not exceeded the current value of p which was 8)
            if (j - i < p)
            {
                goto ContinueTransmit;
            }
        }

        SwitchAreas:

        for (int i = 1; i <= N; ++i)
        cout << Recs[i].Key << " ";
        cout << endl;

        for (int i = N+1; i <= 2*N; ++i)
        cout << Recs[i].Key << " ";
        cout << endl << endl;

        p = p << 1;
        if (p < N)
        {
            s = 1-s;
        }
        else
        {break;}
    }
    
}