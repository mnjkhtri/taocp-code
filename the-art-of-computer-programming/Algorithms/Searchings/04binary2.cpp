#include <iostream>
using namespace std;
struct Records
{
    int Key;
};
int binary2(int, Records*, int, int*);

int main()
{
    const int N = 16;
    Records Recs[N+1] = {-100000, 11, 87, 51, 61, 90, 170, 275, 353, 426, 554, 609, 612, 677, 690, 765, 806};
    int Km = Recs[8].Key;
	
	int t = 0;
	int c = N;
    while (c > 0)
	{
		c >>= 1;
		++t;
	}
	//the D arrays has the delts: rate of change of the pointers after each comparison
	int D[1+t+1];
	
	for (int i = 1; i <= t+1; ++i)
	{
		D[i] = (N+(1<<(i-1)))>>i;
	}
	
	cout << binary2(N, Recs, Km, D);
}

int binary2(int N, Records* Recs, int Km, int* D)
{
	
	int i = D[1]; 
	int j = 2;
	
	while(1)
	{
		if (Recs[i].Key == Km)
		{
			return i;
		}
		else
		{
			if (Recs[i].Key > Km)
			{
				if (D[j] == 0)
				{
					return -1;
				}
				else
				{
					i -= D[j];
				}
			}
			else
			{				
				if (D[j] == 0)
				{
					return -1;
				}
				else
				{
					i += D[j];
				}
			}
		}
		++j;
	}
}