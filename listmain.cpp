#include<iostream>
#include<list>
#include<cmath>
#include"clock.h"
using namespace std;
#define N 100000
int primes[N];

void eratosthenes() {
  for(int i=0; i<N; i++) {
    primes[i]=1;
  }
  primes[0]=0;
  primes[1]=0;
  for(long long int i=2; i<N; i++) {
    if(primes[i]) {
      for(long long int j=2; j*i<N; j++) {
	primes[i*j]=0;
      }
    }
  }
}

void filter(bool (*func) (int), list<int> &l);

bool f(int x) {
  int ans = 0;
  for(int i=2; i<=x; i++) {
    if(primes[i]) {
      while(x%i==0) {
	x = x/i;
	ans++;
      }
    }
  }
  return ans%2==0;
}

int main(void) {

  int n;
  int x;
  list<int> l;
  cin>>n;
  for(int i=0; i<n; i++) {
    cin>>x;
    l.push_back(x);
  }
  eratosthenes();
  start_counter();
  filter(f, l);
  print_counter();

  for(auto itr=l.begin(); itr!=l.end(); itr++) {
    cout<< *itr <<endl;
  }
   return 0;
}
