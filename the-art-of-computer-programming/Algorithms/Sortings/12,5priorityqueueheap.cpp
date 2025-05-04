#include <iostream>
using namespace std;
struct Node
{
    int Key;
};

class PriorityQueueHeap
{
    private:
        Node* Recs;
        int num;
    public:
        PriorityQueueHeap(int N)
        {
            num = N;
            Recs = new Node[1+N];
            Recs[1].Key = 15;
            Recs[2].Key = 12;
            Recs[3].Key = 10;
            Recs[4].Key = 6;
            Recs[5].Key = 11;
            
        }
        Node SiftUp(int l, int r, Node R)
        {
            Node Rm = R;
            int Km = R.Key;
            
            Node Ramesh = Recs[1];
            
            int j = l;
            int i;

            while(1)
            {
                i = j; j = j << 1;

            
                if (j < r)
                {
                    if (Recs[j].Key < Recs[j+1].Key) {++j;}
                }
                else
                {
                    if (j > r) {break;}
                }

                if (Km >= Recs[j].Key) 
                    {break;}   //position found, as selected node is larger or equal to the childs.
                else 
                    {Recs[i] = Recs[j];} // else we move the elements up.
            }
            Recs[i] = Rm;
            return Ramesh;
        }
        
        void show()
        {
            for (int i = 1; i <= num; ++i)
            {
                cout << Recs[i].Key << " ";
            }
        }
};
int main()
{
        PriorityQueueHeap H(5);
        Node manoj;
        manoj.Key = 15;
        Node aayo = H.SiftUp(1, 5, manoj);
        cout << aayo.Key << endl;
        H.show();
}