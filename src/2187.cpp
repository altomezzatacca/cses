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
 
int factorial (int n){
  int mod = 1e9 + 7;
  long long ans = 1;
  for(int i = 2; i <= n; i++)
    ans = (ans * i) % mod;
  return (int)ans;
}
 
int solve(int n, int x, int y){
  if(n & 1) return 0;
  if(x > n / 2) return 0;
  if(x == n / 2) return 1;
  if(x + y == n) return 1;
  int ans = 1;
  int mod = 1e9 + 7;
  n >>= 1;
  int a = factorial(2 * n - x - y);
  int b = factorial(n - x);
  b = fast_exp(b, mod - 2, mod);
  int c = factorial(n - y);
  c = fast_exp(c, mod - 2, mod);
  int d = factorial(n - 1 - x);
  d = fast_exp(d, mod - 2, mod);
  int e = factorial(n + 1 - y);
  e = fast_exp(e, mod - 2, mod);
  long long A = 1;
  A = (A * a) % mod;
  A = (A * b) % mod;
  A = (A * c) % mod;
  long long B = 1;
  B = (B * a) % mod;
  B = (B * d) % mod;
  B = (B * e) % mod;
  ans = A - B;
  if(ans < 0) ans += mod;
  return ans;
}
 
int main() {
    //ifstream cin("test_input.txt");
    //ofstream cout("output.txt");
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    string S; cin >> S;
    int x = 0, y = 0;
    int k = S.size();
    bool possible = 1;
    for(int i = 0; i < k; i++){
        if(S[i] == '(') x++;
        else y++;
        if(y > x) possible = 0;
    }
    cout << (possible ? solve(n, x, y) : 0) << endl;
    return 0;
}
