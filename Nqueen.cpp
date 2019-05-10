#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for(int i = 0, i##_cond = (n); i < i##_cond; i++)
#define FOR(i,a,b) for(int i = (a), i##_cond = (b); i < i##_cond; i++)
#define calc(i,j)  if((n*i+j)%tnum == ti){ int bitj = 1<<j; c +=     rec(2, (biti<<1|bitj)<<1, biti|bitj, (biti>>1|bitj)>>1); }
#define calc2(i,j) if((n*i+j)%tnum == ti){ int bitj = 1<<j; c += 2 * rec(2, (biti<<1|bitj)<<1, biti|bitj, (biti>>1|bitj)>>1); }
#define tnum 16
int sz, mask;
atomic<int> c;

int rec(int y, int left, int down, int right){
  int bitmap, bit;

  if(y == sz){
    //c++;          /* 配置が完了したので解の個数をカウントする */
    return 1;
  }else{
    bitmap = mask & ~(left | down | right); /* 配置可能フィールド */
    int sum = 0;
    while(bitmap){
      bit = -bitmap & bitmap;       /* 最も下位の１ビットを抽出 */
      bitmap ^= bit;
      sum += rec(y+1, (left | bit)<<1, down | bit, (right | bit)>>1);
    }
    return sum;
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
