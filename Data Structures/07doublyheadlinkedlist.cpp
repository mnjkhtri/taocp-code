#include <iostream>
using namespace std;

struct Node
{
    Node* Llink;
    Node* Rlink;
    int Data;
};

class DoublyHeadLinkedList
{
    private:
        Node* HEAD;
    public:
        DoublyHeadLinkedList() 
        {
            HEAD->Data = -1; 
            HEAD->Llink = nullptr;
            HEAD->Rlink = nullptr;
        }
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
}


int DoublyHeadLinkedList::DeleteP(Node* P)
{   
    if (P == HEAD)
    {
        cout << "cannot delete jhead you dumb bitch";
        return -1;
    }

    Node* A = P;
    A->Llink->Rlink = A->Rlink;
    A->Rlink->Llink = A->Llink; 
    int val = A->Data;
    delete A;
    return val;
}   


void DoublyHeadLinkedList::InsertBefore(Node* P, int Y)
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

void DoublyHeadLinkedList::InsertAfter(Node* P, int Y)
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

void DoublyHeadLinkedList::InsertAtBeginning(int Y)
{
    Node* A = new(nothrow) Node;
    
    if (A == nullptr)
    {
        cout << "overflow";
        exit(1);
    }

    A->Data = Y;
    A->Llink = HEAD;
    A->Rlink = HEAD->Rlink;
    HEAD->Rlink->Llink = A;
    HEAD->Rlink = A;
}

void DoublyHeadLinkedList::InsertAtEnd(int Y)
{
    Node* A = new(nothrow) Node;
    
    if (A == nullptr)
    {
        cout << "overflow";
        exit(1);
    }

    A->Data = Y;
    A->Rlink = HEAD;
    A->Llink = HEAD->Llink;
    HEAD->Llink->Rlink = A;
    HEAD->Llink = A; 
}

int DoublyHeadLinkedList::DeleteAtBeginning()
{
    Node* A = HEAD->Rlink;
    int val = A->Data;
    HEAD->Rlink = A->Rlink;
    A->Rlink->Llink = HEAD;
    delete A;
    return val;
}


int DoublyHeadLinkedList::DeleteAtEnd()
{
    Node* A = HEAD->Llink;
    int val = A->Data;
    HEAD->Llink = A->Llink;
    A->Llink->Rlink = HEAD;
    delete A;
    return val;
}

