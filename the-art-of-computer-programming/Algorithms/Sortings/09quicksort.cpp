#include <iostream>
using namespace std;
struct Coordinates
{
    int l;
    int r;
};
class Stack
{
    private:
        Coordinates* coor;
        int T;
    public:
        Stack(int N): T(0) 
        {
            //this is how you caculate floor of lgN
            int t = -1;
            while (N > 0)
            {
                cout << N << endl;
                N >>= 1;
                ++t;
            }
            coor = new Coordinates[1+t];
        }
        void push(int ll, int rr)
        {
            ++T;
            coor[T] = {ll, rr};
        }
        Coordinates pop()
        {
            --T;
            return coor[T+1];
        }
        int top()
        {
            return T;
        }
        ~Stack()
        {
            delete[] coor;
        }
};
struct Records
{
    int Key;
};


//we will have three subroutines, first checks the size of the list then sends to whichever routine is suitable.
void Quick(int, Records *, int);
void StraightInsertion(int, Records *);

int main()
{
    const int N = 16;
    const int M = 4;
    Records Recs[1+N+1] = {-90000, 503, 87, 512, 61, 908, 170, 897, 275, 653, 426, 154, 509, 612, 677, 765, 703, 9000000};
    Quick(N, Recs, M);
    for (int i = 1; i <= N; ++i)
    {
        cout << Recs[i].Key << " ";
    }
}

void Quick(int N, Records *Recs, int M)
{
    if (N <= M)
    {
        StraightInsertion(N, Recs);
    }
    //get the stack ready
    Stack S(N);
    // l points to first element of the list, r to the last, comes handy in calculating the size of the sublists
    int l = 1;
    int r = N;

    //an infinite loop that only breaks when all arrays are less than M,

    //the game plan is to move the first element to its approriate position while exchanging on ways elements to their appropriate place    
    //here lth element if to be placed so i and j will point
    //to just before and after it
    while(1)
    {
        int i = l;
        int j = r+1;
        int Km = Recs[l].Key;
        
        //Km is the key of the pivot to place

        //the inner while loop breaks only when the pivot is placed
        //and array is now ready to be divided into two parts
        while(1)
        {
            do {++i;} while(Recs[i].Key < Km);
            do {--j;} while(Recs[j].Key > Km);

            //now j will be pointing the element just placed on its position, 
            //while i will be pointing just one step ahead of it.
            
            if (i < j)
            {
                Records temp;
                temp = Recs[i];
                Recs[i] = Recs[j];
                Recs[j] = temp;
            }
            else
            {
                Records temp;
                temp = Recs[l];
                Recs[l] = Recs[j];
                Recs[j] = temp;
                break;
            }
        }
        //now we see size of the pivoted array, we push larger one and work on smaller one. 
        //if left is small than right - we work on left and push right
        //if right is small than left - we work on right and push left
        //if equal we push right and work on left

        //rightt array >= left array; both of them > M, so push right array and work on  left array.
        if (r-j >= j-l && j-l > M) {S.push(j+1,r); r=j-1; cout << " working array: " << l << " " << r << endl;}

        //left array > right array; both of them > M, so push left and work on right.
        else if (j-l > r-j && r-j > M) {S.push(l,j-1); l=j+1; cout << " working array: " << l << " " << r << endl;}

        //right array is greater than M but left is not; so work on right
        else if (r-j > M && M >= j-l) {l=j+1; cout << " working array: " << l << " " << r << endl;}

        //left array is greater than M but right is not; so work on right
        else if (j-l > M && M >= r-j) {r=j-1; cout << " working array: " << l << " " << r << endl;}
        else 
        {
            if (S.top() == 0) 
                {
                StraightInsertion(N, Recs);
                break;
                } 
            Coordinates temp; 
            temp = S.pop(); 
            l = temp.l; 
            r = temp.r;
            cout << " working array: " << l << " " << r << endl;
        }
    }
}
void StraightInsertion(int N, Records *Recs)
{
    cout << "after only quick  part is done" << endl;
    for (int i = 1; i <= N; ++i)
    {
        cout << Recs[i].Key << " ";
    }
    cout << endl;
    for (int j = 2; j <= N; ++j)
    {
        if (Recs[j].Key < Recs[j-1].Key)
        {
            int Km = Recs[j].Key;
            Records Rm = Recs[j];
            int i = j-1;
            do
            {
                Recs[i+1] = Recs[i];
                --i;
            } while (Recs[i].Key > Km);
            Recs[i+1] = Rm;
        }
    }

}