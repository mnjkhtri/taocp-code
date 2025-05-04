#include <iostream>
using namespace std;
//is same as before but maintains an array of focus pointers instead of ainfty
//for not reasonalby large n
//why works check taocp page 290
//even better algorithm is there but why bother
int main()
{
	const int n = 10;
	int a[n];
	int f[n+1];
	for (int i = 0; i < n; ++i)
	{
		a[i] = 0;
		f[i] = i;
	}
	f[n] = n;
	
	while(1)
	{
		//vsiting part here
		for (int i = n-1; i >= 0; --i)
		{
			cout << a[i];
		}
		cout << endl;
		
		int j = f[0];
		f[0] = 0;
		if (j == n)
		{
			break;
		}
		else
		{
			f[j] = f[j+1];
			f[j+1] = j+1;
			a[j] = 1 - a[j];
		}
	}

	return 0;
}