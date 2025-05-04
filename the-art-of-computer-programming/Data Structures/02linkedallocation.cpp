 #include <iostream>
using namespace std;

struct Node
{
    Node* Link;
    int Data;
};

class Stack
{
    private:
        Node* T;
    public:
        Stack(): T(nullptr) {}

        void push(int Y)
        {
            //get
            Node* P = new(nothrow) Node;
            if (P == nullptr) 
            {
                cout << "overflow" << endl;
                exit(1);
            }

            //put
            P->Data = Y;
            P->Link = T;

            //change
            T = P;
        }

        int pop()
        {
            //check
            if (T == nullptr)
            {
                cout << "underflow" << endl;
                exit(1);
            }
            
            Node* P = T;
            T = P->Link;
            return P->Data;
            delete P;
        }
};

class Queue
{
    private:
        Node* F;
        Node* R;
    public:
        Queue()
        {
            F = R = nullptr;
        }

        void push(int Y)
        {
            Node* A = new(nothrow) Node;
            if (A == nullptr) 
            {
                cout << "overflow" << endl;
                exit(1);
            }
            A->Data = Y;
            A->Link = nullptr;
            
            if (R == nullptr)
            {
                F = A;
            }
            else
            {
                R->Link = A;

            }
            R = A;
        }

        int pop()
        {
            if (F == nullptr)
            {
                cout << "underflow" << endl;
                exit(1);
            }
            Node* A = F;
            F = A->Link;
            int val = A->Data;
            delete A;
            if (F == nullptr)
            {
                R = nullptr;
            }
            return val;
        }
};



int main()
{
    Queue S;
    S.push(243);
    S.push(23);
    S.push(3);
    cout << S.pop() << endl;
    cout << S.pop() << endl;
    cout << S.pop() << endl;
    cout << S.pop() << endl;
    return 0;
}