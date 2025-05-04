#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

float f(float x, float y)
{
	return (y+x);
}


//we try to approximate the curve by the tangent lines but unless the h is very small, the error is pretty significant
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
	
	cout << "the number of iteration witll be " << n << endl << endl;
		
	float x;
	float y;
	for (int i = 1; i <= n; ++i)
	{
		x = x0+h;
		y = y0 + h*f(x0, y0);
		
		cout << setw(5) << x << setw(15) << y << endl;
		x0 = x;
		y0 = y;
	}
}