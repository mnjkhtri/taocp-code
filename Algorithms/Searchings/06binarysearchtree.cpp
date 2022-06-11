#include <iostream>
#include <stack>
//good stuff ahead
using namespace std;
struct Node
{
	int Data;
	Node* Llink;
	Node* Rlink;
};

class BinarySearchTree
{
	private:
		Node* T;
	public:
		BinarySearchTree(): T(nullptr) {}
		
		Node* SearchInsert(int Km)
		{
			if (T == nullptr)
			{
				Node* A = new Node;
				A->Data = Km;
				A->Llink = nullptr;
				A->Rlink = nullptr;
				T = A;
				return A;
			}
				
			Node* P = T;
			Node* A;
			while(1)
			{
				if (P->Data == Km)
				{
					return P;
				}
				else
				{
					if (P->Data > Km)	//move left
					{
						if (P->Llink == nullptr)	//bro but there is no left
						{
							//then add the node you idiot
							A = new Node;
							P->Llink = A;
							break;
						}
						else
						{
							//ok there is the left
							P = P->Llink;
						}
					}
					else	//move right
					{
						if (P->Rlink == nullptr)	//bro but there is no right
						{
							//then add the node you idiot
							A = new Node;
							P->Rlink = A;
							break;
						}
						else
						{
							//ok there is the right
							P = P->Rlink;
						}	
					}
				}
			}
			A->Data = Km;
			A->Llink = nullptr;
			A->Rlink = nullptr;
			return A;
		}
		
		void LeftDeletion(Node* P)
		{
			//P->Llink is the one
			Node* Q = P->Llink;	
			//now q will point to actual node to delete
			//if rlink is empty that means we delete it just there
			//no need to adjust the links
			if (Q->Rlink == nullptr)
			{
				P->Llink = Q->Llink;
				cout << "is without the rlink" << endl;
			}
			//this is the optional else if
			else if (Q->Llink == nullptr)
			{
				P->Llink = Q->Rlink;
				cout << "the intermezzo step" << endl;
			}
			//means we have to find the successors
			else
			{
				cout << "rlink not empty" << endl;
				Node* R = Q->Rlink;
				//move on to the rlink
				
				//if the left link of that rlink is empty
				//we found the successor so lets adjust the links
				if (R->Llink == nullptr)	
				{
					cout << "the rlink's llink is emtpy" << endl;
					cout << "in other words the successor is" << R->Data << endl;
					//successors' left link, as it was emtpy, will get the left link of the node to delete
					//and the original variable link will point to the sucessor
					R->Llink = Q->Llink;
					//just need to adjust the llink of the sucessor, as the rlink will have to remain the same
					P->Llink = R;
				}
				else
				{
					cout << "oops cannot find the immediate successor" << endl;
					Node* S = R->Llink;
					while (S->Llink != nullptr)
					{
						R = S;
						S = R->Llink;
					}
					//now S will point to the node whose left link is emtpy, who is the sucessor of the node to delete
					//while R will point just back to the node on its journey
					cout << "finally found the sucessor" << S->Data << endl;
					S->Llink = Q->Llink;
					//successors' left link, as it was emtpy, will get the left link of the node to delete

					//here need to change the rlink as well
					R->Llink = S->Rlink;
					S->Rlink = Q->Rlink;
					
					P->Llink = S;
				}
			}
			delete Q;
		}
		
		void RightDeletion(Node* P)
		{
			Node* Q = P->Rlink;	
			if (Q->Rlink == nullptr)
			{
				P->Rlink = Q->Llink;
			}
			else if (Q->Llink == nullptr)
			{
				P->Rlink = Q->Rlink;
				cout << "the intermezzo step" << endl;
			}
			else
			{
				Node* R = Q->Rlink;
				if (R->Llink == nullptr)	
				{
					R->Llink = Q->Llink;
					P->Rlink = R;
				}
				else
				{
					Node* S = R->Llink;
					while (S->Llink != nullptr)
					{
						R = S;
						S = R->Llink;
					}
					S->Llink = Q->Llink;

					R->Llink = S->Rlink;
					S->Rlink = Q->Rlink;
					
					P->Rlink = S;
				}
			}
			delete Q;
		}
		
		void RootDeletion()
		{
			//P->llink changed to T
			Node* Q = T;	
			if (Q->Rlink == nullptr)
			{
				T = Q->Llink;
			}
			else if (Q->Llink == nullptr)
			{
				T = Q->Rlink;
				cout << "the intermezzo step" << endl;
			}
			else
			{
				Node* R = Q->Rlink;
				if (R->Llink == nullptr)	
				{
					R->Llink = Q->Llink;
					T = R;
				}
				else
				{
					Node* S = R->Llink;
					while (S->Llink != nullptr)
					{
						R = S;
						S = R->Llink;
					}
					S->Llink = Q->Llink;
					R->Llink = S->Rlink;
					S->Rlink = Q->Rlink;
					
					T = S;
				}
			}
			delete Q;
			
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
};

int main()
{
	BinarySearchTree b;
	b.SearchInsert(32);
	b.SearchInsert(2);
	b.SearchInsert(34);	
	b.SearchInsert(10);
	b.SearchInsert(4);
	b.InOrderTransversal();
	cout << endl;
	
	//delete before 32 means to delete 2
	b.LeftDeletion(b.SearchInsert(32));
	b.InOrderTransversal();
	cout << endl;
	
	//to delete root is to delete 32 lmao
	b.RootDeletion();
	b.InOrderTransversal();
	//works fine, bro, somehow execute slow but idk why
}