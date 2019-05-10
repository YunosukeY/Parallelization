#include <bits/stdc++.h>
#include "clock.h"
using namespace std;

atomic<int> ans;
int n;
const string enzan = "+-*/";

double sisoku(int mode, double a, double b) { //四則演算の選択用のメソッド
  double c = 0;
  if (mode == 0) {
    c = a + b;
  } else if (mode == 1) {
    c = a - b;
  } else if (mode == 2) {
    c = a * b;
  } else if (mode == 3) {
    c = a / b;
  }
  return c;
}

bool dousyutu(vector<int> suuzi,int i, int j, int k, int l) {
  double kai = 0;
  string siki;  //式表示用
  try {
    if (i == 0) { // ((a*b)*c)*d
      kai = sisoku(l, sisoku(k, sisoku(j, suuzi[0], suuzi[1]), suuzi[2]), suuzi[3]);
    } else if (i == 1) { // ((a*b)*(c*d))
      kai = sisoku(k, sisoku(j, suuzi[0], suuzi[1]), sisoku(l, suuzi[2], suuzi[3]));
    } else if (i == 2) { // (a*(b*c))*d
      kai = sisoku(l, sisoku(j, suuzi[0] , sisoku(k, suuzi[1], suuzi[2])), suuzi[3]);
    } else if (i == 3) { // a*((b*c)*c)
      kai = sisoku(j, suuzi[0], sisoku(l, sisoku(k, suuzi[1], suuzi[2]), suuzi[3]));
    } else if (i == 4) { // a*(b*(c*d))
      kai = sisoku(j, suuzi[0], sisoku(k, suuzi[1], sisoku(l, suuzi[2], suuzi[3])));
    }
  } catch (...) {
    //０で割るときの例外
    kai = 0;
  }
		
  if((kai < n + 0.001)&&(kai > n - 0.001)){
    return true;
    // cout << siki << "=" << kai << endl;
  }
  // if((kai < n + 0.001)&&(kai > n - 0.001)&&(kai != (double)n)){
  //     //cout << siki << "=" << kai << endl;
  // }
  return false;
}


int main() {
  cin >> n;

  start_counter();
  // ===== BEGIN =====

  ans.store(0);
  
  auto f = [&](int aa){
    for (int b = 0; b < 10; b++)
      for (int c = 0; c < 10; c++)
	for (int d = 0; d < 10; d++) {
	  //　i:計算順序　j,k,l:四則演算選択
	  // keisan retu = keisan(n, aa, b, c, d);
	  vector<int> suuzi = {aa,b,c,d};
	  for (int i = 0; i < 5; i++)
	    for (int j = 0; j < 4; j++) 
	      for (int k = 0; k < 4; k++) 
		for (int l = 0; l < 4; l++) 
		  if(dousyutu(suuzi, i, j, k, l)){
		    ans++;
		    //cout << ans << endl;
		    goto L;
		  }
	L:
	  ;
	}
  };

  vector<thread> ts(10);
  for (int a = 0; a < 10; a++){
    ts[a] = thread(f,a);
  }
  for(auto &t : ts) t.join();
  
  // ===== END =====
  print_counter();
  cout << ans << endl;
}
