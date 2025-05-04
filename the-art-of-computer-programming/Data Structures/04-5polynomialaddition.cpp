#include <iostream>
using namespace std;

struct Node
{
    Node *Link;
    int Expo;
    int Coeff;
};

class Poly
{
    private:
        Node* H;
    public:
        Poly(): H(nullptr) {}

        void LeftInsertion(int Expo_, int Coeff_)
        {
            Node* A = new(nothrow) Node;
            if (A == nullptr) 
            {
                cout << "overflow" << endl;
                exit(1);
            }
            A->Expo = Expo_;
            A->Coeff = Coeff_;
            A->Link = H;
            H = A;
        }

        void InsertAfter(Node* P, int Expo_, int Coeff_)
        {
            Node* A = new(nothrow) Node;
            if (A == nullptr) 
            {
                cout << "overflow" << endl;
                exit(1);
            }
            A->Expo = Expo_;
            A->Coeff = Coeff_;
            A->Link = P->Link;
            P->Link = A;
        }

        void add(Poly Poly2)
        {
            Node* P = Poly2.H;    //p points to first node of poly 2
            Node* Q = H;     //q points to first node of poly 1
            Node* Q1 = Q;      //q1 will follow q

            //run along the second polynomial untill the end
            while (P != nullptr)
            {
                //for each element of P we find the element in Q with greater or equal power
                while (P->Expo < Q->Expo)   //expo of P < expo of Q
                {
                    Q1 = Q;
                    Q = Q->Link;
                    if (Q == nullptr)   //the polynomial eneded here
                    {
                        while (P != nullptr)
                        {
                            InsertAfter(Q1, P->Expo, P->Coeff);
                            P = P->Link;
                            Q1 = Q1->Link;
                        }
                        return;
                    }
                }

                if (P->Expo == Q->Expo)     //expo of P == expo of Q
                {
                    Q->Coeff += P->Coeff;
                    if (Q->Coeff == 0) //here if after doing add/sub the coeff becomes zero
                    {
                        //deleting a node after the node pointed by Q2;
                        Node* A = Q;
                        Q = Q->Link;
                        Q1->Link = Q;
                        delete A;
                    }
                    else
                    {
                        Q1 = Q;
                        Q = Q->Link;
                    }
                }
                else    //expo of P > expo of Q
                {
                    Node* A = new(nothrow) Node;

                    if (A == nullptr)
                    {
                        cout << "overflow" << endl;
                        exit(1);
                    }

                    A->Expo = P->Expo;
                    A->Coeff = P->Coeff;
                    A->Link = Q;
                    Q1->Link = A;
                    Q1 = A;
                }
                P = P->Link;
            }
        }

        void show()
        {
            Node* temp = H;
            while (temp != nullptr)
            {
                cout << "+(" << temp->Coeff << ")" << "x^" << temp->Expo;
                temp = temp->Link;
            }
        }

};

int main()
{
    Poly pu;
    pu.LeftInsertion(1, 6);
    pu.LeftInsertion(2, 1);
    pu.LeftInsertion(4, 8);
    pu.show();
    cout << endl;

    Poly pus;
    pus.LeftInsertion(1, 6);
    pus.LeftInsertion(4, -8);
    pus.LeftInsertion(8, 9);

    pus.show();
    cout << endl << endl;

    pus.add(pu);
    pus.show();

}
