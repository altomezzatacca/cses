#include "bits/stdc++.h"
using namespace std;

string to_binary(int n, int bt){
    string ans = string(bt, '0');
    for(int i = 0; i < bt; i++)
        if(n & (1 << i))
            ans[bt - i - 1] = '1';
    return ans;
}

int gray(int n){
    return n ^ (n >> 1);
}

int main(){
    int n; cin >> n;
    int nn = 1 << n;
    for(int i = 0; i < nn; i++)
        cout << to_binary(gray(i), n) << "\n";
}
