#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<long long>> Matrix;
#define tnum 16

class F{
public:
  void operator()(Matrix& A, Matrix& B, Matrix& C, int ylim, int klim, int xbeg,int xen){
#define blsz 3 // ~7
    const int tmpa = klim - blsz;
    const int tmpb = ylim - blsz;
    const int kblim = klim%blsz;
    const int tmpc = ylim - kblim;
    for (int x = xbeg; x < xen; x++){
      for(int k = 0; k <= tmpa; k+=blsz){
	const int tmpb1 = B[x][k];
	const int tmpb2 = B[x][k+1];
	const int tmpb3 = B[x][k+2];
	for(int y = 0; y <= tmpb; y+=blsz){	  
	  C[x][y] += A[k][y] * tmpb1;
	  C[x][y+1] += A[k][y+1] * tmpb1;
	  C[x][y+2] += A[k][y+2] * tmpb1;
	  C[x][y] += A[k+1][y] * tmpb2;
	  C[x][y+1] += A[k+1][y+1] * tmpb2;
	  C[x][y+2] += A[k+1][y+2] * tmpb2;
	  C[x][y] += A[k+2][y] * tmpb3;
	  C[x][y+1] += A[k+2][y+1] * tmpb3;
	  C[x][y+2] += A[k+2][y+2] * tmpb3;
	}
      }
      
      for(int kb = 1; kb <= kblim; kb++)
      	for(int y = 0; y < tmpc; y++)
      	  C[x][y] += A[klim-kb][y] * B[x][klim-kb];
      
      int yblim = ylim%blsz;
      for(int yb = 1; yb <= yblim; yb++)
      	for(int k = 0; k < klim; k++)
      	  C[x][ylim-yb] += A[k][ylim-yb] * B[x][k];
    }
  }
};

void product(Matrix& A, Matrix& B, Matrix& C){
  const int xlim = B.size();
  const int ylim = A.front().size();
  const int klim = A.size();

  // auto f = [&](int xbeg,int xen){
  //   for (int x=xbeg; x<xen; x++){
  //     for (int y=0; y<ylim; y++){
  // 	int sum=0;
  // 	for (int k=0; k<klim; k++){
  // 	  sum += A[k][y]*B[x][k];
  // 	}
  // 	C[x][y] = sum;
  //     }
  //   }
  // };

  vector<thread> ts(tnum);
  const int compsz = xlim / tnum;
  F f;
  for(int i = tnum-1; i >= 0; i--){
    int tmpbeg = compsz * i;
    int tmpen  = compsz * (i+1);
    if(i == tnum - 1) tmpen = xlim;
    //ts[i] = thread(f,tmpbeg,tmpen);
    ts[i] = thread(f,ref(A),ref(B),ref(C),ylim,klim,tmpbeg,tmpen);
  }
  for(int i = 0; i < tnum; i++) ts[i].join();
}
