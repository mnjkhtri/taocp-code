#include <iostream>
using namespace std;
//better when tables starts to get full
//possibilies of H2(k) are as follows:
//1) if H1 is division hash, then h2 = 1+ K mod M-1 or h2 = 1+ K mod M-2

struct Node
{
	int Key;
};

class ProbedHashTables
{
	private:
		int M;
		Node* TABLE;
		int N;	//to store the total number of nodes in the table
		
	public:
		ProbedHashTables()
		{
			M = 9;
			N = 0;
			TABLE = new Node[M];
			
			for (int i = 0; i < M; ++i)
			{
				TABLE[i].Key = -1;
			}
		}
		
		int H1(int Km)
		{
			if (Km == 1) {return 2;}
			if (Km == 2) {return 0;}
			if (Km == 3) {return 3;}
			if (Km == 4) {return 0;}
			if (Km == 5) {return 4;}
			if (Km == 6) {return 0;}
			if (Km == 7) {return 1;}
			if (Km == 9) {return 5;}
			if (Km == 8) {return 2;}
			if (Km == 10) {return 1;}
		}
		
		int H2(int Km)
		{
			//the second hash function gives the increment for c depending on the value of Km, it must give value from 1 to M-1 which are co prime to M
			//so if M is prime then any value can be given
			//if M = 2^m then any odd value can be given
			if (Km == 1) {return 2;}	//co prime to 9 bebs
			if (Km == 2) {return 4;}
			if (Km == 3) {return 5;}
			if (Km == 4) {return 2;}
			if (Km == 5) {return 5;}
			if (Km == 6) {return 2;}
			if (Km == 7) {return 1;}
			if (Km == 9) {return 8;}
			if (Km == 8) {return 4;}
			if (Km == 10) {return 8;}
			
		}
		
		int SearchInsert(int Km)
		{
			int i = H1(Km);
			
			while(1)
			{
				if (TABLE[i].Key < 0)
				{
					break;
				}
				if (TABLE[i].Key == Km)
				{
					cout << "key " << Km << "is found at the position " << i << endl;
					return i;
				}	
				int c = H2(Km);
				i -= c;
				if (i < 0)
				{
					i += M;
				}
			}				
			//now i points to the location where we can insert
			if (N == M-1)
			//having a emtpy node makes it faster because we donot need to keep track of how many times the inner loop's been executed
			//the catch being that the linear probing circulates
			{
				cout << "overflow" << endl;
				exit(1);
			}
			++N;
			TABLE[i].Key = Km;
		}
		void show()
		{
			for (int i = 0; i < M; ++i)
			{
				cout << TABLE[i].Key << endl;
			}
		}
};


int main()
{
	ProbedHashTables p;
	p.SearchInsert(2);
	p.SearchInsert(1);
	p.SearchInsert(6);
	p.SearchInsert(3);
	p.SearchInsert(4);
	p.SearchInsert(5);
	p.SearchInsert(8);
	p.SearchInsert(9);
	p.show();
	//linear probing degrades rapidly as N approaches M;
}