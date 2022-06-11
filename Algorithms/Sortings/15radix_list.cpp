#include <iostream>
using namespace std;
struct Records
{
    int Key;
    Records* L;

    Records(): Key(0), L(nullptr) {}
    Records(int k): Key(k), L(nullptr) {} 
};
Records* radix_list(int, Records*, int, int, Records**, Records**);
int main()
{
    const int N = 16;
    Records R[N+1] = {0, 503, 87, 512, 61, 908, 170, 897, 275, 653, 426, 154, 509, 612, 677, 765, 703};
    const int m = 4;    //2^m will be the base so here 16 is base 
    const int p = 3;    //3 digits of 16 base, no of digits in that base
    
    Records* T[1<<m];  //array of top pointers for the queue;
    Records* B[1<<m];
    Records* Q = radix_list(N, R, m, p, T, B);
    
    while (Q > 0)
    {
        cout << Q->Key << " ";
        Q = Q->L;
    }
    
}
Records* radix_list(int N, Records* R, int m, int p, Records** T, Records** B)
{
    Records* P;     //P will be after returning pointing to the element of smallest key
    int M = 1 << m; //now we will be needing the
                    //bottom pointers for the queue;
    P = R+N;  //initially P starts by pointing to the last element of the record

    for (int k = 1; k <= p; ++k)    //k be be the ?th digit of the key so at first we work with 1st digit
    {
        for (int j = 0; j <= M-1; ++j)
        {
            T[j] = nullptr;     //setting them emtpy
            B[j] = nullptr;
        }

        while(1)
        {
            //i is the kth digit of base M in pointer P record key;
            int i = ((P->Key)>>(m*(k-1)))&(M-1);
            
            //after getting the value of i we weave that record to ith queue
            if (T[i] == 0)
            {
                B[i] = P;
                T[i] = P;
            }
            else
            {
                T[i]->L = P;
                T[i] = P;
            }

            //lets go to next record, depending on the value of k, if and else combination does that
            
            //if were working on the first k means that we donot have the link between the nodes so we have to work like sequentailly
            if (k == 1)
            {
                int j = P - R;  //R points to the base(not first) element of the records array
                                //P points to the last element of that array
                
                //j being equal means there was only one key
                if (j != 1)
                {
                    //if there are more than one key let P point to the second last and we go gain
                    P = &R[j-1];
                }
                else
                {
                    //if there was only one then break
                    break;
                }
            }
            else
            {
                //in case of not first iteration, we already have linked formed so lets move on to the next link of P
                P = P->L;
                //finally if P reaches null we break
                if (P == 0)
                {
                    break;
                }
            }
        }
        
        //cout <<endl << "current tops of queues: " << endl;
        //for (int i = 0; i <= M-1; ++i)
        //{
        //    if (T[i] == nullptr)
        //    {
        //        cout << "empty" << " ";
        //    }
        //    else
        //    {
        //        cout << T[i]->Key << " ";
        //    }
        //}

        //After sorting on the kth key now lets weaave the list togethers

        int i = 0;

        while(1)
        {
            P = T[i];

            Next:
            ++i;

            if (i == M)
            {
                P->L = nullptr;
                P = B[0];
                break;
            }

            //if the pile is empty we skip it and find another non empty pile
            if (B[i] == 0)
            {
                goto Next;
            }

            //now non empty pile is found so lets hook it up.
            P->L = B[i];
        }
        //nothing here, break will take us here. so we can print the hooked queue here.
        //cout << "the weaved list after sorting on digit "<< k << "looks like" << endl;
    }
    return P;
}