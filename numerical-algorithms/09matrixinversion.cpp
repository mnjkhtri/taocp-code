#include <iostream>
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
		for (int j = 1; j <= N; ++j)
		{
			cin >> a[i][j];
		}
	}
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N+1; ++j)
		{
			if (i == j)
			{
				a[i][j+N] = 1;
			}
			else
			{
				a[i][j+N] = 0;
			}
		}
	}
	 
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= 2*N; ++j)
		{
			cout << setw(12) << a[i][j];
		}
		cout << endl;
	}
	
	for (int col = 1; col <= N; ++col)
	{
		for (int row = 1; row <= N; ++row)
		{
			if (row != col)	//do for elements everywhere else on the diagonal
			{
				int helperrow = col;		//row number of helper is same as that of column
				
				float factor = a[row][col]/a[helperrow][helperrow];
				for (int colmover = 1; colmover <= N+N; ++colmover)
				{
					a[row][colmover] = a[row][colmover] - factor*a[helperrow][colmover];
				}
			}
		}
	}
	cout << endl;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			a[i][j+N] /= a[i][i];
		}
		a[i][i] = 1;
	}
	
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= 2*N; ++j)
		{
			cout << setw(12) << a[i][j];
		}
		cout << endl;
	}


}