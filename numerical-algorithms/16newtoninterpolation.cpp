#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
	int N;
	float x[10], y[10];
	cout << "enter the number of data";
	cin >> N;
	int n = N-1;
	for (int i = 0; i <= n; ++i)
	{
		cin >> x[i] >> y[i];
	}
	
	//we know the formula for forward interpolation ie
	
	// y = y0 + p Dy0 + p(p-1)/2! D^2y0 + ... + p(p-1)...(p-n+1)/n! D^ny0;
	// where p = (x-x0)/h and the differences are obtained from the difference table
	
	float h = x[1] - x[0];
	float xx;
	cout << "give me the value of x to find" << endl;
	cin >> xx;
	
	float p = (xx-x[0])/h;
	cout << "the value of p is " << p << endl << endl;
	
	//need a difference 2D matrix of size: numofdata * numofdata
	  
	float diff[10][10];
	
	//row chai zero bata suru hunxa while column chai 1 bata hunx

	//row goes from 0 to n
	//column goes from 1 to n
	for (int i = 0; i <= n-1; ++i)
	{
		diff[i][1] = y[i+1]-y[i];
	}
	
	//for other columns we the difference table itself
	//we need values in the rows: 0 to 
	
	
	for (int col = 2; col <= n; ++col)
	{
		for (int row = 0; row <= n-col; ++row)
		{
			diff[row][col] = diff[row+1][col-1] - diff[row][col-1];
		}
	}
	
	//lets show the table to the people
	
	for (int row = 0; row <= n; ++row)
	{
		cout << setw(10) << x[row] << setw(10) << y[row];
		for (int col = 1; col <= n-row; ++col)
		{
			if (abs(diff[row][col]) < 0.0001)
			{
				cout << setw(10) << "0";				
			}
			else
			{
				cout << setw(10) << diff[row][col];
			}
		}			
		cout << endl;
	}
	//now that the table is ready
	// y = y0 + p Dy0 + p(p-1)/2! D^2y0 + ... + p(p-1)...(p-n+1)/n! D^ny0;
	
	float yp = y[0];
	float pfactor = 1;
	float factorialterm = 1;
	for (int i = 1; i <= n; ++i)
	{
		cout << yp;
		float diffactor = diff[0][i];
		pfactor *= p-i+1;
		factorialterm *= i;
		cout << " now adding the term " << (pfactor*diffactor)/factorialterm << endl;
		yp += (pfactor*diffactor)/factorialterm;
	}
	cout << endl << "the value is " << yp;
}

//additional info for other interpolations

//1) the stirling interpolatino used for central: with p - -1/4 to 1/4

//y = (...) + p(...) + p^2(...) + p(p^2-1)(...) + p^2(p^2-1)(...) + p(p^2-1)(p^2-2)(...) + p^2(p^2-1)(p^2-4)(...)

//meanwhile for the besssels polation
//y = (...) + p(...) + p(p-1)(...) + (p-1/2)p(p-1)(...) + (p+1)p(p-1)(p-2)(...) + p(p^2-1)(p^2-2)(...) + p^2(p^2-1)(p^2-4)(...)

//the bracket represents the terms
//in the first column of y we take y0
//then in respective column if there are two we take the average, else standalo0ne

//for unequal spacing check next