#include <iostream>
#include <vector>
#include "clock.h"

using namespace std;

void quicksort(vector<int> &a);

int main(){
  vector<int> vec;
  while (true){
    int n;
    cin >> n;
    if (cin.eof()) break;
    vec.push_back(n);
  }
  start_counter();
  // === BEGIN ===
  quicksort(vec);
  // === END ===
  print_counter();
  for (auto i=vec.begin(); i!=vec.end(); ++i){
    cout << *i << " ";
  }
  cout << endl;
}
