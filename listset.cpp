#include <bits/stdc++.h>
using namespace std;

// void filter(bool (*func) (int), list<int> &l){
//   vector<atomic<int>> a(100000);
//   auto itr = l.begin();
//   for(int i = 0, ilim = l.size(); i != ilim; i++){
//     int el = *itr;
//     if(a[el] == 1) ++itr;
//     else if(a[el] == -1) itr = l.erase(itr);
//     else if(func(el)){
//       a[el] = 1;
//       ++itr;
//     }else{
//       a[el] = -1;
//       itr = l.erase(itr);
//     }
//   }
// }

atomic<int> pos;

void filter(bool (*func) (int), list<int> &l){
  int tnum = 16;
  pos.store(0);
  int poslim = (1<<tnum)-1;
  int compsz = l.size() / tnum;
  vector<atomic<int>> a(100000);
  
  auto f = [&](int ti){
    int beg = compsz * ti;
    int en  = compsz * (ti+1);
    if(ti == tnum - 1) en = l.size();
    
    auto itr = l.begin();
    for(int i = 0; i < beg; i++) ++itr;
    pos += 1 << ti;
    while(pos != poslim) ;
    
    for(int i = beg; i < en; i++){
      int el = *itr;
      if(a[el] == 1) ++itr;
      else if(a[el] == -1) itr = l.erase(itr);
      else if(func(el)){
	a[el] = 1;
	++itr;
      }else{
	a[el] = -1;
	itr = l.erase(itr);
      }
    }
  };
  
  vector<thread> ts(tnum);
  for(int i = tnum-1; i >= 0; i--)
    ts[i] = thread(f,i);
  for(auto &t : ts) t.join();
}
