#include "bits/stdc++.h"
using namespace std;
static int N, m;
 
struct treap{
    int p, sz;
    char c;
    treap *L, *R;
    treap() {} // costruttore vuoto per permettermi prealloc
    treap(char x){
        L = R = nullptr;
        c = x;
        p = rand();
        sz = 1;
    }
    treap *join(treap *_L, treap *_R){
        L = _L;
        R = _R;
        sz = 1;
        if(L) sz += L->sz;
        if(R) sz += R->sz;
        return this;
    }
};
 
inline int t_sz(treap* T){
    if(T) return T->sz;
    return 0;
}
 
inline pair<treap*, treap*> split(treap *T, int x){
    if(!T) return {nullptr, nullptr};
    if(t_sz(T->L) < x){
        auto [RL, RR] = split(T->R, x - t_sz(T->L) - 1);
        return {T->join(T->L, RL), RR};
    } else {
        auto [LL, LR] = split(T->L, x);
        return {LL, T->join(LR, T->R)};
    }
}
 
inline treap *merge(treap *L, treap *R){
    if(!L) return R;
    if(!R) return L;
    if(L->p > R->p){
        return L->join(L->L, merge(L->R, R));
    } else {
        return R->join(merge(L, R->L), R->R);
    }
}
 
treap *prealloc;
 
inline treap *insert(treap *T, char c, int i){
    auto [L, R] = split(T, i);
    treap *X = prealloc++;
    *X = treap(c);
    return merge(L, merge(X, R));
}
 
inline treap *erase(treap *T, int i){
    auto [L, MR] = split(T, i);
    auto [M, R] = split(MR, 1);
    return merge(L, R);
}
 
inline char qfind(treap *&T, int i){ // valore in posizione i-esima
    auto [L, MR] = split(T, i); // smonto l'albero
    auto [M, R] = split(MR, 1); // trovo il valore
    char ans = M->c;
    T = merge(L, merge(M, R)); // rimonto l'albero
    return ans;
}
 
inline void query(treap *&T, int i, int j){
    auto [L, MR] = split(T, i);
    auto [M, R] = split(MR, j + 1 - i); // davvero j - i ?
    T = merge(L, merge(R, M));
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> m;
    prealloc = new treap[N + m]; // prealloco spazio per N nodi iniziali ed eventuali M nodi
    treap *T = nullptr;
    string S; cin >> S;
    for(int i = 0; i < N; i++)
        T = insert(T, S[i], i); // i + 1 perchè cses è 1-based
    for(int q = 0, i, j; q < m; q++){
        cin >> i >> j;
        i--; j--;
        query(T, i, j);
    }
    for(int i = 0; i < N; i++)
        cout << qfind(T, i);
}
