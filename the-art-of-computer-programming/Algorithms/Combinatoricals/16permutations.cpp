//given sequence of n elements a1, a2, ...an intially sorted so that a1<=a2 and so on
//then generates permutations and visits them in lexicograpphical order
//to see how it works see page no 319


#include <iostream>
using namespace std;

int main()
{
	const int n = 5;
	int a[n+1] = {0, 1, 2, 3, 4, 9};
	//a[0] is auxillary which must be stricly less than a[n]
	while(1)
	{
		for (int i = 1; i <= n; ++i)
		{
			cout << a[i];
		}
		cout << endl;
		
		int j = n-1;
		while (a[j] >= a[j+1])
		{
			j--;
		}
		if (j == 0)
		{
			break;
		}
		int l = n;
		while (a[j] >= a[l])
		{
			l--;
		}
		int temp = a[j];
		a[j] = a[l];
		a[l] = temp;
		
		int k = j+1;
		l = n;
		while (k < l)
		{
			temp = a[k];
			a[k] = a[l];
			a[l] = temp;
			k++;
			l--;
		}
	}
	
	return 0;
}