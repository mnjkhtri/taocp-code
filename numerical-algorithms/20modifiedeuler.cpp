#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

float f(float x, float y)
{
	return y+exp(x);
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
		
	float x;
	float y;
	for (int i = 1; i <= n; ++i)
	{
		x = x0+h;
		y = y0 + h*f(x0, y0);
		
		//we found a good value of y back in the original euler's method but we improve here as following	
		//this block takes the y as input and gives better value of y at the end.
		float ynew = y;
		float yold;
		
		cout << setw(10) << y;
		do
		{
			yold = ynew;
			//remember x0 and y0 are still the same old points
			ynew = y0 + 0.5*h*(f(x0,y0)+f(x0+h,yold));
			cout << setw(10) << ynew;
			
		}while(abs(ynew-yold) > 0.0005);
		cout << endl;
		y = ynew;
		cout << setw(5) << x << setw(15) << y << endl << endl;
		x0 = x;
		y0 = y;
	}
}