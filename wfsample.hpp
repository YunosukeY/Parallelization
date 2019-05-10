#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0,i##_cond=(n);i<i##_cond;++i)

struct node {
  int v;
  double d;
  node(int _a, double _b):v(_a),d(_b){}
  bool operator<(const node &n) const { return d > n.d; }
};
struct edge {
  int to;
  double d;
  edge(int _to, double _d):to(_to),d(_d){}
};
class dijkstra{
public:
  vector<vector<edge>> G;
  vector<double> dist;
  vector<int> prev;

  dijkstra(int s,int t,const vector<vector<edge>> &_G):G(_G){ // sからの最短経路
    dist.resize(G.size(),1 << 30);
    prev.resize(G.size(),-1);
  
    priority_queue<node> que;
    que.push(node(s, 0));
    dist[s] = 0;
    
    while(!que.empty()){
      int v = que.top().v, d = que.top().d;
      // if(v == t) break;
      que.pop();
      
      rep(i, G[v].size()){
	int tmp = d + G[v][i].d;
	if(dist[G[v][i].to] > tmp){
	  dist[G[v][i].to] = tmp;
	  prev[G[v][i].to] = v;
	  que.push(node(G[v][i].to, tmp));
	}
      }
    }
  }

  deque<int> getpath(int t){ // tへの最短経路を返す
    deque<int> path;
    while(t != -1){
      path.push_front(t);
      cout << t << endl;
      t = prev[t];
    }
    return path;
  }
};

deque<int> NearestPath(unsigned nodeSize,
			const vector<unsigned>& e1,
			const vector<unsigned>& e2,
			const vector<double>& ed,
			unsigned s, unsigned g){
  vector<vector<edge>> graph(nodeSize);
  rep(i,e1.size()){
    graph[e1[i]].push_back(edge(e2[i],ed[i]));
    graph[e2[i]].push_back(edge(e1[i],ed[i]));
  }
  dijkstra dijk(s,g,graph);
  return dijk.getpath(g);
}
