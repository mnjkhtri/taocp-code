#include <iostream>
using namespace std;

struct Node
{
    Node* Llink;
    Node* Rlink;
    int Data;
};

class DoublyLinkedList
{
    private:
        Node* LEFT;
        Node* RIGHT;
    public:
        DoublyLinkedList(): LEFT(nullptr), RIGHT(nullptr) {}
        void InsertAtBeginning(int Y);
        int DeleteAtBeginning();
        void InsertAtEnd(int Y);
        int DeleteAtEnd();

        void InsertBefore(Node* P, int Y);
        void InsertAfter(Node* P, int Y);
        int DeleteP(Node* P);
};

int main()
{
    DoublyLinkedList D;
    D.InsertAtEnd(90);
   cout << D.DeleteAtEnd() << "this one " << endl;
   D.InsertAtBeginning(690);
}


int DoublyLinkedList::DeleteP(Node* P)
{   
    if (P == LEFT)
    {
        return DeleteAtBeginning();
    }
    if (P == RIGHT)
    {
        return DeleteAtEnd();
    }
    Node* A = P;
    A->Llink->Rlink = A->Rlink;
    A->Rlink->Llink = A->Llink; 
    int val = A->Data;
    delete A;
    return val;
}   


void DoublyLinkedList::InsertBefore(Node* P, int Y)
{
    if (LEFT == P)
    {
        InsertAtBeginning(Y);
    }
    else
    {
        Node* A = new(nothrow) Node;

        if (A == nullptr)
        {
            cout << "overflow" << endl;
            exit(1);
        } 
        A->Data = Y;

        A->Rlink = P;
        P->Llink = A;

        A->Llink = P->Llink;
        P->Llink->Rlink = A;
    }
}



void DoublyLinkedList::InsertAfter(Node* P, int Y)
{
    if (RIGHT == P)
    {
        InsertAtEnd(Y);
    }
    else
    {
        Node* A = new(nothrow) Node;

        if (A == nullptr)
        {
            cout << "overflow" << endl;
            exit(1);
        } 
        A->Data = Y;

        A->Llink = P;
        P->Rlink = A;

        A->Rlink = P->Rlink;
        P->Rlink->Llink = A;
    }
}

void DoublyLinkedList::InsertAtBeginning(int Y)
{
    Node* A = new(nothrow) Node;
    
    if (A == nullptr)
    {
        cout << "overflow";
        exit(1);
    }

    A->Data = Y;
    A->Llink = nullptr;

    //means list if empty
    if (LEFT == nullptr)
    {
        A->Rlink = nullptr;
        RIGHT = A;
    }
    else
    {
        A->Rlink = LEFT;
        LEFT->Llink = A;
    }
    LEFT = A;
}

void DoublyLinkedList::InsertAtEnd(int Y)
{
    Node* A = new(nothrow) Node;
    
    if (A == nullptr)
    {
        cout << "overflow";
        exit(1);
    }

    A->Data = Y;
    A->Rlink = nullptr;

    if (RIGHT == nullptr)
    {
        A->Llink = nullptr;
        LEFT = A;
    }
    else
    {
        A->Llink = RIGHT;
        RIGHT->Rlink = A;
    }
    RIGHT = A;
}

int DoublyLinkedList::DeleteAtBeginning()
{
    if (LEFT == nullptr)
    {
        cout << "underflow";
        exit(1);
    }

    Node* A = LEFT;
    int val = A->Data;
    LEFT = A->Rlink;
    delete A;
    //if the list becomes empty;
    if (LEFT == nullptr)
    {
        RIGHT = nullptr;
        return val;
    }
    LEFT->Llink = nullptr;
    return val;
}


int DoublyLinkedList::DeleteAtEnd()
{
    if (RIGHT == nullptr)
    {
        cout << "underflow";
        exit(1);
    }

    Node* A = RIGHT;
    int val = A->Data;
    RIGHT = A->Llink;
    delete A;
    //if the list becomes empty;
    if (RIGHT == nullptr)
    {
        LEFT = nullptr;
        return val;
    }
    RIGHT->Rlink = nullptr;
    return val;
}

