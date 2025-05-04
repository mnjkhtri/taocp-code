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
	float e;
	cout << "enter pemisbile error" << endl;
	cin >> e;
	
	cout << "enter the elements of the matrix rowwise" << endl;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			cin >> a[i][j];
		}
	}

	float x[10], z[10];
	cout << "give your initial guess" << endl;
	for (int i = 1; i <= N; ++i)
	{
		cin >> x[i];
	}
	
	float maxerror;	//the while condition will need this value
	
	do
	{
		maxerror = 0;
		float zmax = 0;
		for (int i = 1; i <= N; ++i)
		{
			z[i] = 0;
			for (int j = 1; j <= N; ++j)
			{
				z[i] += a[i][j]*x[j];				
			}
			if (abs(z[i]) > zmax)
			{
				zmax = fabs(z[i]);
			}
		}
		for (int i = 1; i <= N; ++i)
		{
			z[i] /= zmax;
		}
		
		maxerror = abs(x[1]-z[1]);
		for (int i = 2; i <= N; ++i)
		{
			if (abs(x[i]-z[i]) > maxerror)
			{
				maxerror = abs(x[i]-z[i]);
			}
		}
		cout << setw(10) << zmax << setw(10) << " to ";
		for (int i = 1; i <= N; ++i)
		{
			x[i] = z[i];
			cout << setw(10) << x[i];
		}
		cout << endl;
	}while(maxerror > e);
	for (int i = 1; i <= N; ++i)
	{
		cout << setw(15) << z[i];
	}
}