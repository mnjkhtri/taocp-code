#include <iostream>
using namespace std;

//all these before methods they approximate to a polynomial, but when off they give quite bad
//one way we could do is to join the points simply by a linear line, but that wont be smoooth, may be quadratic? nope the key is the cubic? go more? not better

//cubic spline of points for f(x) is such that
//f(x) is a linear polynomial outside the given interal x0 to xn
//f(x) is cubic in each subinterval, so differentiable there
//f'(x) and f''(x) are continuous at each poinit

//since f(x) is cubic, f''x is linear

//for each subinterval the spine is given by

//f(x) = [(xi+1 - x)^3/6h] Mi  +  [(x - xi)^3/6h] Mi+1 
 
	//+  [(xi+1 - x)h] (yi - h^2/6 Mi)  +  [(x - xi)h] (yi+1 - h^2/6 Mi+1)


//imposing the conditions

//Mi-1 + 4Mi + Mi+1 = 6/h^2 (yi-1 - 2yi + yi+1) for i = 1 to n-1

//M0 = 0, Mn = 0

//to get a value in some point, we need to find only one spline but all Ms

int main()
{
	//too complicated for the code now bro will come to you in some points of life
}