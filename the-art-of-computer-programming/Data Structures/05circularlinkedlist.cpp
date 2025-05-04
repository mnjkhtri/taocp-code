#include <iostream>
using namespace std;

struct Node
{
    Node* Link;
    int Data;
};

//in circular list, the insert after and delete after can also be accompanied


class CircularHeadLinkedList    //insertion at beginning, deletion at left
{
    private:
        Node *HEAD;
    public:
        CircularHeadLinkedList()
        {
            HEAD = new Node;
            HEAD->Link = HEAD;
            HEAD->Data = -1;
        }

        void LeftInsertion(int Y)
        {
            Node* A = new(nothrow) Node;
            if (A == nullptr)
            {
                cout << "overflow";
                exit(1);
            }

            A->Data = Y;
            A->Link = HEAD->Link;
            HEAD->Link = A;
        }

        int LeftDeletion()
        {
            if (HEAD->Link == HEAD)
            { 
                cout << "underflow";
                exit(1);
            }
            Node* A = HEAD->Link;
            int val = A->Data;
            HEAD->Link = A->Link;
            delete A;
            return val;
        }

        void InsertAfter(Node* P, int Y)
        {
            Node* A = new(nothrow) Node;
            if (A == nullptr) 
            {
                cout << "overflow" << endl;
                exit(1);
            }
            A->Data = Y;
            A->Link = P->Link;
            P->Link = A;
        }
        int DeleteAfter(Node* P)
        {
            if (P->Link == HEAD)
            {
                cout << "cant delete head bratha" << endl;
                return -1;
            }
            Node* A = P->Link;
            P->Link = A->Link;
            int val = A->Data;
            delete A;
            return val;
        }
};

class CircularLinkedList    //insertion at beginning, insertion at end (leave this in case of list head), deletion at left
{
    private:
        Node* PTR;
    public:
        CircularLinkedList(): PTR(nullptr) {}

        void LeftInsertion(int Y)
        {
            Node* A = new(nothrow) Node;
            if (A == nullptr)
            {
                cout << "overflow";
                exit(1);
            }

            A->Data = Y;
            
            if (PTR == nullptr)
            {
                A->Link = A;
                PTR = A;
            }
            else
            {
                A->Link = PTR->Link;
                PTR->Link = A;
            }
        }

        void RightInsertion(int Y)
        {
            Node* A = new(nothrow) Node;
            if (A == nullptr)
            {
                cout << "overflow";
                exit(1);
            }

            A->Data = Y;
            
            if (PTR == nullptr)
            {
                PTR = A;
                A->Link = A;
            }
            else
            {
                PTR->Link = A;
                A->Link = PTR->Link;
            }
            PTR = A;
        }

        int LeftDeletion()
        {
            if (PTR == nullptr)
            {
                cout << "underflow";
                exit(1);
            }

            Node* A;
            A = PTR->Link;
            int val = A->Data;
            PTR->Link = A->Link;
            delete A;
            if (PTR == A)
            {
                PTR = nullptr;
            }
            return val;
        }

        void InsertAfter(Node* P, int Y)
        {
            Node* A = new(nothrow) Node;
            if (A == nullptr) 
            {
                cout << "overflow" << endl;
                exit(1);
            }
            A->Data = Y;
            A->Link = P->Link;
            P->Link = A;
        }
        int DeleteAfter(Node* P)
        {
           if (P->Link == HEAD)
            {
                cout << "list ends here" << endl;
                return -1;
            }
            else
            {
                Node* A = P->Link;
                P->Link = A->Link;
                int val = A->Data;
                delete A;
                return val;
            }
        }
};

int main()
{


}