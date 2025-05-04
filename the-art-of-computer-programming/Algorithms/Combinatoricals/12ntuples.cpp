//the idea is to present the possibilites of a combinatorical universe in some data structures
#include <iostream>
#include <bitset>
using namespace std;


//to run from 000000 to 11111 just add 1 to the system and same for other base systems
//more generally to generate (a1,...,an) where 0 <= aj < mj where mj might be different for different ajs but note that ms cannot be zeros
int main()
{
	const int n = 4;
	int a[n+1], m[n+1];		//a[0] is for convenience 
	for (int i = 0; i <= n; ++i)
	{
		a[i] = 0;
	}
	m[0] = 2;	//mo is also for conveience;
	m[1] = 2;
	m[2] = 2;
	m[3] = 2;
	m[4] = 2;
	while(1)
	{
		for (int i = 1; i <= n; ++i)
		{
			cout << a[i];
		}
		cout << endl;
	
		int j = n;
		while(a[j] == (m[j]-1))
		{
			a[j] = 0;
			j--;
		}
		if (j == 0)
		{
			break;
		}
		else
		{
			a[j] += 1;
		}
	}
	
	//while when n is small then just make the nested loops of n = something
	
	return 0;
}