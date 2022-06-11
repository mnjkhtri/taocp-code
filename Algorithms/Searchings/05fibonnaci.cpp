#include <iostream>
using namespace std;
struct Records
{
    int Key;
};
//first size, then array of records, key to find, fibonacci array
int fibonacci(int, Records*, int, int*, int);

int main()
{
    const int N = 20;
	//assume N+1 to be perfect k+1 fibonacci number, in this case its 7th fibonacci number so k = 6
	//here 7th fibonacci number bitch
	int k = 6;
    Records Recs[N+1] = {0, 11, 87, 51, 61, 90, 170, 275, 353, 426, 554, 609, 612, 677, 690, 765, 806, 821, 888, 890, 234};
    int Km = Recs[8].Key;
	
	int F[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
	
	cout << fibonacci(N, Recs, Km, F, k);
}

int fibonacci(int N, Records* Recs, int Km, int* F, int k)
{
	while(1)
	{
		int i = F[k];
		int p = F[k-1];
		int q = F[k-2];
		
		if (Recs[i].Key == Km)
		{
			return i;
		}
		else
		{
			if (Recs[i].Key > Km)
			{
				if (q == 0)
				{
					return -1;
				}
				else
				{
					i -= q;
					p = q;
					q = p-q;
				}
			}
			else
			{
				if (p == 0)
				{
					return -1;
				}
				else
				{
					i += q;
					p -= q;
					q -= p;
				}
			}
		}
	}
	
}

