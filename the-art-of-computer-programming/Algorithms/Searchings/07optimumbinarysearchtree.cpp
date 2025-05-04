#include <iostream>
#include <iomanip> 
//do you remember the huffman tree? i got better nigga
//yet to make tree from the tables
//also i think that we do not need to make the explicit tree here
using namespace std;


//deep shit incoming
void binaryoptimumtree(int, int*, int*, int (*)[11], int (*)[11], int (*)[11]);

int main()
{
	//sometheory in the beginning:
	
	//given probabilies pi's that search item is the Kith element in the tree
	//qi's the probability that the search item is between ki and ki+1th
	//so p1+...+pn+q0+q1+...+qn = 1
	//the tree is to find such that the cost is minimized
	//cost = sum for all(pj*[level+1])+sum for all qk*level(qk)
	//ofc i <= j
	//call the cost for tree from i to j: c(i,j)
	//weight for each tree is given by w(i,j) = pi+1+...+pj+qi+...+qj
	//solution is given by the recursie algorithm as
	
	//c[i,j] = 0 for i ==j
	//c[i,j] = w[i,j] + min(i<k<=j) [c(i,k-1)+c(k,j)]
	//eg for tree from 0 to 3 we have
	//c[0,3] = w[0,3] + min{k = 1,2,3}:{c[0,0]+c[1,3]},{c[0,1]+c[2,3]},{c[0,2]+c[3,3]}
	//here the possible combinations include all the possible subtrees for that shit
	
	//also we keep track of the k's in r[i,j] which gives the possible root for the tree
	//this is O(n^3) but lets optimize it further as
	
	//pay attentio madafaka
	//once we determine r(i,j-1) and r(r+1,j) we have
	//r(i,j-1) <= r(i,j) <= r(i+1,j) (wtf bro?)
	//this narrows the search for coming k's
	
	const int N = 10;
	//these will the frequency access of the sorted records
	//yes i was also wtf bro
	int p[1+N] = {0, 50, 96, 23, 43, 25, 22, 97, 30, 155, 57};
	int q[N+1] = {0, 5, 47, 7, 12, 0, 34, 65, 21, 7, 9};
	
	//bro looks crap;
	//c is for costs, w is for weights, and r is for roots
	int w[1+N][1+N] = {0};
	int c[1+N][1+N] = {0};
	int r[1+N][1+N] = {0};
	
	binaryoptimumtree(N, p, q, w, c, r);
	
	//after the calculation is done
	//if i == j then t(i,j) is null, else left subtree is t(i,r[i,j]-1) and right subtree is t(r[i,j],j)
	//the first is r(0,N) 
}


void binaryoptimumtree(int N, int* p, int* q, int (*w)[11], int (*c)[11], int (*r)[11])
{
	//first stage of determining the total weights and one node optimums
	for (int i = 0; i <= N; ++i)
	{
		//the costs of square nodes is zero, meaning to fill the diagonal of c array
		c[i][i] = 0;
		//getting the weights ready now, also filling the diagonal of w array
		w[i][i] = q[i];
		//this fills the upper triangular side of array w, which completes the work to do in w array
		for (int j = i+1; j <= N; ++j)
		{
			w[i][j] = w[i][j-1]+p[j]+q[j];
		}
	}
	
	//now this fills the second diagonal of the c and r array (on the ups) 
	//no need to fill the diagonal array of r
	for (int i = 1; i <= N; ++i)
	{
		c[i-1][i] = w[i-1][i];
		r[i-1][i] = i;
	}
	//if you display here gives the first optimum arrays for all
	
	//and lets do for other optimums for d = 2 to n
	for (int d = 2; d <= N; ++d)
	{
		for (int j = d; j <= N; ++j)
		{
			int i = j-d; //this will be on the first coordinates of the array index
			
			//now we run k: r[i,j-1] to r[i+1,j]
			//which pictorially means that: suppose c ko euta position bhornu xa ie c[i,j] then tyo position bhanda left and down ma bhako r's ko range
			
			int kmin = r[i][j-1];
			int cmin = c[i][kmin-1] + c[kmin][j];
			for (int k = r[i][j-1]+1; k <= r[i+1][j]; ++k)
			{
				int ch = c[i][k-1] + c[k][j];
				if (ch < cmin)
				{
					cmin = ch;
					kmin = k;
				}
			}
			c[i][j] = w[i][j] + cmin;
			r[i][j] = kmin;
		}
	}
	
	
	//for displaying the arrays
	cout << "w array is" << endl;
	for (int i = 0; i <= N; ++i)
	{
		for (int j = 0; j <= N; ++j)
		{
			cout << setw(5) << w[i][j] << " ";
		}
		cout << endl;
	}
	cout << "c array is" << endl;
	for (int i = 0; i <= N; ++i)
	{
		for (int j = 0; j <= N; ++j)
		{
			cout << setw(5) << c[i][j] << " ";
		}
		cout << endl;
	}
	cout << "r array is" << endl;
	for (int i = 0; i <= N; ++i)
	{
		for (int j = 0; j <= N; ++j)
		{
			cout << setw(5) << r[i][j] << " ";
		}
		cout << endl;
	}
}