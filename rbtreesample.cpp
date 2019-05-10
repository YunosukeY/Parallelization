#include <bits/stdc++.h>
using namespace std;

class rbtree {
public:
  struct node {
    int key;
    int red;
    node *par, *ch[2]; // {left, right}
    node(int key):key(key),red(1) {
      par = ch[0] = ch[1] = NULL;
    }
  };

  unsigned sz;
  node *root, *nil;

  rbtree():sz(0) {
    nil = new node(-1);
    nil->red = 0;
    root = nil->par = nil->ch[0] = nil->ch[1] = nil;
  }

  unsigned size() { return sz; }

  void print()const{ print(root,0,0); }
  void print(node *v, int dep, int lr) const{
    if(v == nil) return;
    print(v->ch[1],dep+1,1);
    for(int i = 0; i < dep; i++) printf("  ");
    if(!lr) printf("--");
    else if(lr == 1) printf("「");
    else printf("Ｌ");
    if(v->red) printf("R ");
    else printf("B ");
    printf("%d\n",v->key);
    print(v->ch[0],dep+1,2);
  }

  void rotate(node *x, int d) {
    int e = d^1;
    node *y = x->ch[e];
    x->ch[e] = y->ch[d];
    if(y->ch[d] != nil) y->ch[d]->par = x;
    y->par = x->par;
    if(x->par == nil) root = y;
    else if(x == x->par->ch[d]) x->par->ch[d] = y;
    else x->par->ch[e] = y;
    y->ch[d] = x;
    x->par = y;
  }

  node *insert(int key) {
    node *x = root, *y = nil;
    while(x != nil) {
      y = x;
      if(key != x->key) x = x->ch[key > x->key];
      else return x;
    }
    sz++;
    node *z = new node(key);
    z->par = y;
    if(y == nil) root = z;
    else y->ch[z->key >= y->key] = z;
    z->ch[0] = z->ch[1] = nil;
    insert_update(z);
    nil->par = nil->ch[0] = nil->ch[1] = nil;
    return z;
  }

  void insert_update(node *z) {
    node *y;
    while(z->par->red) {
      int d = z->par == z->par->par->ch[0]? 0: 1, e = d^1;
      y = z->par->par->ch[e];
      if(y->red) {
	z->par->red = 0;
	y->red = 0;
	z->par->par->red = 1;
	z = z->par->par;
      }
      else if(z == z->par->ch[e]) {
	z = z->par;
	rotate(z,d);
      }
      else {
	z->par->red = 0;
	z->par->par->red = 1;
	rotate(z->par->par,e);
      }
    }
    root->red = 0;
  }

};

function<void()> insert_vec(vector<int> &v) {
  rbtree t;
  for(int i = 0, ilim = v.size(); i < ilim; i++){
    t.insert(v[i]);
  }
  return [=](){t.print();};
}
