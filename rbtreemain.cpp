#include<functional>
#include<iostream>
#include<vector>
#include "clock.h"
#include "rbtreesample.cpp"

using namespace std;

function<void()> insert_vec(vector<int>&);
void tree_print();

int main(void) {
  int n;
  int x;
  vector<int> v;
  cin>>n;
  for(int i=0; i<n; i++) {
    cin>>x;
    v.push_back(x);
  }
  start_counter();
  function<void()> print = insert_vec(v);
  print_counter();
  print();
}
