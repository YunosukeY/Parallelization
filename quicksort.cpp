#include<bits/stdc++.h>
using namespace std;

#define rep(i,n) for(int i=0,i##_cond=(n);i<i##_cond;i++)
#define FOR(i,a,b) for(int i=(a),i##_cond=(b);i<i##_cond;i++)
using vi  = vector<int>;

// void quicksort(vector<int> &a) {
//   int minv = 1<<30, maxv = -minv;
//   for(auto x : a){
//     minv = min(minv, x);
//     maxv = max(maxv, x);
//   }

//   vi bucket(maxv-minv+1);
//   for(auto x : a) bucket[x-minv]++;

//   int i = 0;
//   rep(j,bucket.size()){
//     rep(k,bucket[j]){
//       a[i] = j+minv;
//       i++;
//     }
//   }
// }

#define tnum 16
void quicksort(vector<int> &a){
  atomic<int> minv(1<<30), maxv(-minv);

  int sz = a.size();
  int compsz = sz / tnum;
  atomic<int> check(0);
  
  auto f = [&](int ti){
    // 担当範囲[beg,en)
    int beg = compsz * ti;
    int en  = compsz * (ti+1);
    if(ti == tnum - 1) en = sz;

    // 最小値、最大値
    int lminv = 1<<30, lmaxv = -lminv;
    FOR(i,beg,en){
      lminv = min(lminv, a[i]);
      lmaxv = max(lmaxv, a[i]);
    }
    minv = min(minv.load(), lminv);
    maxv = max(maxv.load(), lmaxv);
  };
  
  vector<thread> ts1(tnum);
  rep(i,tnum) ts1[i] = thread(f,i);
  rep(i,tnum) ts1[i].join();

  vector<atomic<int>> bucket(maxv - minv + 1);
  check.store(0); 
  auto g = [&](int ti){
    int lminv = minv;
    
    // 担当範囲[beg,en)
    int beg = compsz * ti;
    int en  = compsz * (ti+1);
    if(ti == tnum - 1) en = sz;
    
    // 数を数える
    FOR(i,beg,en) bucket[a[i]-lminv]++;
    check++;
    while(check.load() != tnum) ;

    // バケツから並べる
    beg = bucket.size() * ti / tnum;
    en  = bucket.size() * (ti + 1) / tnum;
    if(ti == tnum - 1) en = bucket.size();
    int j = 0;
    rep(i,beg) j += bucket[i];
    FOR(i,beg,en){
      rep(k,bucket[i]){
    	a[j] = i+lminv;
    	j++;
      }
    }
  };

  vector<thread> ts2(tnum);
  rep(i,tnum) ts2[i] = thread(g,i);
  rep(i,tnum) ts2[i].join();  
}
