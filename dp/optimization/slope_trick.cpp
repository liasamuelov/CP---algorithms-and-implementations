// Apio 2016 fire works.
// date: 2/08/2026

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vll vector<ll>
#define pll pair<ll,ll>
#define vpll vector<pll>
#define lp(i,s,e)for(ll i =s;i<e;++i)


ll n, m;
vector<vll > g;
vector<ll> c, b;
vector<int> a;
vector<priority_queue<ll> > heap;



void merge_heaps(int u, int v) {
    if (heap[u].size() < heap[v].size()) {
        swap(heap[u], heap[v]);
    }

    while (!heap[v].empty()) {
        heap[u].push(heap[v].top());
        heap[v].pop();
    }
}



void dfs(ll node) {

    if (node > n) {
        a[node] = 1;
        b[node] = -c[node];
        heap[node].push(c[node]);
        heap[node].push(c[node]);
        return;
    }

    for (int v : g[node]) {
        dfs(v);

        a[node] += a[v];
        b[node] += b[v];

        merge_heaps(node, v);
    }


    if (node==1) return;

    while (a[node]>1) {
        auto it = heap[node].top();
        heap[node].pop();
        a[node]--;
        b[node]+=it;
    }

    ll p = heap[node].top();
    heap[node].pop();

    ll q = heap[node].top();
    heap[node].pop();

    heap[node].push(p + c[node]);
    heap[node].push(q + c[node]);

    b[node] -= c[node];



}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    int V = n + m;

    g.resize(V + 1);
    c.resize(V + 1);
    a.assign(V + 1, 0);
    b.assign(V + 1, 0);
    heap.resize(V + 1);

    for (int u = 2; u <= V; ++u) {
        int parent;
        cin >> parent >> c[u];

        g[parent].push_back(u);
    }

    dfs(1);

    while (a[1] > 0) {
        b[1] += heap[1].top();
        heap[1].pop();
        --a[1];
    }

    cout << b[1] << '\n';

}
