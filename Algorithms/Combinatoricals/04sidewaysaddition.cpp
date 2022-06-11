//the binary numbers (xn-1xn-2...x1x0)_n represents a set of positional 1s which is subset of {0,1,...n-1}
//the L and R have the obvious connection of least and greatest number here
//then another function that gives cardinatity
//G0 = 0, G(2x) = G(x), G(2x+1) = G(2x)+1 for x >= 0
//related to R by Rx = 1+G(x-1)-Gx;
//algorithm follows as:
//the foremost algorithm i could not understand see taocp 143

#include <iostream>
#include <bitset>
using namespace std;

int main()
{
	unsigned long long G = 0;	//it ought to be long long becuase it has to be shifted in the belwo
	unsigned long long u[6];
	u[0] = 6148914691236517205;
	u[1] = 3689348814741910323;
	u[2] = 1085102592571150095;
	u[3] = 71777214294589695;
	u[4] = 281470681808895;
	u[5] = 4294967295;
	unsigned long long x = 14564574252;
	unsigned long long y = x;
	unsigned long long a = 72340172838076673; //100000001000000010000000100000001000000010000000100000001;
	cout << bitset<64>(y) << endl;
	y = x - ((x>>1)&u[0]);		//now y = (u31 u30 ... u0) where u0 = y0 + y1 and so on
	cout << bitset<64>(y) << endl;
	y = (y&u[1]) + ((y>>2)&u[1]); //same here
	cout << bitset<64>(y) << endl;
	y = (y+(y>>4))&u[2];
	cout << bitset<64>(y) << endl;
	G = (a*y);
	G = G >> 56;
	cout << "the cardinality is " << G << endl << endl;
	
	//if supposed to be sparse then; bcoz as you can see in the output takes as many iterations as there are 1s
	int Gs = 0;
	y = x;
	cout << bitset<64>(x) << endl;
	while (y != 0)
	{
		Gs = Gs + 1;
		y = y & (y-1);
		cout << bitset<64>(y) << endl;

	}
	cout << Gs << endl;

	//if dense then says y<- y|(y+1) works in similar manner but i couldnot do it
}