#include <iostream>
using namespace std;
//size of set A = N, size of set B = M
//there are total M^N functions out of which N!/(N-M)! one to one functions
//so probability is [M!/(M-N)!]/M^N, which for equal values of M and N is sqrt(2pi m)/e^M
//adding one item might ruin everything lmao

//avoid uniqueness and also hash functions must break the clusters of almost identical keys to avoid collision; let range be 0<= to <M
//1)division method: h(K) = K mod M; some values of M could create biases	//key has to be non negative numbers, maybe
//choose prime M such that r^k not equal to plus minus a for small values of k and a where r is the radix (10, 256)

//2)multiplication method: we multiply the key with a number (0 to 1) take the fractional part and multiply with M
//to do so: make M the power of 2 ie M = 2^m then multiply K with a coprime number A (to the max word size) and extract the most significant m bits
//when the fraction by which we multiply ie A/wordsize = golden ratio = 0.618 (and also 1- that) has good scattering property

//rw floyd idea: A = (40 56 93 B4 62 46 5C 68)
//K*A/wordsize*M

struct Node
{
		int Key;
		int Link;
};

class ChainedHashTable
{
	private:
		int M;	//so M is that same M we discussed above but also the total size of the records
		Node* TABLE;
		int R;	//a auxillary variable to find empty spaces; as all the table[j] in the range R<=j<=M are always occupied
				//so in a emtpy table R = M
	public:
		ChainedHashTable()
		{
			M = 9;
			TABLE = new Node[M];	//one extra node is needed to check the value of R
			R = M;
			
			for (int i = 0; i < M; ++i)
			{
				TABLE[i].Key = -1;	//-1 key implies that this position is not occupied
				TABLE[i].Link = -1;	//-1 of link does not imply that position is empty it just means that the node is not pointing anywhere
			}
		}
		
		int HashFunction(int Km)	//of course ranges from 0 to M-1s: M is 9 here
		{
			//seven keys possiblity
			if (Km == 1) {return 2;}
			if (Km == 2) {return 0;}
			if (Km == 3) {return 3;}
			if (Km == 4) {return 0;}
			if (Km == 5) {return 4;}
			if (Km == 6) {return 0;}
			if (Km == 7) {return 1;}
			if (Km == 9) {return 5;}
			if (Km == 8) {return 2;}
			if (Km == 10) {return 1;}
		}
		
		int SearchInsert(int Km)
		{
			int i = HashFunction(Km);
			
			if (TABLE[i].Key >= 0)
			{
				while(1)
				{
					//position for record is not empty
					//check
					if (TABLE[i].Key == Km)	//record found
					{
						cout << "key " << Km << "is found at the position " << i << endl;
						return i;
					}	
					
					if (TABLE[i].Link < 0)
					{
						break;
					}
					else
					{
						i = TABLE[i].Link;
					}
				}
				
				//oops not found in any of the links
				do
				{
					--R;
					if (R < 0)	//instead of check evertime we could make a conventional 0th node
					{
						cout << "overflow" << endl;
						exit(1);
					}
				}while (TABLE[R].Key >= 0);

				TABLE[i].Link = R;
				i = R;
			}
			cout << "key " << Km << " stored at the positon " << i << endl;
			TABLE[i].Key = Km;			
			return i;
		}
		void show()
		{
			for (int i = 0; i < M; ++i)
			{
				cout << TABLE[i].Key << " ";
			}
		}
};

int main()
{
	ChainedHashTable h;
	h.SearchInsert(3);
	h.SearchInsert(2);
	h.SearchInsert(1);
	h.SearchInsert(4);
	h.SearchInsert(5);
	h.SearchInsert(7);
	h.SearchInsert(6);
	h.SearchInsert(8);
	h.SearchInsert(9);
	h.SearchInsert(10);
	h.show();
}
