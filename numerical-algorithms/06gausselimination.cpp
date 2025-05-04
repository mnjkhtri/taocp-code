#include <iostream>
#include <iomanip>
using namespace std;
//bound to failure when one of the diagonal element is zero

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
			if (row > col)	//do for elements on strict lower triangular matrix
			{
				int helperrow = col;		//row number of helper is same as that of column
				int helpercol = helperrow;	//since diagonal elements are the helpers
				
				float factor = a[row][col]/a[helperrow][helpercol];
				for (int colmover = 1; colmover <= N+1; ++colmover)
				{
					a[row][colmover] = a[row][colmover] - factor*a[helperrow][colmover];
				}
			}
		}
	}

	//substituion stuff
	float x[10];
	
	//last element is gotten easily
	for (int row = N; row >= 1; --row)
	{
		float sum = 0;
		for (int col = row+1; col <= N; ++col)	//sum of all the products on the right of the diagonal
		{
			//the solution row of the solution vector matches the col of the matrix
			int solrow = col;
			sum += a[row][col]*x[solrow];
		}
		x[row] = (a[row][N+1]-sum)/a[row][row];
	}
	
	for (int i = 1; i <= N; ++i)
	{
		cout << setw(20) << x[i];
	}
}