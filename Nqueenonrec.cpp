#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for(int i = 0, i##_cond = (n); i < i##_cond; i++)
#define FOR(i,a,b) for(int i = (a), i##_cond = (b); i < i##_cond; i++)
#define calc(i,j)  if((n*i+j)%tnum == ti){ int bitj = 1<<j; c +=     nonrec(2, (biti<<1|bitj)<<1, biti|bitj, (biti>>1|bitj)>>1); }
#define calc2(i,j) if((n*i+j)%tnum == ti){ int bitj = 1<<j; c += 2 * nonrec(2, (biti<<1|bitj)<<1, biti|bitj, (biti>>1|bitj)>>1); }
#define tnum 16
int sz, mask;
atomic<int> c;

int nonrec(int y, int left, int down, int right){
  int bitmap, bit;
  int res = 0;
  stack<tuple<int,int,int,int>> st;

  while(1){
    if(y == sz){
      if(st.empty()) return res+1;
      else{
	res++;
	tie(y,left,down,right) = st.top();
	st.pop();
      }
    }else{
      bitmap = mask & ~(left | down | right);
      while(bitmap){
	bit = -bitmap & bitmap;
	bitmap ^= bit;
	st.emplace(y+1, (left | bit)<<1, down | bit, (right | bit)>>1);
      }
      if(st.empty()) return res;
      else{
	tie(y,left,down,right) = st.top();
	st.pop();
      }
    }
  }
}

void base(int n){
  auto odd = [&](int ti){
    int pos = 1<<ti;
    rep(i,n/2){
      int biti = 1<<i;
      rep(j,i-1)   calc2(i,j);
      FOR(j,i+2,n) calc2(i,j);
    }
   
    int i = n/2;
    int biti = 1<<i;
    rep(j,i-1)   calc(i,j);
    FOR(j,i+2,n) calc(i,j);
  };

  auto even = [&](int ti){
    int pos = 1<<ti;
    rep(i,n/2){
      int biti = 1<<i;
      rep(j,i-1)   calc2(i,j);
      FOR(j,i+2,n) calc2(i,j);
    }
  };
  
  vector<thread> ts(tnum);
  if(n&1) rep(i,tnum) ts[i] = thread(odd,  i);
  else    rep(i,tnum) ts[i] = thread(even, i);
  rep(i,tnum) ts[i].join();
}

int findSolution(int n){
  sz = n;
  mask = (1 << n) - 1;
  base(n);
  return c;
}

// void base(int n){
//   auto f = [&](int ti){
//     int b = 1 << ti;
//     c += 2 * nonrec(1,b<<1,b,b>>1);
//   };
  
//   vector<thread> ts(n/2);
//   rep(i,n/2) ts[i] = thread(f, i);
//   if(n&1){
//     int b = 1 << (n/2);
//     c += nonrec(1,b<<1,b,b>>1);
//   }
//   rep(i,n/2) ts[i].join();
// }

// int findSolution(int n){
//   sz = n;
//   mask = (1 << n) - 1;
//   base(n);
//   return c;
// }
