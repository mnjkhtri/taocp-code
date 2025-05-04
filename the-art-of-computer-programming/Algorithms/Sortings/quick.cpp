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
    const int M = 4;
    
    for (int N = 10000; N <= 500000; N=N+1000)	//10 hajar dekhi 500 hajar samma hai lmao
	{
		Records Recs[1+N+1];
		for (int i = 1; i <= N; ++i)
		{
            Recs[0] = -90000000;
			Recs[i].Key = i;
		}
        Recs[N+1] = +90000000;
		random_shuffle(Recs+1, Recs+N+1);
        for (int i = 1; i <= N; ++i)
        {
        cout << Recs[i].Key << " ";
        }
		Quick(N, Recs, M);
        for (int i = 1; i <= N; ++i)
        {
        cout << Recs[i].Key << " ";
        }
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
        if (r-j >= j-l && j-l > M) {S.push(j+1,r); r=j-1;}
        else if (j-l > r-j && r-j > M) {S.push(l,j-1); l=j+1;}
        else if (r-j > M && M >= j-l) {l=j+1;}
        else if (j-l > M && M >= r-j) {r=j-1;}
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
        }
    }
}
void StraightInsertion(int N, Records *Recs)
{
    cout << "after only quick  part is done" << endl;
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