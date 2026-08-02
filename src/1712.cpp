#include "bits/stdc++.h"
using namespace std;
 
int fast_exp (long long b, int e, int mod){
  long long ans = 1;
  while(e){
    if(e & 1)
      ans = (ans * b) % mod;
    e >>= 1;
    b = (b * b) % mod;
  }
  return ans;
}
 
void solve(){
  int a, b, c; cin >> a >> b >> c;
  int mod = 1e9 + 7;
  int e = fast_exp(b, c, mod - 1);
  int ans = fast_exp(a, e, mod);
  cout << ans << "\n";
}
 
int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    int t; cin >> t;
    while(t--)
      solve();
    return 0;
}
