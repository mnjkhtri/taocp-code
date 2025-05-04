//to search a sequence of bytes in a long bits 
//eg to search for 0s that marks the end of a string

#include <iostream>
#include <bitset>
using namespace std;

int main()
{
	unsigned long long l = 0x0101010101010101;
	unsigned long long h = 0x8080808080808080;
	
	/*
	//unsigned long long x = 12312342344232312000;
	unsigned long long x = 0b0111011011010000000000000010011001011001010010001011011010000001;

	cout << bitset<64>(x) << endl;
	unsigned long long t = h&(x-l)&(~x);
	cout << bitset<64>(t) << endl;
	*/
	
	//if all xjs non zero then t will be zero 
	//but if xj zero and all other on its right be non zero then t will have rho t = 8j+7 ..... knuth says now rho and lambda can be calculated faster see pageno 153 ko last tira ko paragraph
	//hence pinpoints rightmost zero byte of the 64bit number
	
	//as i have notied whereve byte is non zero gives zero wherever is zero gives 1000000
	
	/*
	//this seems to produce the same thing though but knuth says this one precise
	unsigned long long u = h&(~(x|((x|h)-l)));
	cout << bitset<64>(u) << endl;
	*/
	
	//also he leftmost zero byte of x is now xj, Lt = 8j+7
	
	//to check the 0x0a byte in teh string we check for zero in x XOR 0x0a0a0a0a0a0a0a0a
	
	//further taking it
	//to compute z7...z0_256 from x and y where zj = xj when xj=yj else zj = * ie if x = beaching and y = belching then z = be*ching
	
	
	/*
	//unchecked
	unsigned long long t = h & ((x xor y)|(((x xor y)}h)-l));
	unsigned long long m = (t<<1)-(t>>7);
	unsigned long long z = x xor ((x xor "********")&m);
	*/
	
	//the above test checked bytes that are zero, but in real they check whether they are less than 01
	//if we replace l by c.l = (cccccccc)_256 then we can check whether thhe bytes are less the c
	
	//the following sets tj = 128(as before) for [xj < yj] for each byte j 
	
	/*
	//ofcourse unchecked
	unsigned long long t = h & (~<x~yz); z = (x|h)-(y&h');
	*/
	
	
	//now some broadbits stuffs was there but didnot care
	//application to directed graphs (reachability), to data representation, to data strucuters
	
	return 0;
}