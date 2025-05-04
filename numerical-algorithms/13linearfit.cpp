#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	int n;
	cout << "enter number of data point" << endl;
	cin >> n;
	
	float x[10], y[10];
	cout << "enter the data pairs" << endl;
	for (int i = 1; i <= n; ++i)
	{
		cin >> x[i];
		cin >> y[i];
	}
	
	float sumy = 0;
	float sumx = 0;
	float sumxy = 0;
	float sumxx = 0;
	
	
	//the linear line is y = a + bx;
	//normal equations are obtained as:
	
	//Ey = na + bEx
	//Exy = aEx + bEx^2
	for (int i = 1; i <= n; ++i)
	{
		sumx += x[i];
		sumy += y[i];
		sumxy += x[i]*y[i];
		sumxx += x[i]*x[i];
	}
	//now all the values are ready we need to the solve the equations
	//maybe cramers rule will help
	
	float d = n*sumxx - sumx*sumx;
	float da = sumy*sumxx - sumx*sumxy;
	float db = n*sumxy - sumx*sumy;
	
	float a = da/d;
	float b = db/d;
	
	cout << "the equation is " << setw(5)  << a << setw(5) << " + " << setw(5) << b << " x";
}