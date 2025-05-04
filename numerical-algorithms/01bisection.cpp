#include <iostream>
#include <cmath>

using namespace std;

float func(float x)
{
	return x*x-1;
}

int main()
{
	float a, b, e;
	cout << "enter the first boundary of interval" << endl;
	cin >> a;
	cout << "enter second boundary of interval" << endl;
	cin >> b;
	cout << "enter the error limit" << endl;
	cin >> e;
	
	float x;
	//to get the value of answer
	
	float count;
	count = (log(b-a)-log(e))/log(2);
	cout << "expected value of iteration was " <<  count << endl;
	
	int i = 0;	//also keeping count of the iterations
	do
	{
		++i;
		x = (a+b)/2;
		cout << x << endl;
	
		//not necessary but can add a intermediate step here; ie to check the functional values
		//take the note that functional value does not correspond to the error;
	
		if (func(x)*func(a) < 0)	//x and b they satisfy the IVT
		{
			b = x;
		}
		else
		{
			a = x;
		}
		cout << a  << " " << b << endl;
	}while(abs(a-b) > e);
	
	cout << "no of iterations was " << i << endl;
	cout << "value is " << x << endl;
}