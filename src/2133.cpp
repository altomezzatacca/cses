#include "bits/stdc++.h"
using namespace std;
 
// Problema : vogliamo anche rimuovere gli archi, non solo aggiungerli
// Idea : tengo uno storico delle operazioni
// Se l'arco che tolgo è l'ultimo che ho aggiunto, rollbacko di 1 operazione
// Ogni arco ha un intervallo di vita [i, j] (che appartiene a [0, Q] dove Q è il numero di query)
// Al tempo i aggiungo e, al tempo j lo rimuovo; se un arco esiste dall'inizio i = 0, se non viene mai rimosso j = Q
// Se riesco a tenere una DSU per ogni istante che tiene gli archi attivi ho risolto il problema
// Idea : vedo gli intervalli e li metto in un segment. Se devo rispondere alla query del tempo t, so che tutti gli archi
//        che devo considerare sono tutti e soli quelli presenti nei nodi da t alla radice
// Visito il segment seguendo l'ordine DFS -> quando entro in un nodo aggiorno la DSU, quando ci esco elimino gli aggiornamenti
// Quindi mentre sono in un nodo gli unici intervalli vivi nella DSU sono quelli indicati nel percorso nodo -> radice
 
struct dsu{
    vector<int> parent, sz;
    vector<pair<int, int>> history; // storico
    int cc; // componenti connesse
    dsu(int n) : parent(n), sz(n, 1), cc(n){
        iota(begin(parent), end(parent), 0);
    }
    int find (int v){
        return v == parent[v] ? v : find(parent[v]);
    }
    bool merge (int a, int b){
        a = find(a);
        b = find(b);
        if(a == b)
            return false;
        if(sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        history.emplace_back(a, b);
        cc--;
        return true;
    }
    void rollback() { // risalgo all'inverso
        auto [a, b] = history.back();
        cc++;
        history.pop_back();
        sz[a] -= sz[b];
        parent[b] = b;
    }
};
 
void dfs(int i, vector<vector<pair<int, int>>> &segtree, dsu &dsu, vector<int> &ans){
    int sz = ans.size();
    int count = 0;
    for(auto [a, b] : segtree[i])
        count += dsu.merge(a, b);
    if(i >= sz) { // sono in una foglia
        ans[i - sz] = dsu.cc;
    } else { // non sono in una foglia
        dfs(2 * i, segtree, dsu, ans);
        dfs(2 * i + 1, segtree, dsu, ans);
    }
    while(count--)
        dsu.rollback();
}
 
int main(){
    int n, m, k;
    cin >> n >> m >> k;
    int sz = 1;
    while(sz <= k + 1) sz <<= 1;
    vector<vector<pair<int, int>>> segtree(2 * sz);
    // l'arco a-b è vivo in [l, r)
    auto add_edge = [&] (int a, int b, int l, int r) {
        for(l += sz, r += sz; l < r; l >>= 1, r >>= 1){
            if(l & 1) segtree[l++].emplace_back(a, b);
            if(r & 1) segtree[--r].emplace_back(a, b);
        }
    };
    map<pair<int, int>, int> edge_to_l;
    for(int i = 0, a, b; i < m; i++){
        cin >> a >> b;
        a--; b--;
        if(a > b)
            swap(a, b);
        edge_to_l[{a, b}] = 0;
    }
    for(int i = 1, t, a, b; i <= k; i++){
        cin >> t >> a >> b;
        a--; b--;
        if(a > b)
            swap(a, b);
        if(t == 1)
            edge_to_l[{a, b}] = i;
        else{
            add_edge(a, b, edge_to_l[{a, b}], i);
            edge_to_l.erase({a, b});
        }
    }
    for(auto [e, l] : edge_to_l)
        add_edge(e.first, e.second, l, sz); // chi è vivo alla fine muore al tempo sz
    dsu dsu(n);
    vector<int> ans(sz);
    dfs(1, segtree, dsu, ans);
    for(int i = 0; i <= k; i++)
        cout << ans[i] << " \n"[i == k];
}
 
// println("{}", contenitore);
