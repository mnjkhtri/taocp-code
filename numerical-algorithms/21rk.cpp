#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

float f(float x, float y)
{
	return (y*y-x*x)/(y*y+x*x);
}

int main()
{
	float x0, y0;
	cout << "give the initial conditions" << endl;
	cin >> x0 >> y0;
	
	float h;
	float xx;
	cout << "give me the x to find the function at" << endl;
	cin >> xx;
	
	cout << "give me the size of the subinterval" << endl;
	cin >> h;
	
	int n = (xx-x0)/h;
		
	float x;
	float y;
	
	float k1, k2, k3, k4;
	for (int i = 1; i <= n; ++i)
	{
		k1 = h*f(x0,y0);
		k2 = h*f(x0+h/2, y0+k1/2);
		k3 = h*f(x0+h/2, y0+k2/2);
		k4 = h*f(x0+h, y0+k3);
		
		x = x0 + h;
		y = y0 + (k1+2*k2+2*k3+k4)/6;
		
		cout << setw(10) << x << setw(10) << y << endl;
		
		x0 = x;
		y0 = y;
	}
}