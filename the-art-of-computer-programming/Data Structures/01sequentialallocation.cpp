#include <iostream>
using namespace std;

const int M = 5;
//pushes: increase check do
//pops: check do decrease

class Stack
{
    private:
        int T;
        int X[M];
    public:
        Stack(): T(0) {}

        void push(int Y)
        {
            ++T;

            if (T > M) 
                {
                    cout << "overflow";
                }

            X[T] = Y;
        }

        int pop()
        {
            if (T == 0)
            {
                cout << "underflow";
            }

            return X[T];

            --T;
        }
};




class Queue
{
    private:
        int F;
        int R;
        int X[M];
    public:
        Queue(): F(1), R(1) {}
        
        void push(int Y)
        {
            R = (R == M)? 1: R+1;

            if (R == F) 
                {
                    cout << "overflow" << endl;
                    exit(1);
                }

            X[R] = Y;
        }

        int pop()
        {
            if (F == R)
            {
                cout << "underflow" << endl;
                exit(1);
            }

            F = (F == M)? 1: F+1;

            return X[F];
        }
};

int main()
{
    Queue Q;

    Q.push(34);

    Q.push(234);

    cout << Q.pop();
}