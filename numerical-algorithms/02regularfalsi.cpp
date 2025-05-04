#include <iostream>
#include <cmath>
//approximated by chords
//guaranteed to converge

using namespace std;

float func(float x)
{
	return x*log10(x)-1.2;
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
		x = x0 - (x1-x0)/(f1-f0)*f0;
		//take the note that functional value does not correspond to the error;
	
		if (func(x)*func(x0) < 0)	//x and x0 they satisfy the IVT
		{
			x1 = x;	
		}
		else
		{
			x0 = x;
		}
		cout << x0  << " " << x1 << endl;
	}while(abs(func(x)) > e);
	//here the error is not sure, so the functional value is measured
	
	cout << "no of iterations was " << i << endl;
	cout << "value is " << x << endl;
}