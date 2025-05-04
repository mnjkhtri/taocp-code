#include <iostream>
#include <iomanip>
using namespace std;
//in the do little's method U is upper triangular, L is lower triangular (with diagonal element 1)


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
	 
	//generating the L and U matrices
	float L[10][10], U[10][10];
	
	for (int col = 1; col <= N; ++col)
	{
		for (int row = 1; row <= N; ++row)
		{
			if (row <= col)	//upper triangular including the diagonal
			{
				U[row][col] = a[row][col];
				
				for (int k = 1; k <= row-1; ++k)
				{
					U[row][col] -= L[row][k]*U[k][col];
				}
				
				if (row == col)
				{
					L[row][col] = 1;
				}
				else
				{
					L[row][col] = 0;
				}
			}
			else	//strict lower triangular matrix
			{
				L[row][col] = a[row][col];
				
				for (int k = 1; k <= col-1; ++k)
				{
					L[row][col] -= L[row][k]*U[k][col]; 
				}
				L[row][col] /= U[col][col];
				U[row][col] = 0;
			}
		}
	}
	
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			cout << setw(20) << L[i][j];
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			cout << setw(20) << U[i][j];
		}
		cout << endl;
	}
	
	//now the substitution part comes
	float Y[10], X[10];
	for (int row = 1; row <= N; ++row)
	{
		float sum = 0;
		for (int col = 1; col < row; ++col)
		{
			int solrow = col;
			sum += L[row][col]*Y[solrow];
		}
		Y[row] = (a[row][N+1]-sum)/1;
	}
	for (int row = N; row >= 1; --row)
	{
		float sum = 0;
		for (int col = row+1; col <= N; ++col)
		{
			int solrow = col;
			sum += U[row][col]*X[solrow];
		}
		X[row] = (Y[row]-sum)/U[row][row];
	}
	cout << endl;
	for (int i = 1; i <= N; ++i)
	{
		cout << setw(20) << Y[i];
	}
	cout << endl;
	for (int i = 1; i <= N; ++i)
	{
		cout << setw(20) << X[i];
	}
}