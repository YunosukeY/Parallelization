#include <bits/stdc++.h>
using namespace std;

atomic<int> pos;

void filter(bool (*func) (int), list<int> &l){
  int tnum = 16;
  pos.store(0);
  int compsz = l.size() / tnum;
  
  auto f = [&](int ti){
    int beg = compsz * ti;
    int en  = compsz * (ti+1);
    if(ti == tnum - 1) en = l.size();
    
    auto itr = l.begin();
    for(int i = 0; i < beg; i++) ++itr;
    pos++;
    while(pos != tnum) ;
    
    for(int i = beg; i < en; i++){
      if(!func(*itr))
	itr = l.erase(itr);
      else
	++itr;
    }
  };

  auto g = [&](int ti){
    int beg = compsz * ti;
    int en  = compsz * (ti+1);
    if(ti == tnum - 1) en = l.size();
    
    auto itr = l.end();
    int ilim = l.size() - beg;
    for(int i = 0; i < ilim; i++) --itr;
    pos++;
    while(pos != tnum) ;
    
    for(int i = beg; i < en; i++){
      if(!func(*itr))
	itr = l.erase(itr);
      else
	++itr;
    }
  };
  
  vector<thread> ts(tnum);
  for(int i = tnum/2-1; i >= 0; i--)
    ts[i] = thread(f,i);
  for(int i = tnum/2; i < tnum; i++)
    ts[i] = thread(g,i);
  for(auto &t : ts) t.join();
}
