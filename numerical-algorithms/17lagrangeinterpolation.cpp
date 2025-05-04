#include <iostream>
#include <iomanip>
#include <cmath>
//for n points, throws out a n-1 degree polynomial

//y = [(x-x1)(x-x2)...(x-xn-1)(x-xn)]/[(x0-x1)(x0-x2)...(x0-xn-1)(x0-xn)]y0 
//+ [(x-x0)(x-x2)...(x-xn-1)(x-xn)]/[(x1-x0)(x1-x2)...(x1-xn-1)(x1-xn)]y1
//...
//[(x-x0)(x-x1)(x-x2)...(x-xn-1)]/[(xn-x0)(xn-x1)(x0-x2)...(x0-xn-1)]yn

using namespace std;

int main()
{
	int N;
	float x[10], y[10];
	cout << "enter the number of data";
	cin >> N;
	int n = N-1;
	for (int i = 0; i <= n; ++i)
	{
		cin >> x[i] >> y[i];
	}
		
	float xx;
	cout << "enter the value of tind" << endl;
	cin >> xx;
	
	float totalsum = 0;
	for (int term = 0; term <= n; ++term)	//loop to calculate each term
	{
		float num = 1;
		float dem = 1;
		
		//now since each term consists of many products, this loop is to calculate the products in the numerator and denominator
		for (int prod = 0; prod <= n; ++prod)
		{
			if (prod == term)
			{
				continue;
			}
			num *= xx - x[prod];
			dem *= x[term] - x[prod]; 
		}
		cout << term << " th term " << (num/dem)*y[term] << endl; 
		totalsum += (num/dem)*y[term];
	}
	cout << endl;
	cout << "final value is " << totalsum;
}