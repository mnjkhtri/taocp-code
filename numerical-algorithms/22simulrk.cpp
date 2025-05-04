#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//solves the simultaneous dy/dx = f(x,y,z) and dz/dx = g(x,y,z)

float f(float x, float y, float z)
{
	return 1+x*z;
}

float g(float x, float y, float z)
{
	return -x*y;
}

int main()
{
	float x0, y0, z0;
	cout << "give the initial conditions" << endl;
	cin >> x0 >> y0 >> z0;
	
	float h;
	float xx;
	cout << "give me the x to find the function at" << endl;
	cin >> xx;
	
	cout << "give me the size of the subinterval" << endl;
	cin >> h;
	
	int n = (xx-x0)/h;
		
	float x;
	float y;
	float z;
	
	float k1, k2, k3, k4;
	float l1, l2, l3, l4;
	for (int i = 1; i <= n; ++i)
	{
		k1 = h*f(x0,y0,z0);
		l1 = h*g(x0,y0,z0);
		
		k2 = h*f(x0+h/2, y0+k1/2, z0+l1/2);
		l2 = h*g(x0+h/2, y0+k1/2, z0+l1/2);
		
		k3 = h*f(x0+h/2, y0+k2/2, z0+l2/2);
		l3 = h*g(x0+h/2, y0+k2/2, z0+l2/2);
		
		k4 = h*f(x0+h, y0+k3, z0+l3);
		l4 = h*g(x0+h, y0+k3, z0+l3);
		
		cout << setw(15) << k1 << setw(15) << l1 << endl;
		cout << setw(15) << k2 << setw(15) << l2 << endl;
		cout << setw(15) << k3 << setw(15) << l3 << endl;
		cout << setw(15) << k4 << setw(15) << l4 << endl;
		
		x = x0 + h;
		y = y0 + (k1+2*k2+2*k3+k4)/6;
		z = z0 + (l1+2*l2+2*l3+l4)/6;
		
		cout << setw(10) << x << setw(10) << y << setw(10) << z << endl << endl;
		
		x0 = x;
		y0 = y;
		z0 = z;
	}
}