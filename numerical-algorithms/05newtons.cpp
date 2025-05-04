#include <iostream>
#include <cmath>
using namespace std;
//converges on the interval where _given in overleft_, convergence is quadratic
//so choose a nearby point where that condition matches

float func(float x)
{
	return x*x*x-3*x+2;
}

float funcdash(float x)
{
	return 2*x-3;
}

int main()
{
	float x0, e;
	cout << "enter the first guess" << endl;
	cin >> x0;
	cout << "enter the functional limit" << endl;
	cin >> e;
	
	float x;
	//to get the value of answer
	
	int i = 0;	//also keeping count of the iterations
	do
	{
		++i;
		x = 1-func(x0)/funcdash(x0);
		x0 = x;
		cout << x0 << endl;
	}while(abs(func(x)) > e);
	//here the error is not sure, so the functional value is measured
	
	cout << "no of iterations was " << i << endl;
	cout << "value is " << x << endl;
}

//nice result:
//iteration for root N = 0.5*(x+N/x)