#include <iostream>
#include <cmath>
//approximated by secants
//faster rate of convergence than regular falsi but not guaranteed to converge
//if at any iteration f(xn) == f(xn-1) then it fails ie functional value comes out to be same for successive iterations

using namespace std;

float func(float x)
{
	return x*x*x-2*x-5;
}

int main()
{
	float x0, x1, e;
	cout << "enter the first boundary of interval" << endl;
	cin >> x0;
	cout << "enter second boundary of interval" << endl;
	cin >> x1;
	cout << "enter the functional limit" << endl;
	cin >> e;
	
	float x;
	//to get the value of answer
	
	int i = 0;	//also keeping count of the iterations
	do
	{
		++i;
		float f0 = func(x0);
		float f1 = func(x1);
		x = x1 - (x1-x0)/(f1-f0)*f1;
		//take the note that functional value does not correspond to the error;
	
		x0 = x1;
		x1 = x;
		cout << x0  << " " << x1 << endl;
	}while(abs(func(x)) > e);
	//here the error is not sure, so the functional value is measured
	
	cout << "no of iterations was " << i << endl;
	cout << "value is " << x << endl;
}