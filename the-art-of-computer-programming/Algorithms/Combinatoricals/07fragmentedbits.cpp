#include <iostream>
#include <bitset>
using namespace std;

//again using the representation of binary number as a set of 1s from 0 to n-1
//we know x & -x extracts the rightmost 1 which the lowest value in the subset to get its successor
//follow the algoirthm, notice carefully

//further generalizing to generate sequences of *10*1*01 annd so on
//define a and b as:

int main()
{
	/*
	unsigned long long x = 123123;
	cout << bitset<64>(x) << endl;
	
	unsigned long long y = 0;
	y = (y - x) & x;
	cout << bitset<64>(y) << endl;

	y = (y - x) & x;
	cout << bitset<64>(y) << endl;	
	
	y = (y - x) & x;
	cout << bitset<64>(y) << endl;
	
	y = (y - x) & x;
	cout << bitset<64>(y) << endl;

	y = (y - x) & x;
	cout << bitset<64>(y) << endl;
	*/
	
	unsigned long long a = 0b10010100	//* 1 in the place where * goes elsewhere 0
	unsigned long long b = 0b01001001	//0 goes in place of * and other bits remains same

	unsigned long long x = 0b01001001
	//the lexicographical successor is given by
	unsigned long long y;
	
	y = ((x-(a+b))&a)+b;
	cout << bitset<64>(x) << endl;
	cout << bitset<64>(y) << endl;
	
	return 0;
}