#include "bits/stdc++.h"
using namespace std;

int main(){
    int n; cin >> n;
    if(n == 1){
        cout << 1;
        return 0;
    }
    if(n <= 3){
        cout << "NO SOLUTION";
        return 0;
    }
    int m = (n % 2 == 0 ? n - 1 : n);
    if(m == n) n--;
    while(m > 0){
        cout << m << " ";
        m -= 2;
    }
    while(n > 0){
        cout << n << " ";
        n -= 2;
    }
}
