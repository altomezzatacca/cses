#include "bits/stdc++.h"
using namespace std;

int main(){
    string s; cin >> s;
    vector<int> v(26);
    int n = s.size();
    for(int i = 0; i < n; i++)
        v[s[i] - 'A']++;
    int b = 2;
    for(int i = 0; i < 26; i++)
        if(v[i] & 1)
            b--;
    if(b <= 0){
        cout << "NO SOLUTION\n";
        return 0;
    }
    string ans = "";
    for(int i = 0; i < 26; i++){
        if(v[i] & 1) continue;
        ans = ans + string(v[i] / 2, 'A' + i);
    }
    string x = ans;
    for(int i = 0; i < 26; i++)
        if(v[i] & 1)
            ans = ans + string(v[i], 'A' + i);
    reverse(begin(x), end(x));
    ans = ans + x;
    cout << ans << "\n";
}
