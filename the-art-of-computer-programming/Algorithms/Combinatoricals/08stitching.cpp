#include <bitset>
#include <iostream>
using namespace std;

//z = zn-1...z0 is formed by stitching xr-1...x0 and ys-1...y0; r+s = n
//with mask X for which GX = s; ie wherever X is 1, y's bits will take the place
//if X = 10010100 then z = y2 x4 x3 y1 x2 y0 x1 x0 

//now we want to perfrom some operatiosn in the y's bits without changing x's bits

int main()
{
	unsigned long long z;	//where y bits are stitched
	unsigned long long z';	//where y'
	unsigned long long X;
	
	unsigned long long r = ((z & X) + (z' | X)) & X;
	return 0;
}