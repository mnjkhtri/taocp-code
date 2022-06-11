//generalization to 2's complement arithment:
//A 2-adic number is a binary number u = (...u3u2u1u0u-1u-2..u-n)_2
//7 = (...000000111)_2
//-7 = (...111111001)_2 becoz 7-7 = (....0000)_2
//1/7 = (...110110110110111)_2 becoz 1/7*7 = 1
//7/4 = (...000001.11)_2
//sqsrt(-7) = (...1000001-asomebla bla)_2 or (...0112123blabla)_2

//almost any nonzero 2adic integer can be written as x = (alpha 01^a10^b)_2, exception is when x = -2^b then a = infty
//OPERATIONS:
//x' = (A' 10^a01^b)_2
//x-1 = (A 01^a01^b)_2
//-x = (A' 10^a10^b)_2

//...
//to find the b in the representation
//delta 0 = infty, delta(2x+1) = 0, delta(2x)=delta(x)+1, delta(x-y) = delta(x xor y)
//the masks uk = -1/(2^2^k+1) gives u0 = (...101010101)_2 = -1/3; u1 = (...1100110011)_2 = -1/5; u3 = (....111100001111)_2 = -1/17;
//for 2^d bit computer: make ud,k = (2^2^d-1)/(2^2^k+1) for 0 <= k <d
//another approach is look at taocp page no 142

#include <iostream>
#include <bitset> 
using namespace std;

int main()
{
	//unsigned long long x = 1234346;
	//cout << bitset<64>(x) << endl;
	//cout << bitset<64>(x & (x-1)) << endl;	//remove the rightmost 1 into 0: (A 01^a00^b)
	//cout << bitset<64>(x & (-x)) << endl; //extract the rightmost 1 ie change all the other bits into 0: (0^inf 00^a10^b)
	//cout << bitset<64>(x | (-x)) << endl; //smear the rightmost 1 to left ie all bits on left from RM1 changes into 1 others remain unchanged
	//cout << bitset<64>(x xor (-x)) << endl; //removes and smear the rightmost 1 to left
	//cout << bitset<64>(x | (x-1)) << endl; //smear the rightmost 1 to right
	//cout << bitset<64>(x xor (x-1)) << endl; //extract and smear the rightmost 1 to right ie change others to 0
	//cout << bitset<64>(~x & (x-1)) << endl; //extract, remove and smear the rightmost 1 to right ie change others to 0
	//cout << bitset<64>(((x|(x-1)) + 1)&x) << endl; //remove the rightmost runs of 1

	const int d = 6;
	unsigned long long x= 23423423416;
	cout << endl << endl << bitset<64>(x) << endl;
	unsigned long long u[6];
	u[0] = 6148914691236517205;
	u[1] = 3689348814741910323;
	u[2] = 1085102592571150095;
	u[3] = 71777214294589695;
	u[4] = 281470681808895;
	u[5] = 4294967295;
	//initialized from wolfrom alpha
	for(int i = 0; i < d; ++i)
	{
		cout << bitset<64>(u[i]) << endl;
	}

	int r = 0;
	unsigned long long y = x & (-x);
	for (int k = 0; k < d; ++k)
	{
		if ((y & u[k]) == 0)
		{
			r = r + (1<<k);
		}
	}
	cout << "the value of rho is " << r << endl;
	//this gives rho x except for x = 0;
	return 0;
}