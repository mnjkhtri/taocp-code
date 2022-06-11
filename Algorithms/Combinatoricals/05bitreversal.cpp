#include <iostream>
#include <bitset>
using namespace std;

int main()
{
	unsigned long long x = 1223;
	cout << bitset<64>(x) << endl;
	
	unsigned long long u[6];
	u[0] = 6148914691236517205;
	u[1] = 3689348814741910323;
	u[2] = 1085102592571150095;
	u[3] = 71777214294589695;
	u[4] = 281470681808895;
	u[5] = 4294967295;
	
	unsigned long long y, z;
	
	y = (x>>1)&u[0]; z = (x&u[0])<<1; x = y|z;		//swap bits;
	cout << bitset<64>(x) << endl;
	
	y = (x>>2)&u[1]; z = (x&u[1])<<2; x = y|z;		//swap twobitss;
	cout << bitset<64>(x) << endl;
	
	y = (x>>4)&u[2]; z = (x&u[2])<<4; x = y|z;		//swap nibbles
	cout << bitset<64>(x) << endl;
		
	y = (x>>8)&u[3]; z = (x&u[3])<<8; x = y|z;		//swap bits;
	cout << bitset<64>(x) << endl;

	y = (x>>16)&u[4]; z = (x&u[4])<<16; x = y|z;		//swap bits;
	cout << bitset<64>(x) << endl;
	
	x = (x >> 32)|(x << 32);
	cout << bitset<64>(x) << endl;	
	
	return 0;
}