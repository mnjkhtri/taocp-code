#include <iostream>
using namespace std;
//collision is countered by linear probing in which when the key is to be searched first goes to h(K) then if not matched then
//linearly goes to h(K)-1,...,0, M-1, M-2,..., h(K)+1 

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
				--i;
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
		
		void Delete(int i)
		{
			while(1)
			{
				cout << "Key " << TABLE[i].Key << " delted from the position " << i << endl;
				TABLE[i].Key = -1;
				--N;
				int j = i;	//save the value of i;	
				
				while(1)
				{
					--i;
					if (i < 0) {i += M;}
					cout << "now checking on position " << i;
					
					if (TABLE[i].Key < 0)
					{
						cout << "empty and we are done" << endl;
						return;
					}
					int r = H1(TABLE[i].Key);
					cout << " not empty " << "with the value of " << r;
					
					//if r is cylically between i and j, we continue else we brea
					if (i < j)	//i and j are on the same side
					{
						if (r <= i)	//lies between them
						{
							cout << " and i and j on the same side" << endl;
							continue;
						}
					}
					else	//i has fallen
					{
						//on the side of i || on the side of j
						if (r >= i || r < j)
						{
							cout << " and i and j on the different side" << endl;							
							continue;
						}
					}
					break;
				}
				cout << " moved now " << endl;
				TABLE[j] = TABLE[i];
				++N;
			}
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
	cout << endl;
	p.Delete(2);
	p.show();
	cout << endl;
	p.SearchInsert(8);
	cout << endl;
	p.show();
	p.SearchInsert(1);
	cout << endl;
	p.show();
	//linear probing degrades rapidly as N approaches M;
}