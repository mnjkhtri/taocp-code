#include <iostream>
using namespace std;
//for theory read the 11th 

struct Node
{
		int Key;
		Node* Link;
};

class LinkedHashTable
{
	private:
		Node** TABLE;
	public:
		LinkedHashTable()
		{
			TABLE = new Node*[9];
			for (int i = 0; i < 9; ++i)
			{
				TABLE[i] = nullptr;
			}
		}
		
		int HashFunction(int Km)
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
		
		Node* SearchInsert(int Km)
		{
			int i = HashFunction(Km);
			//the list is empty
			if (TABLE[i] == nullptr)
			{
				cout << "key " << Km << " is inserted on the list of " << i << endl;
				Node* A = new Node;
				A->Key = Km;
				A->Link = nullptr;
				TABLE[i] = A;
				return A;
			}
			
			//list is not emtpy
			Node *P = TABLE[i];
			while(1)
			{
				//check if it matches with the key
				if (P->Key == Km)
				{
					cout << "key " << Km << "is found on the lsit " << i << endl;
					return P;
				}	
				
				if (P->Link == nullptr)
				{
					break;
				}
				else
				{
					P = P->Link;
				}
			}
			
			//oops not found in any of the links, now P points on to the last node of that list;

			Node* A = new Node;
			A->Key = Km;
			A->Link = nullptr;
			P->Link = A;
			cout << "key " << Km << " is inserted on the list of " << i << endl;		
			return A;
		}
		
		void show()
		{
			for (int i = 0; i < 9; ++i)
			{
				Node* P = TABLE[i];
				if (P == nullptr)
				{
					cout << "e" << endl;
					continue;
				}
				while (P != nullptr)
				{
					cout << P->Key << " ";
					P = P->Link;
				}
				cout << "e" << endl;
			}
		}
};

int main()
{
	LinkedHashTable l;
	l.SearchInsert(1);
	l.SearchInsert(8);
	l.show();
}
