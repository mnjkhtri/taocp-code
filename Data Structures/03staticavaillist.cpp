#include <iostream>
using namespace std;

const int M = 5;

struct Node
{
    int Link;
    int Data;
};

struct AvailList
{
    Node X[M];
    int AVAIL;
    AvailList(): AVAIL(0)
    {
        for (int i = 0; i <= M-2; ++i)
        {
            X[i].Link = i+1;
        }
        X[M-1].Link = -1;
    }

    int GetNode()
    {
        if (AVAIL == -1)
        {
            return -1;
        }
        int p = AVAIL;
        AVAIL = X[p].Link;
        return p;
    }

    void DeleteNode(int p)
    {
        X[p].Link = AVAIL;
        AVAIL = p;
    }
};

int main()
{
    class Queue
    {
        private:
            int F;
            int R;
            AvailList L;
        public:
            Queue(): F()
            {
                F = R = -1;
            }

            void push(int Y)
            {
                int a = L.GetNode();
                if (a == -1) 
                {
                    cout << "overflow" << endl;
                    exit(1);
                }
                L.X[a].Data = Y;
                L.X[a].Link = -1;
            
                if (R == -1)
                { 
                    F = a;
                }
                else
                {
                    L.X[R].Link = a;
                }
                R = a;
            }

            int pop()
            {
                if (F == -1)
                {
                    cout << "underflow" << endl;
                    exit(1);
                }
                int a = F;
                F = L.X[a].Link;
                int val = L.X[a].Data;
                L.DeleteNode(a);
                if (F == -1)
                {
                    R = -1;
                }
                return val;
            }   
    };

    Queue que;
    que.push(3);
    que.push(32);
    que.push(33);
    que.push(31);
    que.push(35);
    que.push(35);
    cout << que.pop();
    return 0;
}