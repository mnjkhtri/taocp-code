//to represent boolean functions as data structures
//they must be ordered ie whenever a LO or HI arc goes from i to j then i < j
//must be reduced ie a branch node's LO and HI pointers must never be equal, and that no nodes are allowed to have same triple of values (V,LO,HI)
//every node is accesible from the roots 
//check below programme

//a truth talbe of function of ordern n variables is a string of length 2^n
//a bead of order n is a truth table B of order n that is not a square ie B doesnot have the form AA for any string A of length 2T(n-1)
//for order of beads n is of length 2^n there are 2^2^n strings of length 2^n out of which 2^2^(n-1) are squares
//so 2^2^(n) - 2^2^(n-1) are beads

//eg for order of 2 the beads are 0001, 0010 and so on
//these are the truth tables of functions f(x1,x2) that depen on x1 in the sense that f(0,x2) is not the same function as f(1,x2)

//every truth table is a bead or some power of a bead (called its root);
//a truth table compose of t0t1, t0 corresponds to f(0,x2,...xn), t1 to f(1,x2,...xn) each of which is a subtable, subtables have subtalbes and so on
//a truth table of order n has 2^k subtables of order n-k; 
//beads of a boolean functions are the sbutables that happen to be the beads

//the nodes of a boolean function BDD ae in one to one correspondecne with its beads
//so if(k) is a branch node corresponding to the truth table t=t0t1 then its LO and HI branches respectively correspond to roots of t0t1

//so each boolean function has one BDD, where size of its nodes is its BDD

//lets make a BDD using beads
//take the function with truth table 1100100100001111: is a bead so put it in the root as (1)
//subtalbes are 11001001 and 00001111 each will give (2) and (2)
//again 11001001 = 1100 and 1001; while 00001111 = 0000 and 1111; taking the last one we see 0 and 1 so LO goes to 0 and HI to 1
//take the first 1100 and 1001 each are beads so are (3) and (3)
//finally breaking into 11 and 00 ... 10 and 01 while the later ones are (4)s

//working good for small B(f)s

//some reasons why BDD are gods and related algorithms

#include <iostream>
#include <bitset>
using namespace std;

class Node
{
	public:
		int V;
		Node* LO;
		Node* HI;
		Node(int vv)
		{
			V = vv;
			LO = nullptr;
			HI = nullptr;
		}
}

class BoolFunction
{
	public:
		Node* ROOT;
		BoolFunction()
		{
			ROOT = nullptr;
		}
}

int main()
{
	BoolFunction median;
	median.ROOT = new Node(1);
	return 0;
}