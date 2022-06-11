//is it possile to just generate permuatation by adjacent interchange utrns out not for multiset but yet for set
//to see page 322
//results donot show in lexicographically

//there is more something called plain change transistions and alphanumetrics

#include <iostream>
using namespace std;

int main()
{
	int n = 3;
	int a[n+1] = {0, 1, 2, 3};	//a1,...,an will be the permutation
	int c[n+1], o[n+1];
	for (int i = 1; i <= n; ++i)
	{
		c[i] = 0;
		o[i] = 1;
	}
	
	while(1)
	{
		for (int i = 1; i <= n; ++i)
		{
			cout << a[i];
		}
		cout << endl;
		
		int j = n;
		int s = 0;
		
		p4:
		int q = c[j] + o[j];
		if (q < 0)
		{
			p7:
			o[j] = -o[j];
			j--;
			goto p4;
		}
		else if (q == j)
		{
			if (j == 1)
			{
				break;
			}
			else
			{
				s++;
				goto p7;
			}
		}

		int temp = a[j-c[j]+s];
		a[j-c[j]+s] = a[j-q+s];
		a[j-q+s] = temp;
			
		c[j] = q;
	}
	
	return 0;
}