//grey code of n tupes is a sequence v0...v_2^-1 where each differes by 1 bit positio
//while grey cycle is where vk differes from v_(k+1)mod2^n in one bit pstions
//gray cycle would be an oriented hamiltonian cycle on the n cube where each vertex are named
//if v's are treated as binary numbers then there are deltas integers, d0, ...d2^n-1 such
//v(k+1)mod2^n = vk XOR 2^dk for 0 <= k <2^n
//it is essentially a ruler function dk = rho(k+1) but the final value of n-1 instead of n
//the individuals dk lies in the range [0,n) 

//wtf i got my self into pls pageno 294

//there is also non binary grey codes

#include <iostream>
using namespace std;