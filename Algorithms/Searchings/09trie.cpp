#include <iostream>
#include <stack>
using namespace std;
//so trie is basically a what we call M-ary tree whose nodes are the Mplace vectors with components corresponding to digits or characters
//M'ary array from 0 to M-1
//each node on level 'l' represents the set of all keys that begin with a certain sequence of l characters called its prefix
//the nodes decides the M way brach depending on the (l+1)th character

struct Node
{
	int Key;
	Node* Llink;
	Node* Rlink;
};

class BinaryTrie
{
	private:
		Node* ROOT;
		int c;
	public:
		BinaryTrie(): ROOT(nullptr), c(1<<5) {}
		
		Node* SearchInsert(int Km)
		{
			if (ROOT == nullptr)
			{
				Node* A = new Node;
				A->Key = Km;
				A->Llink = nullptr;
				A->Rlink = nullptr;
				ROOT = A;
				return A;
			}
			Node* P = ROOT;
			int Ks = Km;
			
			int b;
			
			while(1)
			{
				if (P->Key == Km)
				{
					return P;
				}
				else
				{
					b = c & Ks;
					Ks = Ks << 1;
				
					if (b == 0)	//move left
					{
						if (P->Llink == nullptr)
						{
							break;
						}
						else
						{
							P = P->Llink;
						}
					}
					else	//move right
					{
						if (P->Rlink == nullptr)
						{
							break;
						}
						else
						{
							P = P->Rlink;
						}
					}
				}
			}
			//insert here
			Node* A = new Node;
			A->Key = Km;
			A->Llink = nullptr;
			A->Rlink = nullptr;
			if (b == 0)
			{
				P->Llink = A;
			}
			else
			{
				P->Rlink = A;
			}		
		}
		
		void show()
		{
			cout << ROOT->Key;
		}
		
		void InOrderTransversal()
		{
			stack<Node*> s;
			Node *P = ROOT;
			while(1)
			{
				if (P == nullptr)
				{
					if (s.empty())
					{
						break;
					}
					else
					{
						P = s.top();
						s.pop();
						cout << P->Key << " ";	//visit the node here
						P = P->Rlink;
					}
				}
				else
				{
					s.push(P);
					P = P->Llink;
				}
			}
		}
};

int main()
{
	BinaryTrie b;
	b.SearchInsert(3);
	b.SearchInsert(35);
	b.SearchInsert(2);
	//b.SearchInsert(52);
	//cout << b.SearchInsert(32)->Key;
	b.InOrderTransversal();
	
}