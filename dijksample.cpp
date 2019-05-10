#include<bits/stdc++.h>
using namespace std;

#define rep(i,n) for(unsigned i=0,i##_cond=(n);i<i##_cond;++i)
#define pb push_back

using Cost = unsigned;
constexpr Cost inf = 1<<30;
#define scale 1000

class node {
public:
  unsigned v;
  Cost d;
  node(unsigned _a, Cost _b):v(_a),d(_b){}
  bool operator<(const node &n) const { return d > n.d; }
};
class edge {
public:
  unsigned to;
  Cost d;
  edge(){}
  edge(unsigned _to, Cost _d):to(_to),d(_d){}
};
class dijkstra{
public:
  vector<vector<edge>> G;
  vector<Cost> dist;
  vector<unsigned> prev;

  dijkstra(unsigned s,unsigned t,const vector<vector<edge>> &_G):G(_G){ // sからtへの最短経路
    dist.resize(G.size(),inf);
    prev.resize(G.size(),-1);
  
    priority_queue<node> que;
    que.push(node(s, 0));
    dist[s] = 0;
    
    while(!que.empty()){
      unsigned v = que.top().v;
      Cost d = que.top().d;
      que.pop();
      if(v == t) break;
      
      rep(i, G[v].size()){
	Cost tmp = d + G[v][i].d;
	if(dist[G[v][i].to] > tmp){
	  dist[G[v][i].to] = tmp;
	  prev[G[v][i].to] = v;
	  que.push(node(G[v][i].to, tmp));
	}
      }
    }
  }

  
  deque<unsigned> getpath(unsigned t){ // tへの最短経路を返す
    deque<unsigned> path;
    while(t != -1){
      path.push_front(t);
      t = prev[t];
    }
    return path;
  }
};

deque<unsigned> NearestPath(unsigned sz,const vector<unsigned>& ei1,const vector<unsigned>& ei2,const vector<double>& ed,unsigned s,unsigned t){
  vector<vector<edge>> g(sz);
  rep(i,ei1.size()){
    g[ei1[i]].pb(edge(ei2[i],ed[i]*scale));
    g[ei2[i]].pb(edge(ei1[i],ed[i]*scale));
  }
  dijkstra d(s,t,g);
  return d.getpath(t);
}
