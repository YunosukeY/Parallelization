#include <bits/stdc++.h>
#include "clock.h"
#define init_matrix(w,h) Matrix(w,vector<long long>(h,0))
#define tnum 8
using namespace std;
typedef vector<vector<long long>> Matrix;

void input_matrix(Matrix& m){
  int w,h;
  cin >> w >> h;
  m = init_matrix(w,h);
  for(int y = 0; y < h; y++){
    for(int x = 0; x < w; x++){
      cin >> m[x][y];
    }
  }
}

void print_matrix(Matrix& m){
  for(int y = 0; y < m.front().size(); y++){
    for(int x = 0; x < m.size(); x++){
      cout << m[x][y] << " ";
    }
    cout << endl;
  }
}    

int main(){
  Matrix A,B,C;
  input_matrix(A);
  input_matrix(B);

  if (A.size() != B.front().size()){
    cerr << "Error: Product is undefined." << endl;
    return 1;
  }

  C = init_matrix(B.size(),A.front().size());

  start_counter();
  // === BEGIN ===
  
  int xlim = B.size();
  int ylim = A.front().size();
  int klim = A.size();
  int compsz = xlim / tnum;

  auto f = [&](int xbeg, int xen){
    for(int x = xbeg; x < xen; x++){
      for(int y = 0; y < ylim; y++){
	int sum = 0;
	for (int k = 0; k < klim; k++){
	  sum += A[k][y] * B[x][k];
	}
	C[x][y] = sum;
      }
    }
  };

  vector<thread> ts(tnum);
  for(int ti = 0; ti < tnum; ti++){
    int tmpbeg = compsz * ti;
    int tmpen  = compsz * (ti+1);
    if(ti == tnum - 1) tmpen = xlim;
    ts[ti] = thread(f,tmpbeg,tmpen);
  }
  for(auto &t : ts) t.join();
  
  // === END ===
  print_counter();

  print_matrix(C);

  return 0;
}
