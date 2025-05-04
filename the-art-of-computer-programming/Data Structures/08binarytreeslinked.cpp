#include <iostream>
#include <stack>	//push, pop, top and empty
using namespace std;

struct Node
{
	int Data;
	Node* Llink;
	Node* Rlink;
};

class BinaryTreeLinked
{
	private:
		Node* T;
	public:
		BinaryTreeLinked()
		{
			T = nullptr;
		}
		void InsertRoot(int Y)
		{
			Node* A = new Node;
			A->Data = Y;
			A->Llink = nullptr;
			A->Rlink = nullptr;
			T = A;
		}
		Node* InsertLeft(Node* P, int Y)
		{
			Node* A = new Node;
			A->Data = Y;
			A->Llink = P->Llink;
			A->Rlink = nullptr;
			P->Llink = A;
			return A;
		}
		Node* InsertRight(Node* P, int Y)
		{
			Node* A = new Node;
			A->Data = Y;
			A->Rlink = P->Rlink;
			A->Llink = nullptr;
			P->Rlink = A;
			return A;
		}
		Node* Top()
		{
			return T;
		}
		void InOrderTransversal()
		{
			stack<Node*> s;
			Node *P = T;
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
						cout << P->Data << " ";	//visit the node here
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
		
		void PreOrderTransversal()
		{
			stack<Node*> s;
			Node *P = T;
			
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
						P = P->Rlink;
					}
				}
				else
				{
					cout << P->Data << " ";	//visit the node here
					s.push(P);
					P = P->Llink;
				}
			}
		}
};
int main()
{
	BinaryTreeLinked b;
	b.InsertRoot(23);
	b.InsertLeft(b.Top(), 345);
	b.InsertRight(b.Top(), 5);
	b.InsertLeft(b.Top(), 45);
	b.InOrderTransversal();
	cout << endl;
	b.PreOrderTransversal();
}