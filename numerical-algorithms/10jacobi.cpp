#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
	int N;
	cout << "enter number of variables" << endl;
	cin >> N;
	float a[10][10];
	
	cout << "enter the elements of the matrix rowwise" << endl;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N+1; ++j)
		{
			cin >> a[i][j];
		}
	}

	float x[10], x0[10];
	float maxerror;
	cout << "give your initial guess" << endl;
	for (int i = 1; i <= N; ++i)
	{
		cin >> x0[i];
	}
	
	do
	{
		//this loop is for one iteration
		for (int i = 1; i <= N; ++i)
		{
			maxerror = 0;
			float sum = 0;
			for (int j = 1; j <= N; ++j)
			{
				if (j != i)
				{
					sum += a[i][j]*x0[j];
				}
			}
			x[i] = (a[i][N+1]-sum)/a[i][i];			
			//this thing here calculates the error
			if (abs(x[i]-x0[i]) > maxerror)
			{
				maxerror = abs(x[i]-x0[i]);
			}
		}
		
		for (int i = 1; i <= N; ++i)
		{
			cout << setw(15) << x[i];
		}
		cout << endl;
		//this is essentailly X0 = X;
		for (int i = 1; i <= N; ++i)
		{
			x0[i] = x[i];
		}
	}while(maxerror > 0.00001);
	
	for (int i = 1; i <= N; ++i)
	{
		cout << setw(15) << x[i];
	}
}