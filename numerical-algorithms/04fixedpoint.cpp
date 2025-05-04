#include <iostream>
#include <cmath>
using namespace std;
//the function f(x) = 0 is converted into phi(x) = x, now we take a guess then the another guess is given by
//the project on the y = x line
//smaller the value of phi derivative faster it converges

float func(float x)
{
	return x*x*x+x*x-1;
}

float phi(float x)
{
	return 1/(sqrt(x+1));
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
		x = phi(x0);
		x0 = x;
		cout << x0 << endl;
	}while(abs(func(x)) > e);
	//here the error is not sure, so the functional value is measured
	
	cout << "no of iterations was " << i << endl;
	cout << "value is " << x << endl;
}