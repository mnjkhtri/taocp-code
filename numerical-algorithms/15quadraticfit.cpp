#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	int n;
	cout << "enter number of data point" << endl;
	cin >> n;
	
	float x[10], y[10];
	cout << "enter the data pairs" << endl;
	for (int i = 1; i <= n; ++i)
	{
		cin >> x[i];
		cin >> y[i];
	}
	
	//the fit line is y = a+bx+cx^2;
	//the normal equations are:
	//Ey = 		an 		+ 	bEx 	+	cEx^2
	//Exy = 	aEx 	+	bEx^2 	+ 	cEx^3
	//Ex^2y = 	aEx^2 	+	bEx^3	+	cEx^4
	
	float sumy = 0;
	float sumx = 0;
	float sumxx = 0;
	float sumxy = 0;
	float sumxxx = 0;
	float sumxxy = 0;
	float sumxxxx = 0;
	
	
	for (int i = 1; i <= n; ++i)
	{
		sumy += y[i];
		sumx += x[i];
		sumxx += x[i]*x[i];
		sumxy += x[i]*y[i];
		sumxxx += x[i]*x[i]*x[i];
		sumxxy += x[i]*x[i]*y[i];
		sumxxxx += x[i]*x[i]*x[i]*x[i];
	}
	//now all the values are ready we need to the solve the equations
	//maybe cramers rule will help
	
	float d = n*(sumxx*sumxxxx-sumxxx*sumxxx)-sumx*(sumx*sumxxxx-sumxx*sumxxx)+sumxx*(sumx*sumxxx-sumxx*sumxx);
	float da = sumy*(sumxx*sumxxxx-sumxxx*sumxxx)-sumx*(sumxy*sumxxxx-sumxxy*sumxxx)+sumxx*(sumxy*sumxxx-sumxxy*sumxx);
	float db = n*(sumxy*sumxxxx-sumxxy*sumxxx)-sumy*(sumx*sumxxxx-sumxx*sumxxx)+sumxx*(sumx*sumxxy-sumxx*sumxy);
	float dc = n*(sumxx*sumxxy-sumxxx*sumxy)-sumx*(sumx*sumxxy-sumxx*sumxy)+sumy*(sumx*sumxxx-sumxx*sumxx);
	float a = da/d;
	float b = db/d;
	float c = dc/d;
	
	
	cout << "the equation is " << setw(5)  << a << setw(5) << " + " << setw(5) << b << " x" << setw(5) << c << " x^2" << endl;
}