#include <iostream>
#include <bitset>
using namespace std;

//to exchange xi and xj (i>j)

int main()
{
	int i = 2;
	int j = 0;
	//int d = i-j;
	unsigned long long x = 123123;
	cout << bitset<64>(x) << endl;
	
	/*
	unsigned long long y, z, m;
	y = (x>>d)&(1<<j);
	z = (x&(1<<j))<<d;
	m = (1<<i)|(1<<j);
	x = (x&(~m))|y|z;
	//two shifts and five bitwise booleans
	cout << bitset<64>(x) << endl;
	//just like the reversal but extra mask is needed 
	*/
	//assignment to y and z can be done simultaneously

	/*
	unsigned long long y;
	y = (x xor (x >> d)) & (1 << j);
	x = x xor y xor (y << d);	
	cout << bitset<64>(x) << endl;
	//the first assingment puts (xi XOR xj) into xj
	//second changes xi to xi XOR (xi XOR xj) and xj to xj XOR (xi XOR xj)
	//remember the old formulas
	//easy to fromulate convert x to g(x) in convert x to x XOR g(x)
	*/
	
	/*
	//can be used to swap several non overlapping bits as well using mask 2^theta which is moree genral than 2^j
	//puts d = 39 and c = 2^25-1 to swap leftmost and rightmost 25 bits; as c has 1s in the right pair to be swapped; d is distanve between left of each pair
	unsigned long long y;
	int d = 30;
	unsigned long long c = (1<<12)-1;
	cout << bitset<64>(c) << endl;
	y = (x xor (x >> d)) & c;
	x = x xor y xor (y << d);	
	cout << bitset<64>(x) << endl;
	*/
	
	//to reverse whole bits
	
	unsigned long long u = 6148914691236517205;
	unsigned long long y, z;
	y = (x>>1)&u; z = (x&u)<<1; x = y|z;
	cout << bitset<64>(x) << endl;
	
	y = (x xor (x>>4))& 0x0300c0303030c303; x = x xor y xor (y << 4);
	cout << bitset<64>(x) << endl;
		
	y = (x xor (x>>8))& 0x00c0300c03f0003f; x = x xor y xor (y << 8);
	cout << bitset<64>(x) << endl;

	y = (x xor (x>>20))& 0x00000ffc00003fff; x = x xor y xor (y << 20);
	cout << bitset<64>(x) << endl;
	
	x = (x >> 34)|(x << 30);
	cout << bitset<64>(x) << endl;	
	
	
	return 0;
}