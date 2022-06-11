 #include <iostream>
using namespace std;

struct Node
{
    Node* Link;
    int Data;
};

class LinkedList //list has 1)insert begnning 2)insert after 3)delete after 4) delete beggining
{
    private:
        Node* H;
    public:
        LinkedList(): H(nullptr) {};

        void InsertAtBeginning(int Y);
        int DeleteAtBeginning();
        void InsertAfter(Node* P, int Y);
        int DeleteAfter(Node* P);

        void check()
        {
            Node* temp = H->Link;
            temp = temp->Link;
            DeleteAfter(temp);
        }
};

int main()
{
    LinkedList x;

    x.InsertAtBeginning(23);
    x.InsertAtBeginning(56);
    x.InsertAtBeginning(3);
    x.check();
    cout << x.DeleteAtBeginning() << endl;
    cout << x.DeleteAtBeginning() << endl;
    cout << x.DeleteAtBeginning() << endl;
}

void LinkedList::InsertAtBeginning(int Y)
{
    Node* A = new(nothrow) Node;
    if (A == nullptr) 
    {
        cout << "overflow" << endl;
        exit(1);
    }
    A->Data = Y;
    A->Link = H;

    H = A;
}

int LinkedList::DeleteAtBeginning()
{
    if (H == nullptr)
    {
        cout << "underflow";
        exit(1);
    }
    Node* A = H;
    H = A->Link;
    int val = A->Data;
    delete A;
    return val;
}
        void LinkedList::InsertAfter(Node* P, int Y)
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

        int LinkedList::DeleteAfter(Node* P)
        {
            if (P->Link == nullptr)
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