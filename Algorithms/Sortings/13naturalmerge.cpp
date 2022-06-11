#include <iostream>
using namespace std;
struct Records
{
    int Key;
};
bool natural_merge(int, Records *);
int main()
{
    const int N = 21;
    Records Recs[1+N+N] = {0, 12, 503, 87, 512, 61, 908, 170, 897, 275, 32, 353, 2323, 653, 426, 154, 509, 612, 677, 765, 703, 99};
    bool where = natural_merge(N, Recs);

    // s = 0 we will find in the later part of the arrray.
    if (where == true)
    {
        for (int i = 1; i <= N; ++i)
        cout << Recs[i].Key << " ";
    }
    else
    {
        for (int i = 1+N; i <= N+N; ++i)
        cout << Recs[i].Key << " ";
    }
}

bool natural_merge(int N, Records *Recs)
{
    int s = 0;
    int i, j, k, l;


    //this loop ends after the sorting is completed, the break point is when f equals 1
    while(1)
    {

        //s == 0 means we are transferring the records from 1-N to N+1-2N as we are merging them.
        //i, j will store the indexes of array to transfer, 
        //k, l will include where we are transfering.

        // i will point to the left element on the current array to transfer, while j will point to the right element on array to transfer
        // k will point to the place to transfer on left, while l will point to the right place available to transfer.
        if (s == 0)
        {
            //for transfering left to right, i and j points to the left array
            //and k and l will point to the right array
            i = 1; j = N; k = N+1; l = N << 1;
        }
        else
        {
            //else the opposite
            i = N+1; j = N << 1; k = 1; l = N;
        }

        //d gives the direction of increment
        int d = 1;

        //f will be later set to zero if more passes are necessary.
        int f = 1;

        //this loop does transfer a block of elements from one side to another
        while(1)
        {
            if (Recs[j].Key < Recs[i].Key)    //if K[j] is less than K[i] we will transmit j to the next array.
            {
                Recs[k] = Recs[j];    //this transfers the records
                k += d;     //this moves the k 
                --j;    //this decreases the j, now also j and k point to whatever they were required to do.

                //this condition checks wheher the next element to j is greater, if greater than we continue comparing 
                if (Recs[j].Key >= Recs[j+1].Key) {continue;}
                
                //now j's part is done transmitting now we transmit the i's part untill we encounter a hurdle.
                do
                {
                    Recs[k] = Recs[i];
                    k += d;
                    ++i;

                    //we do that unil the less element is encountered.
                } while (Recs[i].Key >= Recs[i-1].Key);

            }
            else        //ok K[j] is not less that of i so lets check if we have to transmit i or break the loop
            {
                if (i == j) //ohh we are on the same index, here Keys weould be equal so lets transmit this space and break the loop.
                {
                    Recs[k] = Recs[i];    //in this case k and l would also be equal.
                    break;
                }

                //ok so now we can transmit the i's elements
                Recs[k] = Recs[i];    //copy the record
                k += d;     //move the place
                ++i;    //increment the index.

                if (Recs[i].Key >= Recs[i-1].Key)
                {
                    continue;   //now lets check if the transmitting process of i is to be continued stopeed, we continue as long as we find greater or equal elements on the right.
                }

                //now  we stop transmitting i and transmit j now.
                do
                {
                    Recs[k] = Recs[j];
                    k += d;
                    --j;

                    //we will do that as long as we find the greater or equal element on left.
                } while (Recs[j].Key >= Recs[j+1].Key);
                
            }


            //we are done transmitting the first stage of the elements but we have more element to do so lets switch SIDES, now we trasmit to the right side of the next array.
            f = 0;

            //now the direction is changed.
            d = -d;

            //lets change the position of k and l to do so.
            int temp; temp = k; k = l; l = temp;
        }

        // we are here now because we broke from the position we asked for i == j meaning that the array is sorted good.
        if (f == 0) {s = 1-s;}
        else {break;}
    }
    return s;
    
}