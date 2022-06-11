//tricks and techniques notating &, |, XOR for integers
//the same laws apply except 1 is replaced by -1 because of 2s complement nature of brinin all ones on left
//GOOD PART STARTS HERE:
//check the intial part of the program
//x << k = floor(x2^K), x >> k = floor(x2^-k); x<<(-k)=x>>k; x>>(-k)=x<<k

//APPLICATIONS:
//1) packing and unpacking:
//eg: a date consisting of year, month and date can be packed as x = (((y<<4)+m)<<5)+d
//with x < x' and unpaciking as: d = x mod 32, m = (x >> 5) mod 16, y = x >> 9 where mods are x mod 2^n = x & (2^n-1)
//to check primality of odd numbers <1024 we got another technique
//...check the program....
//be careful of the endianess (espeially when loaded and stored in different sized chunks or tranfereed ffrom one machine to another)

#include <iostream>
#include <bitset>
//for conversion to binary
using namespace std;

int main()
{
	//x + x' = -1;
	unsigned long long a = 0b0111011011010011001011010010011001011001010010001011011010000001;
	unsigned long long b = ~a;
	unsigned long long r = a + b;
	cout << bitset<64>(r) << endl;
	
	//which implies -x = x'+1 = (x-1)'
	//in general (x-y)' = x'+y
	
	unsigned long long P[8], Q[8];
	//P[0] packs like this 1,3,5.... (big indian)
	//Q[0] packs like this ....5,3,1 (little indiaN)
	P[0] = 0b0111011011010011001011010010011001011001010010001011011010000001;
	P[1] = 0b0100110000110010010100100110000110110000010000010110100110000100; 
	P[2] = 0b1001001100101100001000000101101000000100100001101001000100100101; 
	P[3] = 0b0010001010001000011000011001010010001011010000010001010001010010; 
	P[4] = 0b0000110000000010010000100100110010000100100110010010110000010000; 
	P[5] = 0b1101001001100000101001000100001000100001000100100101000100101000; 
	P[6] = 0b1010000001000010000011000011011000010000001011010000001011010000; 
	P[7] = 0b0000010100010000100010100100100000010100100100010010000010100110;
	unsigned long long ps;
	ps = 0b1000000000000000000000000000000000000000000000000000000000000000;
	
	Q[0] = 0b1000000101101101000100101001101001100100101101001100101101101110;  
	Q[1] = 0b0010000110010110100000100000110110000110010010100100110000110010; 
	Q[2] = 0b1010010010001001011000010010000001011010000001000011010011001001;  
	Q[3] = 0b0100101000101000100000101101000100101001100001100001000101000100; 
	Q[4] = 0b0000100000110100100110010010000100110010010000100100000000110000; 
	Q[5] = 0b0001010010001010010010001000010001000010001001010000011001001011; 
	Q[6] = 0b0000101101000000101101000000100001101100001100000100001000000101;  
	Q[7] = 0b0110010100000100100010010010100000010010010100010000100010100000; 
	unsigned long long qs;
	qs = 0b0000000000000000000000000000000000000000000000000000000000000001;
	
	//to check if 2k+1 is prime (0 <= k < 512) we compute P[floor(k/64)] << (k&63) and check leftmost bits
	int num;
	cout << "enter an odd number";
	cin >> num;
	int check = (num-1)>>1;
	
	unsigned long long test = P[check>>6] << (check&63);
	cout << "P test is " << bitset<64>(test) << endl;
	if ((test&ps) != 0)
	{
		cout << "P says prime" << endl;
	}
	else
	{
		cout << "P says not prime" << endl;
	}
	unsigned long long testq = Q[check>>6] >> (check&63);
	cout << "Q test is " << bitset<64>(testq) << endl;
	if (testq & qs != 0)
	{
		cout << "Q says prime";
	}
	else
	{
		cout << "Q says not prime";
	}
	
	return 0;
}