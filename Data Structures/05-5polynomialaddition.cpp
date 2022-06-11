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
        Node* HEAD;
    public:
        Poly()
        {
            HEAD = new Node;
            HEAD->Expo = -1;
            HEAD->Coeff = 0;
            HEAD->Link = HEAD;
        }

        void LeftInsertion(int Expo_, int Coeff_)
        {
            Node* A = new(nothrow) Node;
            if (A == nullptr)
            {
                cout << "overflow";
                exit(1);
            }

            A->Expo = Expo_;
            A->Coeff = Coeff_;
            A->Link = HEAD->Link;
            HEAD->Link = A;
        }

        void add(Poly Poly2)
        {
            Node* P = Poly2.HEAD->Link;    //p points to first node of poly 2
            Node* Q = HEAD->Link;     //q points to first node of poly 1
            Node* Q1 = HEAD;      //q1 will follow q


            while (P->Expo >= 0)
            {
                while (P->Expo < Q->Expo)   //expo of P < expo of Q
                {
                    Q1 = Q;
                    Q = Q->Link;
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
            Node* temp;
            temp = HEAD->Link;
            while (temp != HEAD)
            {
                cout << "+" << temp->Coeff << "x^" << temp->Expo;
                temp = temp->Link;
            }
        }

};

int main()
{
    Poly pu;
    pu.LeftInsertion(1, 6);
    pu.LeftInsertion(2, 8);
    pu.LeftInsertion(49, 9);
    pu.show();
    cout << endl;

    Poly pus;
    pus.LeftInsertion(11, 6);
    pus.LeftInsertion(24, 8);
    pus.LeftInsertion(49, 9);

    pus.show();
    cout << endl;

    pus.add(pu);
    pus.show();

}
