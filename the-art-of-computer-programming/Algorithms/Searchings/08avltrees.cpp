#include <iostream>
#include <stack>
using namespace std;

//there is jump from implicit binary search algorithm to optimal binary search tree (which somehow relates to the concept of binary trees themselves
//then from explicit binary trees we jump to the AVLs
//that do insertion and deletion with O(logN), so optimized of sequential and linked allocations
//AVLs are such that height of left subtree does not exceed that of its left by plus minus 1
//search paths will not be longer than 45% of the optimums

struct Node
{
	int Key;
	Node* Llink;
	Node* Rlink;
	int Bal;
	//height of right subtree - height of left subtree: -1 0 or 1
};

class AVLTree
{
	//tree starts from the right link of the HEAD node
	private:
		Node* HEAD;
	public:
		AVLTree()
		{
			HEAD = new Node;
			HEAD->Key = 0;	//lets count the height of tree with this data
			HEAD->Rlink = nullptr;
			HEAD->Llink = nullptr;	//should be used to store the height of the tree
			HEAD->Bal = 0;
		}
		
		Node* SearchInsert(int Km)
		{
			if (HEAD->Rlink == nullptr)
			{
				Node* A = new Node;
				A->Key = Km;
				A->Llink = nullptr;
				A->Rlink = nullptr;
				A->Bal = 0;
				HEAD->Rlink = A;
				++HEAD->Key;
				cout << "root inserted " << Km << endl;
				return A;
			}
			//first initialize;
			Node* T = HEAD;
			Node* S = HEAD->Rlink;
			Node* P = HEAD->Rlink;
			//P will moe down the tree
			//S will point to the place where rebalacing may be necessary
			//while T will point to the parent of S;
			Node* Q;
			//a temporary node pointer to get the data;
			while(1)
			{
				if (P->Key == Km)
				{
					return P;					
				}
				else
				{
					if (P->Key > Km)
					{
						//move left
						Q = P->Llink;	//in contrast to the BST we store in a temporary variable becuase its reffered frequently
						
						if (Q == nullptr)	//but bro there is no left
						{
							//then add the new node you dumb bitch
							Q = new Node;
							P->Llink = Q;
							break;
						}
						else	//ok ok there is a left
						{
							if (Q->Bal != 0)	//is that left's balance factor not zero? if so then rebalancing will be necessary here, note this position
							{
								T = P;	//T will point its parent
								S = Q;	//S will point the node
							}
							P = Q;
						}
					}
					else
					{
						//move right
						Q = P->Rlink;
						
						if (Q == nullptr)	//but there is no right
						{
							//so add the node
							Q = new Node;
							P->Rlink = Q;
							break;
						}
						else	//oh okay there is the right
						{
							if (Q->Bal != 0)	//is that right's balance factor not zero? if so then note this position
							{
								T = P;	//T to the parent
								S = Q;	//S to the actual node
							}
							P = Q;
						}
					}
				}
			}
			//as we break from the while loop, we insert the q node into the tree
			//and further perform the balacing if necessary
			Q->Key = Km;
			Q->Llink = nullptr;
			Q->Rlink = nullptr;
			Q->Bal = 0;
			
			//now the difference to a BST, to adjust the balance factors
			
			//1) Adjust the balance factors
			//balance factors on the nodes between S and Q needs to be changed from 0 to plus minus one as all the nodes from S to Q are zero factor nodes
			
			//S is pointing to the node that needs balacing
			int a = (S->Key > Km)? -1: 1;	//a == -1 means that Q is added to the left of the S node and vice versa
			
			//so accordingly we move the R pointer in that direction,
			
			Node* R;
			if (a == 1)
			{
				R = P = S->Rlink;
			}
			else
			{
				R = P = S->Llink;
			}
			
			//we go through the path until we meet the Q node itself while in the path we change the balance factors
			//as all the nodes on whose left is the Q node inserted gets the balance factor of -1 and vice versa
		
			while (P != Q)
			{
				//again we have the following conditions to move the P,
				
				//Q is added to the left of P
				if (P->Key > Km)
				{
					P->Bal = -1;
					P = P->Llink; 
				}
				//Q is added to the right of P
				else
				{
					P->Bal = 1;
					P = P->Rlink;
				}
			}
			
			//as the factors are adjusted now comes the critical part of the algorithm which is to do the balancing act 
			//we have several cases on that
			
			//i) if balance factor of S was initially 0 then now the tree has grown larger ie by 1
			if (S->Bal == 0)
			{
				cout << "Tree grown higher for " << Km << endl;
				S->Bal = a;
				++HEAD->Key;
				return Q;
			}
			
			if (S->Bal == -a)	//means tree has balanced (why?)
			{
				cout << "Tree grown into balanced for " << Km << endl;
				S->Bal = 0;
				return Q;
			}
			
			if (S->Bal == a)	//means tree got shit
			//now the complicated condition when tree goes out of balance
			{
				cout << "tree grown out of balance for " << Km;
				//we check the balacing factor of the node next on the path from S to Q;
				
				//if Q is on the same side of R as it was on the side of S then we do the single rotation
				if (R->Bal == a)
				{
					cout << " solved as single rotation";
					P = R;
					
					//have to change two links (excluding the top parent link) on the basis of value of a
					if (a == 1)
					{
						cout << " on the right" << endl;
						S->Rlink = R->Llink;
						R->Llink = S;
					}
					else
					{
						cout << " on the left" << endl;
						S->Llink = R->Rlink;
						R->Rlink = S;
					}
					S->Bal = 0;
					R->Bal = 0;
					
				}
				else	//double rotation
				{
					cout << " solved as double rotation";
					//have to change four links on the basis of value of a;
					if (a == 1)
					{
						cout << " on the right" << endl;
						P = R->Llink;	//P now points to the left link of R which might be the intermediate or the node added itself
						
						//like the first rotation
						S->Rlink = P->Llink;
						P->Llink = S;
						
						//followed by another rotation
						R->Llink = P->Rlink;
						P->Rlink = R;

					}
					else
					{
						cout << " on the left" << endl;
						P = R->Rlink;
						
						S->Llink = P->Rlink;
						P->Rlink = S;
						
						R->Rlink = P->Llink;
						P->Llink = R;
					}
					
				}
				
				
				//was S the Rlink of its parent(T), then change the Rlink of its parent;
				if (S == T->Rlink)
				{
					T->Rlink = P;
				}
				else
				//else of course change the llink;d
				{
					T->Llink = P;
				}
				
			}
		}
		
		void InOrderTransversal()
		{
			stack<Node*> s;
			Node *P = HEAD->Rlink;
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
						cout << P->Key << "  ";	//visit the node here
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
	AVLTree avl;
	avl.SearchInsert(2);
	avl.SearchInsert(1);
	avl.SearchInsert(34);
	//avl.SearchInsert(39);
	avl.SearchInsert(5);
	avl.SearchInsert(6);
	//inserting 4 gives single rotation, while inserting 6 gives double rotation
	avl.InOrderTransversal();
	cout << endl;
}