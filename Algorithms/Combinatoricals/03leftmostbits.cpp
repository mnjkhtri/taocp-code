//the function floor(lgx) located the leftmost bit when x>0
//with the recurrence L1 =0; L(2x)=L(2x+1)=L(x)+1 for x >0
//algorithm follows as:

//to extract the leftmost bit fikkiws:

#include <iostream>
using namespace std;

int main()
{
	unsigned long long x = 12213;
	int L = 0;
	unsigned long long y = x;
	const int d = 6;
	for (int k = d-1; k >=0; --k)
	{
		if ((y >> (1<k)) !=0 )
		{		
			L = L + (1<<k);
			y = y >> (1<<k);
		}
	}
	
	unsigned long long y = x;
	for (int k = 0; k < d; ++k)
	{
		y = y | (y >> (1<<k));
	}
	y = y - (y >> 1);
	//Lx = Lx if and only if x XOR y <= x & y
	return 0;
}