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
		for (int j = 1; j <= N+1; ++j)
		{
			cin >> a[i][j];
		}
	}
	 
	//elimination stuff
	for (int col = 1; col <= N; ++col)
	{
		for (int row = 1; row <= N; ++row)
		{
			if (row != col)	//do for elements everywhere else on the diagonal
			{
				int helperrow = col;		//row number of helper is same as that of column
				
				float factor = a[row][col]/a[helperrow][helperrow];
				for (int colmover = 1; colmover <= N+1; ++colmover)
				{
					a[row][colmover] = a[row][colmover] - factor*a[helperrow][colmover];
				}
			}
		}
	}

	//substituion stuff
	float x[10];
	
	//simple calculation
	//the interesting thing is the same substitution stuff we did with gauss elimination applies here as well
	for (int row = N; row >= 1; --row)
	{
		x[row] = a[row][N+1]/a[row][row];
	}
	
	for (int i = 1; i <= N; ++i)
	{
		cout << setw(20) << x[i];
	}
}