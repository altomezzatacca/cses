#include "bits/stdc++.h"
using namespace std;

int factorial(int n) {
    int ans = 1;
    for (int i = 2; i <= n; i++)
        ans *= i;
    return ans;
}

int perm(string s) {
    int n = s.size();
    int ans = factorial(n);
    int cur = 1;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1])
            cur++;
        else {
            ans /= factorial(cur);
            cur = 1;
        }
    }
    ans /= factorial(cur);
    return ans;
}

int main() {
    string s; cin >> s;
    sort(begin(s), end(s));
    cout << perm(s) << "\n";
    do {
        cout << s << "\n";
    } while (next_permutation(begin(s), end(s)));
}
