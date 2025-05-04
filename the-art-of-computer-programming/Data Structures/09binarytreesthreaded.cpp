#include <iostream>
using namespace std;

struct Node
{
	int Data;
	Node* Llink;
	Node* Rlink;
	bool Lthread;
	bool Rthread;
};

class BinaryTreeThreaded
{
	private:
		Node* HEAD;
	public:
		BinaryTreeThreaded()
		{
			HEAD = new Node;
			HEAD->Data = -1;
			HEAD->Llink = HEAD;
			HEAD->Lthread = true;
			HEAD->Rlink = HEAD;
			HEAD->Rthread = false;
		}
		Node* InOrderSuccessor(Node* P)
		{
			Node* Q = P->Rlink;
			if (P->Rthread == true)
			{
				return Q;
			}
			while (Q->Lthread == false)
			{
				Q = Q->Llink;
			}
			return Q;
		}
		Node* InOrderPredecessor(Node* P)
		{
			Node* Q = P->Llink;
			if (P->Lthread == true)
			{
				return Q;
			}
			while (Q->Rthread == false)
			{
				Q = Q->Rlink;
			}
			return Q;
		}
		
		Node* PreOrderSuccessor(Node* P)
		{
			if (P->Lthread == false)
			{
				Node* Q = P->Llink;
				return Q;
			}
			Node* Q = P;
			while (Q->Rthread == true)
			{
				Q = Q->Rlink;
			}
			Q = Q->Rlink;
			return Q;
		}
		Node* InsertLeft(Node* P, int Y)
		{
			Node* A = new Node;
			A->Data = Y;
			A->Llink = P->Llink;	A->Lthread = P->Lthread;
			A->Rlink = P;	A->Rthread = true;
			P->Llink = A;	P->Lthread = false;
			
			if (A->Lthread == false)
			{
				Node* As = InOrderPredecessor(A);
				As->Rlink = A;
			}
			
			return A;
		}
		Node* InsertRight(Node* P, int Y)
		{
			Node* A = new Node;
			A->Data = Y;
			A->Rlink = P->Rlink;	A->Rthread = P->Rthread;
			A->Llink = P;	A->Lthread = true;
			P->Rlink = A;	P->Rthread = false;
			
			if (A->Rthread == false)
			{
				Node* As = InOrderSuccessor(A);
				As->Llink = A;
			}
			return A;
		}
		Node* Top()
		{
			return HEAD;
		}
		
		void InOrderTransversal()
		{
			Node *P = InOrderSuccessor(HEAD);
			while (P != HEAD)
			{
				cout << P->Data << " ";
				P = InOrderSuccessor(P);
			}
		}
		void PreOrderTransversal()
		{
			Node *P = PreOrderSuccessor(HEAD);
			while (P != HEAD)
			{
				cout << P->Data << " ";
				P = PreOrderSuccessor(P);
			}
		}
};
int main()
{
	BinaryTreeThreaded b;
	Node* tempa = b.InsertLeft(b.Top(), 'A');
	Node* tempb = b.InsertLeft(tempa, 'B');
	Node* tempc = b.InsertRight(tempa, 'C');
	Node* tempd = b.InsertLeft(tempb, 'D');
	Node* tempe = b.InsertLeft(tempc, 'E');
	Node* tempf = b.InsertRight(tempc, 'F');
	Node* tempg = b.InsertRight(tempe, 'G');
	Node* temph = b.InsertLeft(tempf, 'H');
	Node* tempj = b.InsertRight(tempf, 'J');
			
	b.InOrderTransversal();
	cout << endl;
	b.PreOrderTransversal();
}