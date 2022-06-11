#include <iostream>
#include <bitset>
using namespace std;

int main()
{
	//to add corresponding 8bits modulo
	unsigned long long x, y;
	x = 0b0111011011010011001011010010011001011001010010001011011010000001;
	y = 0b0100110000110010010100100110000110110000010000010110100110000100; 
	unsigned long long z;
	unsigned long long h = 0x8080808080808080;
	z = (x xor y) & h;
	z = z + ((x & ~h) + (y & ~h)) xor z;
	
	//to computer the bytewise averages; zj = floor(xj+yj/2)
	unsigned long long l = 9x0101010101010101;
	z = ((x xor y) & ~l) >> 1;
	z = (x & y) + z;
	return 0;
}